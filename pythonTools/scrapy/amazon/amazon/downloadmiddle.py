import logging as log
from twisted.web._newclient import ResponseNeverReceived
from twisted.internet.error import TimeoutError, ConnectionRefusedError, ConnectError, ConnectionLost
from scrapy.core.downloader.handlers.http11 import TunnelError
import re
from scrapy.exceptions import IgnoreRequest
import time

class CustomNormalMiddleware(object):
    def __init__(self):
        self.used_set = []
        self.setting=[]
        self.cookies = {'session-id': '452-1177854-7355524', 'session-id-time': '2082729601l',
                        'ubid-acbcn': '454-5630272-1938337',
                        'session-token': 'RxkMPtwxH4lKEpmuxd5JzA1Lw02mK/ezCCUV8ltabW4BrnabsNsbACKIh4y8UAf6POVih70SBWvx0WxgHxqKNEVqKu83YGvnyqEpnPFxdSgpUUWX6eGqKqFBILeLGgM0dse+fLCBpXwE6a6UNNE1Uzl5Vcj3H9zHLRpBDNxTuhg3pHKbn48u0hHqBY471/Z5fK+Z1OERrWMgVwfuBYGhI79SahBH7MlRx+/s8npIW6GCfFRxTq/vnw==',
                        'csm-hit': 'MCXEJA8B83DXNVNXD0ZV+s-JVQ3JSC44E31X7V2J7T2|1489891366789',
                        'x-wl-uid': '1jX/awdUfnsR9g3GeHBR31ZsvqGf4rJvh4kWAVLxk9lSsmvz58XmBO9g3mpK7aT4lNAgt8IwyCV4='}

    def process_request(self, request, spider):
        if 'signin' in request.url:
            # need signin,be slow
            time.sleep(2)
        if 'dp' in request.url:
            tmp = re.compile(r'/dp/.{10}/').findall(request.url)
            if tmp not in self.used_set:
                flag = True
                self.used_set.append(tmp)
            else:
                flag = False
        else:
            flag = True

        if flag:
            request.headers[
                'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87'
            request.headers['Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
            request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
            request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8,zh-TW;q=0.6'
            request.headers['Connection'] = 'keep-alive'
            request.headers['Host'] = 'www.amazon.cn'
            request.cookies = self.cookies
        else:
            raise IgnoreRequest
            
    def produce_setting(self):
        pass
        '''from amazon.setting import COOKIES
        from amazon.setting import AGENTS
        for one in COOKIES:
            self.setting.append({cookie:one,agent:AGENTS.pop()})'''

    def process_response(self, request, response, spider):
        # print('response headers {}'.format(response.headers))
        return response

    def process_exception(self, request, exception, spider):
        print(exception)
