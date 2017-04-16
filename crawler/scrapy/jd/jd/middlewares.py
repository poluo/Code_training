import logging as log
from jd.agents import AGENTS
import random


class CustomNormalMiddleware(object):
    def __init__(self):
        self.cookies = {'__jdv': '122270672|direct|-|none|-|1492328119353', 'ipLoc-djd': '1-72-4137-0', 'areaId': '1',
                        'listck': '0b15ebdd1717df092dc803a111f3e90d',
                        '__jda': '122270672.14923281193521819411447.1492328119.1492328119.1492328119.1',
                        '__jdb': '122270672.4.14923281193521819411447|1.1492328119', '__jdc': '122270672',
                        '__jdu': '14923281193521819411447',
                        ' o2-webp': 'true',
                        '3AB9D23F7A4B3C9B': 'POP3RB26NQEQKDRSJ6CVJUPMWCZTQIXTIEISD7CAF3UOGEEPI2VTWX7KTRBUM4DMB4X4CABVDPATZ6X4ER4U4VM7GE'}

    def process_request(self, request, spider):
        request.headers['User-Agent'] = random.choice(AGENTS)
        request.headers[
            'Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
        request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
        request.headers['Connection'] = 'keep-alive'
        request.headers['referer'] = 'https://www.jd.com/'
        request.headers['cache-control'] = 'max-age=0'
        try:
            cookies_enable = request.meta.get('cookies')
        except Exception as e:
            log.info(e)
            cookies_enable = True
        if cookies_enable:
            try:
                self.cookies[':authority'] = request.meta.get('authority')
                self.cookies[':method'] = request.meta.get('method')
                self.cookies[':path'] = request.meta.get('path')
                self.cookies[':scheme'] = request.meta.get('scheme')
            except Exception as e:
                log.info(e)
                self.cookies[':authority'] = 'www.jd.com'
                self.cookies[':method'] = 'GET'
                self.cookies[':path'] = '/'
                self.cookies[':scheme'] = 'https'
            request.cookies = self.cookies

        # def process_response(self, request, response, spider):
        #     pass
        #
        # def process_exception(self, request, exception, spider):
        #     pass
