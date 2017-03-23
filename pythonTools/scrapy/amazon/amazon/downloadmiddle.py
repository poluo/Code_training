from twisted.web._newclient import ResponseNeverReceived
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost
from scrapy.core.downloader.handlers.http11 import TunnelError
import re
from scrapy.exceptions import IgnoreRequest
import time
import random
import logging as log
import pymongo
import requests
import json


class CustomNormalMiddleware(object):
    IP_ERRORS = (ResponseNeverReceived, ConnectError, ConnectionLost, TunnelError, TimeoutError, ConnectionRefusedError)

    def __init__(self):
        # for mongodb
        self.client = pymongo.MongoClient('mongodb://poluo:poluo123@115.28.36.253:27017/proxy')
        self.db = self.client.proxy
        self.collection = self.db.proxy_list
        self.proxy = None
        self.cookies = None
        self.agent = None
        self.request_count = 0
        self.used_set = []
        self.update_setting()

    def process_request(self, request, spider):
        self.request_count += 1
        if self.request_count > 100:
            self.request_count = 0
            log.info('request more than 400,update setting')
            self.update_setting()
        if 'signin' in request.url:
            log.info('need signin,try sleep 2s...')
            time.sleep(2)
        if 'dp' in request.url:
            tmp = re.compile(r'/dp/.{10}/').findall(request.url)
            if tmp not in self.used_set:
                flag = True
                self.used_set.append(tmp)
            else:
                flag = False
        else:
            flag = True

        if flag:
            request.meta['proxy'] = self.proxy
            request.headers[
                'User-Agent'] = self.agent
            request.headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
            request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
            request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
            request.headers['Connection'] = 'keep-alive'
            request.headers['Host'] = 'www.amazon.cn'
            request.cookies = self.cookies
        else:
            raise IgnoreRequest

    def update_setting(self):
        self.get_proxy()
        self.get_new_cookie()

    def process_response(self, request, response, spider):
        if 'book' in response.url:
            name = response.css('#title > span:nth-child(1)::text').extract_first()
        else:
            name = 1
        if '自动程序' in response.text or not name:
            log.info('robot check happened,update setting')
            self.update_setting()

        return response

    def get_proxy(self):
        num = 5
        tid = '555947027942665'
        url = 'http://tvp.daxiangdaili.com/ip/?tid={}&num={}&category=2&delay=5&protocol=https&ports=80,8080,3128'.format(
            tid, num)
        ip_all = []
        result = requests.get(url)
        result = result.text.split('\n')
        for one in result:
            if one != '':
                ip = {
                    'ip': one.split(':')[0].strip(),
                    'port': one.split(':')[1].strip()
                }
                ip_all.append(ip)
        if len(ip_all) == 0:
            log.info('NO PROXY AVAILABLE')
        else:
            log.info('get new proxy {}'.format(ip_all))
        tmp = ip_all.pop()
        self.proxy = 'http://{}:{}'.format(tmp['ip'], tmp['port'])

    def get_proxy_test(self):
        order = "888888888888888";
        # 获取IP的API接口
        apiUrl = "http://api.ip.data5u.com/dynamic/get.html?order=" + order;
        ip_all = []
        try:
            # 获取IP列表,一次获取一个
            res = requests.get(apiUrl).text.strip("\n");
            # 按照\n分割获取到的IP
            ips = res.split("\n");
            for one in ips:
                ip = {
                    'ip': one.split(':')[0].strip(),
                    'port': one.split(':')[1].strip()
                }
                ip_all.append(ip)
        except Exception as e:
            log.info(e)
        if len(ip_all) == 0:
            log.info('NO PROXY AVAILABLE')
        else:
            log.info('get new proxy {}'.format(ip_all))
        tmp = random.choice(ip_all)
        self.proxy = 'https://{}:{}'.format(tmp['ip'], tmp['port'])
        log.info('proxy {}'.format(self.proxy))

    def get_new_cookie(self):
        from amazon.agents import AGENTS
        self.agent = random.choice(AGENTS)
        headers = {'user-agent': self.agent}
        flag = 1
        count = 0
        log.info(headers)
        while flag:
            try:
                r = requests.get('https://www.amazon.cn', headers=headers, timeout=5, proxies={'https': self.proxy}, )
            except Exception as e:
                log.info(e)
                count += 1
                time.sleep(2)
                self.get_proxy()
            else:
                flag = 0
            finally:
                log.info('count {}'.format(count))
        cookies = r.headers['Set-Cookie'].split(';')
        result = {}
        for one in cookies:
            if 'session-id-time' in one:
                tmp = one.split(',')[-1].split('=')[-1]
                if tmp != '-':
                    result['session-id-time'] = tmp
            elif 'session-id' in one and 'time' not in one:
                tmp = one.split(',')[-1].split('=')[-1]
                if tmp != '-':
                    result['session-id'] = tmp
            elif 'x-wl-uid' in one:
                tmp = one.split(',')[-1].split('=')[1]
                if tmp != '-':
                    result['x-wl-uid'] = tmp
            elif 'x-acbcn' in one:
                tmp = one.split(',')[-1].split('=')[1]
                if tmp != '-':
                    result['x-acbcn'] = tmp
            elif 'csm-hit' in one:
                tmp = one.split(',')[-1].split('=')[1]
                if tmp != '-':
                    result['csm-hit'] = tmp
            elif 'ubid-acbcn' in one:
                tmp = one.split(',')[-1].split('=')[1]
                if tmp != '-':
                    result['ubid-acbcn'] = tmp
        log.info('new cookies {}'.format(result))
        self.cookies = result
        with open('cookies_dump.json', 'a') as fobj:
            line = json.dumps(self.cookies) + '\n'
            fobj.write(line)

    def process_exception(self, request, exception, spider):
        log.info('exception {}'.format(exception))
        if isinstance(exception, self.IP_ERRORS):
            self.update_setting()
            self.process_request(request, spider)
