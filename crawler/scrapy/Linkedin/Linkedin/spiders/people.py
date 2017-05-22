# -*- coding: utf-8 -*-
import scrapy
import re
import poplib


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
    company = re.compile('fs_miniCompany: [\d]*&')

    def start_requests(self):
        return [scrapy.Request(url='https://www.linkedin.com/uas/login', meta={'cookiejar': 1},
                               callback=self.parse)]

    def parse(self, response):
        account = 'xxx'
        passwd = 'xx'
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
        if 'consumer-email-challenge' in response.url:
            code = self.get_vcode()
            tmp = response.css('#uas-consumer-ato-pin-challenge')
            sgign = '提交'
            challenge_id = tmp.css('#security-challenge-id-ATOPinChallengeForm::attr(value)').extract_first()
            dts = tmp.css('#dts-ATOPinChallengeForm::attr(value)').extract_first()
            origSourceAlias = tmp.css('#origSourceAlias-ATOPinChallengeForm::attr(value)').extract_first()
            csrfToken = tmp.css('#csrfToken-ATOPinChallengeForm::attr(value)').extract_first()
            sourceAlias = tmp.css('#sourceAlias-ATOPinChallengeForm::attr(value)').extract_first()
            post_data = {
                'PinVerificationForm_pinParam': code,
                'signin': sgign,
                'security-challenge-id': challenge_id,
                'dts': dts,
                'origSourceAlias': origSourceAlias,
                'csrfToken': csrfToken,
                'sourceAlias': sourceAlias,
            }
            self.logger.info(post_data)
            response = response.replace(url='https://www.linkedin.com/uas/ato-pin-challenge-submit')
            yield scrapy.FormRequest.from_response(response, formdata=post_data, callback=self.after_login,
                                                   meta={'cookiejar': response.meta['cookiejar']})
        else:
            yield scrapy.Request(url='http://www.linkedin.com/feed/', callback=self.parse_home,
                                 meta={'cookiejar': response.meta['cookiejar']})

    def parse_home(self, response):
        text = response.text.replace('&quot;', '"')
        res = self.public_id.findall(text)
        self.logger.info(text)
        for one in res[1:]:
            self.logger.info(one)
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

        company = self.company.findall(content)
        self.logger.info(company)

        res = self.public_id.findall(content)
        for one in res[1:]:
            one = re.split(':', one.split(',')[0])[1][1:-1]
            yield scrapy.Request(url='http://www.linkedin.com/in/' + one + '/', callback=self.parse_people,
                                 meta={'cookiejar': response.meta['cookiejar']})

    def get_vcode(self):
        mail_host = 'xx'
        mail_user = 'xx'
        mail_passwd = 'xx'
        # 连接到POP3服务器:
        server = poplib.POP3_SSL(mail_host)
        # 可以打开或关闭调试信息:
        # server.set_debuglevel(1)
        # 可选:打印POP3服务器的欢迎文字:
        # print(server.getwelcome())
        # 身份认证:
        server.user(mail_user)
        server.pass_(mail_passwd)
        # list()返回所有邮件的编号:
        resp, mails, octets = server.list()
        index = len(mails)
        # 收取最新邮件
        resp, lines, octets = server.retr(index)
        msg = '\r\n'.join([one.decode('utf8') for one in lines])
        if 'security' in msg:
            res = re.findall('\s\d{6}\s', msg)[0].strip()
        else:
            res = None
        # 可以根据邮件索引号直接从服务器删除邮件:
        # server.dele(index)
        # 关闭连接:
        server.quit()
        return res


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
