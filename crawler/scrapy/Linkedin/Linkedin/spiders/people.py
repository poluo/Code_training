# -*- coding: utf-8 -*-
import scrapy
import re


class PeopleSpider(scrapy.Spider):
    name = "people"
    allowed_domains = ["linkedin.com"]
    first_name = re.compile('"firstName":"(.*?)"')
    last_name = re.compile('"lastName":"(.*?)"')
    summary = re.compile('"summary":"(.*?)"')
    location_name = re.compile('"locationName":"(.*?)"')
    occupation = re.compile('"headline":"(.*?)"')
    educations = re.compile('(\{[^\{]*?profile\.Education"[^\}]*?\})')
    school_name = re.compile('"schoolName":"(.*?)"')
    position = re.compile('(\{[^\{]*?profile\.Position"[^\}]*?\})')
    company_name = re.compile('"companyName":"(.*?)"')
    public_id = re.compile('"publicIdentifier":"[^{}]*",')

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
        response = response.replace(url='https://www.linkedin.com/uas/login-submit')
        return scrapy.FormRequest.from_response(response, formdata=post_data, callback=self.after_login,
                                                meta={'cookiejar': response.meta['cookiejar']})

    def after_login(self, response):
        yield scrapy.Request(url='http://www.linkedin.com/feed/', callback=self.parse_home,
                             meta={'cookiejar': response.meta['cookiejar']})

    def parse_home(self, response):
        text = response.text.replace('&quot;', '"')
        res = self.public_id.findall(text)
        for one in res[1:]:
            one = re.split(':', one.split(',')[0])[1][1:-1]
            yield scrapy.Request(url='http://www.linkedin.com/in/' + one + '/', callback=self.parse_people,
                                 meta={'cookiejar': response.meta['cookiejar']})

    def parse_people(self, response):
        text = response.text
        content = text.replace('&quot;', '"')
        profile_txt = ' '.join(re.findall('(\{[^\{]*?profile\.Profile"[^\}]*?\})', content))
        res = {}
        first_name = self.first_name.findall(profile_txt)
        last_name = self.last_name.findall(profile_txt)
        if first_name and last_name:
            res['name'] = '{} {}'.format(last_name[0], first_name[0])
            res['url'] = response.url
            summary = self.summary.findall(profile_txt)
            if summary:
                res['summary'] = summary[0].replace('&#92;n', '')
            occupation = self.occupation.findall(profile_txt)
            if occupation:
                res['occupation'] = occupation[0]

            location_name = self.location_name.findall(profile_txt)
            if location_name:
                res['location'] = location_name[0]

            educations = self.educations.findall(content)
            if educations:
                res['education'] = ''
            for one in educations:
                school_name = self.school_name.findall(one)
                res['education'] += school_name[0]

            position = self.position.findall(content)
            if position:
                res['position'] = ''
                for one in position:
                    company_name = self.company_name.findall(one)
                    res['position'] += company_name[0]
            yield res
        else:
            self.logger.warning('No matched')
            self.logger.info(profile_txt)

        res = self.public_id.findall(content)
        for one in res[1:]:
            one = re.split(':', one.split(',')[0])[1][1:-1]
            yield scrapy.Request(url='http://www.linkedin.com/in/' + one + '/', callback=self.parse_people,
                                 meta={'cookiejar': response.meta['cookiejar']})


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
