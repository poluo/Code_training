# -*- coding: utf-8 -*-
import scrapy
from scrapy.http import FormRequest


class FollowersSpider(scrapy.Spider):
    name = "followers"
    allowed_domains = ["quora.com"]
    start_urls = (
        'https://www.quora.com/webnode2/server_call_POST',
    )
    frmdata = {}
    frmdata['json'] = '{"args":[],"kwargs":{"email":"email","password":"password"}}'
    frmdata['formkey'] = '376e95ee12d0ea5c0283756e752e677b'
    frmdata['postkey'] = '08abe632cba5fc15aadd81d958143e1f'
    frmdata['window_id'] = 'dep3705-2845669908552192457'
    frmdata['referring_controller'] = 'index'
    frmdata['referring_action'] = 'index'
    frmdata['__vcon_json'] = '["Vn03YsuKFZvHV9"]'
    frmdata['__vcon_method'] = 'do_login'
    frmdata['__e2e_action_id'] = 'eodozmz679'
    frmdata['js_init'] = '{}'
    frmdata['__metadata'] = '{}'
    cookies = {'m-b': 'aGHsLgiQsfTPMCptNf4GWQ\075\075', 'm-s': '16mssxDvJ1tuVYXVsuvu1w\075\075', 'm-css_v': '786be883cc4fadb1',
               'm-login': '0', 'm-early_v': '8739208bd2590aae', 'm-tz': '-480', 'm-wf-loaded': 'q-icons-q_serif',
               '_ga': 'GA1.2.420550872.1490615030'}

    def start_requests(self):
        for one in self.start_urls:
            yield FormRequest(one, cookies=self.cookies, formdata=self.frmdata, callback=self.parse, headers={
                'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36',
                'Referer': 'https://www.quora.com/'})

    def parse(self, response):
        self.cookies['m-login'] = '1'
        url = 'https://www.quora.com/'
        yield scrapy.Request(url, cookies=self.cookies, callback=self.parse_page, headers={
            'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/56.0.2924.87 Safari/537.36'})

    def parse_page(self, response):
        print(response.text)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
