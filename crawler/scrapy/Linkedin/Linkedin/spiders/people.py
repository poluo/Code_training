# -*- coding: utf-8 -*-
import scrapy
from lxml import etree


class PeopleSpider(scrapy.Spider):
    name = "people"
    allowed_domains = ["linkedin.com"]

    def start_requests(self):
        return [scrapy.Request(url='https://www.linkedin.com/uas/login', meta={'cookiejar': 1},
                               callback=self.parse)]

    def parse(self, response):
        account = '997786818@qq.com'
        passwd = 'poluo123'
        tmp = response.css('#login')
        is_js_enabled = tmp.css('input[type="hidden"]:nth-child(1)::attr(value)').extract_first()
        source_app = tmp.css('input[type="hidden"]:nth-child(2)::attr(value)').extract_first()
        try_count = tmp.css('#tryCount::attr(value)').extract_first()
        clicked_suggestion = tmp.css('#clickedSuggestion::attr(value)').extract_first()
        session_redirect = tmp.css('#session_redirect-login::attr(value)').extract_first()
        trk = tmp.css('#trk::attr(value)').extract_first()
        login_csrf_param = tmp.css('#loginCsrfParam-login::attr(value)').extract_first()
        from_email = tmp.css('#fromEmail::attr(value)').extract_first()
        csrf_token = tmp.css('#csrfToken-login::attr(value)').extract_first()
        source_alias = tmp.css('#sourceAlias-login::attr(value)').extract_first()
        sgign = tmp.css('div.form-buttons > input::attr(value)').extract_first()
        if not trk:
            trk = ''
        if not login_csrf_param:
            login_csrf_param = ''
        if not from_email:
            from_email = ''
        post_data = {
            'isJsEnabled': is_js_enabled,
            'source_app': source_app,
            'tryCount': try_count,
            'clickedSuggestion': clicked_suggestion,
            'session_key': account,
            'session_password': passwd,
            'signin': sgign,
            'session_redirect': session_redirect,
            'trk': trk,
            'loginCsrfParam': login_csrf_param,
            'fromEmail': from_email,
            'csrfToken': csrf_token,
            'sourceAlias': source_alias
        }
        self.logger.info(post_data)
        response = response.replace(url='https://www.linkedin.com/uas/login-submit')
        self.logger.info(response.url)
        return scrapy.FormRequest.from_response(response, formdata=post_data, callback=self.after_login,
                                                meta={'cookiejar': response.meta['cookiejar']})

    def after_login(self, response):
        self.logger.info(response.status)
        yield scrapy.Request(url='http://www.linkedin.com/feed/', callback=self.parse_home,
                             meta={'cookiejar': response.meta['cookiejar']})

    def parse_home(self, response):
        pass

if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
