import logging as logger
import random


class CrawlMiddleware(object):
    def __init__(self):
        self.setting = []
        res = {}
        with open('C:/Users/poluo/PycharmProjects/zhihu/zhihu/Cookies', 'r') as fobj:
            for line in fobj:
                logger.info(line)
                tmp = line.split(';')
                for one in tmp:
                    one = one.replace('\'', '')
                    index = one.index('=')
                    res[one[:index].strip()] = one[index + 1:].replace('\"', '')
                xudid = res['d_c0'].split('|')[0]
                auth = 'Bearer ' + res['z_c0']
                self.setting.append({'cookies': res, 'xudid': xudid, 'auth': auth})

    def process_request(self, request, spider):
        setting = random.choice(self.setting)
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36'
        request.headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
        request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        request.headers['Host'] = 'www.zhihu.com'
        request.headers['Referer'] = 'https://www.zhihu.com/'
        request.cookies = setting['cookies']
        # logger.info('request cookies')
        # logger.info(request.cookies)
        Referfer = request.meta.get('referer')
        if Referfer:
            request.headers['Referer'] = Referfer
            request.headers['x-api-version'] = '3.0.40'
            request.headers['x-udid'] = setting['xudid']
            request.headers['authorization'] = setting['auth']