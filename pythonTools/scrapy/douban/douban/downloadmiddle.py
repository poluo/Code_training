import logging as log
from twisted.web._newclient import ResponseNeverReceived
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost
from scrapy.core.downloader.handlers.http11 import TunnelError
import requests
import random
import string
from douban.validate import Validator
import json
import time


class CustomNormalMiddleware(object):
    IP_ERRORS = (ResponseNeverReceived, ConnectError, ConnectionLost, TunnelError, ValueError)
    SERVER_ERRORS = (TimeoutError, ConnectionRefusedError)
    validator = Validator("https://movie.douban.com/", 5, 1, 5)

    def __init__(self):
        self.proxy_list = []
        self.proxy = None
        self.cookies = None
        self.update_proxy(1)

    def process_request(self, request, spider):
        log.debug('downloadmiddle process')
        if 'douban' in request.url:
            request.meta['proxy'] = self.proxy
            request.cookies['bid'] = self.cookies

    def process_response(self, request, response, spider):
        if response.status != 200:
            log.debug("response status not in 200 {}".format(response.status))
            self.update_proxy(1)
            new_request = request.copy()
            new_request.dont_filter = True
            new_request.meta['proxy'] = self.proxy
            new_request.cookies['bid'] = self.cookies
            return new_request
        else:
            return response

    def process_exception(self, request, exception, spider):
        if isinstance(exception, self.IP_ERRORS):
            self.update_proxy(1)
        elif isinstance(exception, self.SERVER_ERRORS):
            log.debug("exception {}".format(exception))
            self.update_proxy(0)
            new_request = request.copy()
            new_request.meta['proxy'] = self.proxy
            new_request.cookies['bid'] = self.cookies
            new_request.dont_filter = True
            return new_request
        else:
            pass
        log.info('exception  {}'.format(exception))

    def update_proxy(self, mode):
		# mode 0, try again
        # self.cookies = "".join(random.sample(string.ascii_letters + string.digits, 11))
        if mode:
            self.validte()
            self.cookies = "".join(random.sample(string.ascii_letters + string.digits, 11))
            log.info('cookies = {}'.format(self.cookies))

    def validte(self):
        while not len(self.proxy_list):
            tmp = self.get_proxy()
            self.proxy_list = self.validator.run(tmp)
        log.info('proxy list len ={}'.format(len(self.proxy_list)))
        tmp = self.proxy_list.pop()
        self.proxy = "http://{}:{}".format(tmp['ip'], tmp['port'])
        log.info('new proxy {}'.format(self.proxy))

    def get_proxy(self):
        tid = '555947027942665'
        num = 10
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
            log.warning('NO PROXY AVAILABLE')
        else:
            log.info('update proxy')
        return ip_all
