import logging as log
from twisted.web._newclient import ResponseNeverReceived
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost
from scrapy.core.downloader.handlers.http11 import TunnelError
from scrapy.exceptions import CloseSpider
import requests
import random
import string


class CustomNormalMiddleware(object):
    DONT_RETRY_ERRORS = (
    TimeoutError, ConnectionRefusedError, ResponseNeverReceived, ConnectError, ConnectionLost, TunnelError, ValueError)

    def __init__(self):
        self.proxy_list = []
        self.proxy = None
        self._count = 501
        # every 200 times change a proxy
        self._threshold = 20
        self.update_proxy()

    def process_request(self, request, spider):
        log.debug('downloadmiddle process')
        if 'douban' in request.url:   
            request.meta['proxy'] = self.proxy
            request.cookies['bid'] = self.cookies

    def process_response(self, request, response, spider):
        if response.status != 200:
            log.debug("response status not in 200 {}".format(response.status))
            self.update_proxy()
            new_request = request.copy()
            new_request.dont_filter = True
            new_request.meta['proxy'] = self.proxy
            return new_request
        else:
            return response

    def process_exception(self, request, exception, spider):
        if isinstance(exception, self.DONT_RETRY_ERRORS):
            log.debug("exception {}".format(exception))
            self.update_proxy()
            new_request = request.copy()
            new_request.meta['proxy'] = self.proxy
            new_request.dont_filter = True
            return new_request
        else:
            log.info('exception retry {}'.format(exception))

    def update_proxy(self):
        self._count += 1
        log.info(self._count)
        self.cookies ="{}".format("".join(random.sample(string.ascii_letters + string.digits, 11)))
        log.info('cookies = {}'.format(self.cookies))
        if self._count > self._threshold:
            self._count = 0
            self.validte()

    def validte(self):
        while True:
            try:
                tmp = self.proxy_list.pop()
            except IndexError as e:
                self.get_proxy_in_daxiangdaili()
                tmp = self.proxy_list.pop()
            self.proxy = "https://{0}:{1}".format(tmp['ip'], tmp['port'])
            try:
                r = requests.get('https://www.baidu.com', proxies={"https":self.proxy}, timeout=10)
                if r.status_code == requests.codes.ok:
                    log.info('validate {}'.format(self.proxy))
                    break
                else:
                    log.info('not validate {}'.format(self.proxy))
            except Exception as e:
                log.info("not validate {} {}".format(self.proxy,e))
            

    def get_proxy_in_daxiangdaili(self):
        tid = '555947027942665'
        num = 10
        url = 'http://tvp.daxiangdaili.com/ip/?tid={}&num={}&category=2&delay=5&protocol=https&ports=80,8080,3128'.format(tid, num)
        result = requests.get(url)
        result = result.text.split('\n')
        for one in result:
            if one != '':
                ip = {
                    'ip': one.split(':')[0].strip(),
                    'port': one.split(':')[1].strip()
                }
                self.proxy_list.append(ip)
        if len(self.proxy_list) == 0:
            log.warning('NO PROXY AVAILABLE')
        else:
            log.info('update proxy')
