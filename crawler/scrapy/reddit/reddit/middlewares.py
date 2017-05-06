import logging as log


class CustomNormalMiddleware(object):
    def __init__(self):
        self.cookies = {
            'loid': '000000000000exy00v.2.1494036347029.Z0FBQUFBQlpEUzk3SlhtMXhmQ0JsdmdQTjdfem01Ynl2V2ZlcWYzaTEyc21Hc1JkMUEyUTRvSC01XzFrVm13b0haeEFfRkw2UllWcDl0U0xKRmhzN2IyWXliVGtNQmtjUGd6VU8yZFJ2UDFKWTEwZkNVMmNjTl8xUDd4ZF9VTjRNUXZLcXJWN3BxNG8',
            'session_tracker': 'evSCD5wTj3ey9RMuA9.0.1494036347024.Z0FBQUFBQlpEUzk3S09oNzlZVzlxUGNGV2c3X0NzYmpaOFdGV1FWN2ZCWmxQbmVQbW16aG5sMzBielZIaFZwMWIwdzg0VzlRRDh3R3VLQzduZ1RvQlI1aVhVVVpIZUozUU5iczRqbnA3R2ZTT1ZpVGZ3VDlyeTRfWDhtM3Yza01yUy11d2ZVaW51MEE',
            'edgebucket': 'PFlj5KT5bklfdvmFjZ', 'pc': 'wa'}

    def process_request(self, request, spider):
        request.headers[
            'User-Agent'] = 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/57.0.2987.133 Safari/537.36'
        request.headers[
            'Accept'] = 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8'
        request.headers['Accept-Encoding'] = 'gzip, deflate, sdch, br'
        request.headers['Accept-Language'] = 'zh-CN,zh;q=0.8'
        request.headers['Connection'] = 'keep-alive'
        request.headers['upgrade-insecure-requests'] = 1
        request.headers['dnt'] = 1
        try:
            cookies_enable = request.meta.get('cookies')
        except Exception as e:
            log.info(e)
            cookies_enable = True
        if cookies_enable:
            try:
                self.cookies[':authority'] = 'www.reddit.com'
                self.cookies[':method'] = 'GET'
                self.cookies[':path'] = request.meta.get('path')
                self.cookies[':scheme'] = 'https'
            except Exception as e:
                log.info(e)
                self.cookies[':authority'] = 'www.reddit.com'
                self.cookies[':method'] = 'GET'
                self.cookies[':path'] = '/user/SallyYatesIsAHero/'
                self.cookies[':scheme'] = 'https'
            request.cookies = self.cookies
