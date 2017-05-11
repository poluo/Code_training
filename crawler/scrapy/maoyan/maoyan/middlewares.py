class CustomNormalMiddleware(object):
    def __init__(self):
        self.cookies = {'_lxsdk': '15bf273283fc8-09fdefa5a314d-8373f6a-1fa400-15bf273283fc8',
                        '__utma': '17099173.200065505.1494421420.1494421420.1494421420.1',
                        '__utmz': '17099173.1494421420.1.1.utmcsr',
                        'lt': 'Q8Xb8ASMM7CLCsRw2-K9YcgMeg4AAAAAAgQAAF0tRB7my2HrvrgbCabTNcXhwLHEI3xwdYn6OOYF-fQHhN04YOA-p05DSuZjLqRyhA',
                        'lt.sig': '8Htm5IgU2Gnh_3rpL_LoAvRiajA', '_lx_utm': '',
                        '__mta': '41899549.1494421285773.1494504614343.1494504766524.32',
                        '_lxsdk_s': '345994513a31761776e3da3061ca%7C%7C16'}

    def process_request(self, request, spider):
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36'
        request.headers[
            'Accept'] = 'application/json, text/javascript, */*; q=0.01'
        request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        request.headers['referer'] = 'http://maoyan.com/films?'
        request.headers['DNT'] = 1
        request.headers['Host'] = 'maoyan.com'
        request.headers['Upgrade-Insecure-Requests'] = 1
        request.cookies = self.cookies
