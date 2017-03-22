import logging as log
from twisted.web._newclient import ResponseNeverReceived
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost
from scrapy.core.downloader.handlers.http11 import TunnelError
import re
from scrapy.exceptions import IgnoreRequest
import time
import random
import logging as log
import pymongo


class CustomNormalMiddleware(object):
    IP_ERRORS = (ResponseNeverReceived, ConnectError, ConnectionLost, TunnelError, TimeoutError, ConnectionRefusedError)

    def __init__(self):
        # for mongodb
        self.client = pymongo.MongoClient('mongodb://poluo:poluo123@115.28.36.253:27017/proxy')
        self.db = self.client.proxy
        self.collection = self.db.proxy_list
        self.proxy = None
        self.request_count = 0
        self.used_set = []
        self.setting_list = []
        self.setting = {}
        self.produce_setting()
        # self.get_proxy()

    def process_request(self, request, spider):
        self.request_count += 1
        if self.request_count > 1000:
            self.request_count = 0
            # time.sleep(random.randint(2, 5))
        if 'signin' in request.url:
            # need signin,be slow
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
            # request.meta['proxy'] = 'https://{}:{}'.format(self.proxy['ip'], self.proxy['port'])
            request.headers[
                'User-Agent'] = self.setting['agent']
            request.headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
            request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
            request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
            request.headers['Connection'] = 'keep-alive'
            request.headers['Host'] = 'www.amazon.cn'
            request.cookies = self.setting['cookies']
        else:
            raise IgnoreRequest

    def produce_setting(self):
        from amazon.cookies import COOKIES
        from amazon.agents import AGENTS
        for one in COOKIES:
            self.setting_list.append({'cookies': one, 'agent': random.choice(AGENTS)})
        log.info('get {} setting'.format(len(self.setting_list)))
        self.setting = self.setting_list.pop()

    def process_response(self, request, response, spider):
        if ‘book’ in response.url:
            name = response.css('#title > span:nth-child(1)::text').extract_first()
        if '自动程序' in response.text or not name:
            # update setting
            log.info('robot check happened,update setting')
            if len(self.setting_list):
                self.setting = self.setting_list.pop()
            else:
                log.info('no avaliable setting,try update proxy')
                # self.get_proxy()
                self.produce_setting()
        return response

    def get_proxy(self):
        for one in self.collection.find():
            self.proxy = one
            self.collection.remove(one)
            break
        log.info('got new proxy {}'.format(self.proxy))

    def process_exception(self, request, exception, spider):
        log.info('exception {}'.format(exception))
        if isinstance(exception, self.IP_ERRORS):
            self.get_proxy()
            self.process_request(request, spider)
