import logging as logger


class CustomNormalMiddleware(object):
    def __init__(self):
        res = {}
        with open('C:/Users/poluo/PycharmProjects/Linkedin/Linkedin/Cookie', 'r') as fobj:
            for line in fobj:
                tmp = line.split(';')
                for one in tmp:
                    one = one.replace('\'', '')
                    index = one.index('=')
                    res[one[:index].strip()] = one[index + 1:].replace('\"', '')
            logger.info(res)
        self.cookies = res

    def process_request(self, request, spider):
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
        request.headers['Accept'] = '*/*'
        request.headers['Accept-Encoding'] = 'gzip, deflate,br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        request.headers['Host'] = 'www.linkedin.com'
        request.headers['Referer'] = 'https://www.linkedin.com/'
        # if self.cookies:
        #     pass
        request.cookies = self.cookies
        # else:
        #     self.cookies = request.headers.getlist('Cookie')
        #     with open('Cookie', 'w') as fobj:
        #         fobj.write(str(self.cookies))
        #     logger.info(self.cookies)
