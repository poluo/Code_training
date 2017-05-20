import logging as logger


class CustomNormalMiddleware(object):
    def __init__(self):
        self.cookies = None

    def process_request(self, request, spider):
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
        request.headers['Accept'] = '*/*'
        request.headers['Accept-Encoding'] = 'gzip, deflate,br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        # request.headers['X-Requested-With'] = 'XMLHttpRequest'
        request.headers['Host'] = 'www.linkedin.com'
        # request.headers['Origin'] ='https://www.linkedin.com'
        request.headers['Referer'] = 'https://www.linkedin.com/'
        # request.headers['X-IsAJAXForm'] = '1'
        # request.headers['X-LinkedIn-traceDataContext'] = 'X-LI-ORIGIN-UUID=oJeAl5wuwBRADY514yoAAA=='
        # if self.cookies:
        #     request.cookies = self.cookies

