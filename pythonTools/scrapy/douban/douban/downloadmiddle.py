import logging as log
import pymongo
from twisted.web._newclient import ResponseNeverReceived
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError
from scrapy.exceptions import CloseSpider

class CustomNormalMiddleware(object):
    DONT_RETRY_ERRORS = (TimeoutError, ConnectionRefusedError, ResponseNeverReceived, ConnectError, ValueError)

    def __init__(self):
        url = 'mongodb://poluo:poluo123@115.28.36.253:27017/proxy'
        self.client = pymongo.MongoClient(url)
        self.db = self.client.proxy
        self.collection = self.db.proxy_list
        self.pending_proxy_list = []
        self.proxy = None
        self._count = 0
        # every 200 times change a proxy
        self._threshold = 200
        self.update_proxy()

    def process_request(self, request, spider):
        log.debug('downloadmiddle process')
        if 'douban' in request.url:
            self._count += 1
            if self._count > self._threshold:
                self._count = 0
                self.update_proxy()
            request.meta['proxy'] = self.proxy

    def process_response(self, request, response, spider):
        if response.status != 200:
            log.debug("response status not in 200")
            self.update_proxy()
            new_request = request.copy()
            new_request.dont_filter = True
            new_request.meta['proxy'] = self.proxy
            return new_request
        else:
            return response

    def process_exception(self, request, exception, spider):
        if isinstance(exception, self.DONT_RETRY_ERRORS):
            print(exception)
            log.debug("process_exception")
            self.update_proxy()
            new_request = request.copy()
            new_request.meta['proxy'] = self.proxy
            new_request.dont_filter = True
            return new_request
        else:
            log.info('exception retry {}'.format(exception))

    def update_proxy(self):
        tmp = self.collection.find_one()
        self.collection.remove(tmp)
        if not tmp:
            try:
                self.proxy = self.pending_proxy_list.pop()
            except IndexError:
                log.warning('NO PROXY AVAILABLE')
                raise CloseSpider('NO PROXY AVAILABLE')
        else:
            if not self.proxy:
                self.pending_proxy_list.append(self.proxy)
            self.proxy = "http://{0}:{1}".format(tmp['ip'], tmp['port'])
        log.debug(self.proxy)
        log.debug('update proxy')
