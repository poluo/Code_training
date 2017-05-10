import logging as log


class CustomNormalMiddleware(object):
    def __init__(self):
        self.cookies = {'_lxsdk': '15bf273283fc8-09fdefa5a314d-8373f6a-1fa400-15bf273283fc8',
                        '__utma': '17099173.200065505.1494421420.1494421420.1494421420.1',
                        '__utmb': '17099173.32.9.1494421618244', '__utmc': '17099173',
                        '__utmz': '17099173.1494421420.1.1.utmcsr', '_lx_utm': '',
                        '__mta': '41899549.1494421285773.1494422613214.1494422669525.18',
                        '_lxsdk_s': '63b0b1b46a0b8c9058982c94aa4a%7C%7C90'}

    def process_request(self, request, spider):
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36'
        request.headers[
            'Accept'] = 'application/json, text/javascript, */*; q=0.01'
        request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        request.headers['referer'] = 'http://maoyan.com/films'
        request.headers['DNT'] = 1
        request.headers['Host'] = 'maoyan.com'

        request.cookies = self.cookies
