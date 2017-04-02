# -*- coding: utf-8 -*-
import scrapy
from scrapy.http import FormRequest
from quora.items import FollowerItem
import pymongo
import os
import time
import requests

class FollowersSpider(scrapy.Spider):
    name = "followers"
    allowed_domains = ["quora.com"]
    handle_httpstatus_list = [429]
    start_urls = (
        'https://www.quora.com/webnode2/server_call_POST',
    )
    frmdata = {}
    frmdata['json'] = '{"args":[],"kwargs":{"email":"997786818@qq.com","password":"poluo123"}}'
    frmdata['formkey'] = '75ec5150317eefe0dae46fc9f101a5da'
    frmdata['postkey'] = 'fc42a7c6aeffd2a56634a5e750b312a4'
    frmdata['window_id'] = 'dep3200-335053055489061942'
    frmdata['referring_controller'] = 'index'
    frmdata['referring_action'] = 'index'
    frmdata['__vcon_json'] = '["Vn03YsuKFZvHV9"]'
    frmdata['__vcon_method'] = 'do_login'
    frmdata['__e2e_action_id'] = 'eojq4wgqa9'
    frmdata['js_init'] = '{}'
    frmdata['__metadata'] = '{}'
    cookies = {'m-b': 'pGLDg-FVmqrI6CF2993g9g\075\075', 'm-s': 'asXhk8Af26gYfG5n-beTXw\075\075',
               'm-css_v': 'ec931eb5703b888f',
               'm-login': '0', 'm-early_v': '0f20c735abd3a97d', 'm-tz': '-480', 'm-wf-loaded': 'q-icons-q_serif',
               '_ga': 'GA1.2.420550872.1490615030'}

    passed_list = []

    url = 'mongodb://poluo:poluo123@115.28.36.253:27017/proxy'
    client = pymongo.MongoClient(url)
    db = client.proxy
    collection = db.quora_user
    collection_backup = db.quora_user_backup
    need_login = 0
    login_count = 0

    def start_requests(self):
        self.logger.info('Login')
        self.cookies['m-login'] = '0'
        for one in self.start_urls:
            yield FormRequest(one, cookies=self.cookies, formdata=self.frmdata, callback=self.parse, headers={
                'Referer': 'https://www.quora.com/'}, dont_filter=True)

    def parse(self, response):
        self.cookies['m-login'] = '1'
        url = 'https://www.quora.com/'
        yield scrapy.Request(url, cookies=self.cookies, callback=self.parse_page)

    def parse_page(self, response):
        while True:
            tmp = self.collection.find_one()
            try:
                self.collection_backup.insert(tmp)
            except pymongo.errors.DuplicateKeyError:
                pass
            self.collection.remove(tmp)
            if tmp:
                yield self.procss_item(tmp)
            else:
                break

    def procss_item(self, tmp):
        if str.isdigit(tmp['Name'][-1]):
            num = int(tmp['Name'].split('-')[-1])
            tmp['Name'] = tmp['Name'].replace('-' + str(num), '')
        else:
            num = int(tmp['Num'])

        if tmp['Name'] not in self.passed_list:
            self.passed_list.append(tmp['Name'])
            if num == 0:
                url = 'https://www.quora.com' + tmp['Name']
            else:
                url = 'https://www.quora.com' + tmp['Name'] + '-1'
            return scrapy.Request(url=url, cookies=self.cookies, callback=self.parse_home_page, headers={
                'Referer': 'https://www.quora.com/'})
        else:
            return None

    def parse_home_page(self, response):
        my_dict = {}
        my_dict['Name'] = response.url.split('/')[-1]
        my_dict['Work'] = response.css(
            'div.CredentialListItem.WorkCredentialListItem.AboutListItem > span > span > span::text').extract_first()
        my_dict['School'] = response.css(
            'div.CredentialListItem.AboutListItem.SchoolCredentialListItem > span > span > span::text').extract_first()
        my_dict['Location'] = response.css(
            'div.CredentialListItem.LocationCredentialListItem.AboutListItem > span > span > span::text').extract_first()
        my_dict['AnswerViews'] = response.css(
            'div.AboutListItem.AnswerViewsAboutListItem > span.main_text::text').extract_first()
        my_dict['PublishedWriter'] = response.css(
            'div.AboutListItem.PublishedWriterAboutListItem > span.main_text > a::text').extract_first()
        my_dict['FollowersNum'] = response.css(
            'li.EditableListItem.NavListItem.FollowersNavItem.NavItem.not_removable > a > span.list_count::text').extract_first()
        my_item = FollowerItem(my_dict)
        yield my_item
        if str.isdigit(response.url[-1]):
            try:
                num = int(response.url.split('-')[-1])
            except ValueError:
                num = 0
                pass
            if num:
                url = response.url.replace(str(num), str(num + 1))
                yield scrapy.Request(url=url, cookies=self.cookies, callback=self.parse_home_page, headers={
                    'Referer': 'https://www.quora.com/'})
        else:
            pass


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
