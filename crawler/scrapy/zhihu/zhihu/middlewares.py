import logging as logger


class CrawlMiddleware(object):
    def __init__(self):
        res = {}
        with open('C:/Users/poluo/PycharmProjects/zhihu/zhihu/Cookies', 'r') as fobj:
            for line in fobj:
                tmp = line.split(';')
                for one in tmp:
                    one = one.replace('\'', '')
                    index = one.index('=')
                    res[one[:index].strip()] = one[index + 1:].replace('\"', '')
            logger.info(res)
        self.xudid= res['d_c0'].split('|')[0]
        self.auth = 'Bearer '+res['z_c0']
        logger.info(self.xudid)
        logger.info(self.auth)
        self.cookies = res

    def process_request(self, request, spider):
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
        request.headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
        request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        request.headers['Host'] = 'www.zhihu.com'
        request.headers['Referer'] = 'https://www.zhihu.com/'
        request.cookies = self.cookies
        try:
            Referfer = request.meta.get('referer')
            request.headers['Referer'] = Referfer
            request.headers['x-api-version'] = '3.0.40'
            request.headers['x-udid'] = self.xudid
            request.headers['authorization'] = self.auth
        except Exception as e:
            logger.info(e)
