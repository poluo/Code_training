import logging as log
import pymongo


class CustomNormalMiddleware(object):
    def __init__(self):
        url = 'mongodb://poluo:poluo123@115.28.36.253:27017/proxy'
        self.client = pymongo.MongoClient(url)
        self.db = self.client.proxy
        self.collection = self.db.proxy_list

        self.proxy = None
        self._count = 0
        # every 20 times change a proxy
        self._threshold = 20
        self.update_proxy()

    def process_request(self, request, spider):
        if 'douban' in request.url:
            self._count += 1
            if self._count > self._threshold:
                self._count = 0
                self.update_proxy()
            request.meta['proxy'] = "http://{0}:{1}".format(self.proxy['ip'], self.proxy['port'])

    def update_proxy(self):
        self.proxy = self.collection.find_one()
        self.collection.remove(self.proxy)
        log.info(self.proxy)
        log.info('update proxy')
