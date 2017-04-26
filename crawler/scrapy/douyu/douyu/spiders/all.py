# -*- coding: utf-8 -*-
import scrapy
import re
import json
import requests
from douyu.settings import MY_HEADERS
import time


class AllSpider(scrapy.Spider):
    name = "all"
    allowed_domains = ["douyu.com"]
    start_urls = (
        'https://www.douyu.com/directory#',
    )
    live_data = []

    def parse(self, response):
        unit_list = response.css('li.unit')
        for one in unit_list:
            unit = {}
            url = one.css('::attr(href)').extract_first()
            unit['href'] = url
            unit['title'] = one.css('p.title::text').extract_first()
            unit['data_tid'] = one.css('::attr(data-tid)').extract_first()
            unit['pic_href'] = one.css('img::attr(src)').extract_first()
            yield scrapy.Request(url='https://www.douyu.com' + url, callback=self.parse_directory)

    def parse_directory(self, response):
        live_list = response.css('#live-list-contentbox > li')
        if not live_list:
            referer = response.meta['referer']
            live_list = response.css('li')
        else:
            referer = response.url

        if not live_list:
            self.logger.warning('None')
        for one in live_list:
            live = {}
            live['href'] = one.css('a::attr(href)').extract_first()
            live['title'] = one.css('a::attr(title)').extract_first()
            live['tag'] = one.css('a > div > div.mes-tit > span.tag.ellipsis::text').extract_first()
            live['owner'] = one.css('a > div.mes > P > span.dy-name.ellipsis.fl::text').extract_first()
            live['num'] = one.css('a > div.mes > P > span.dy-num.fr::text').extract_first()
            if live not in self.live_data:
                self.live_data.append(live)
                self.logger.debug(live)

        if 'page' not in response.url:
            num = 2
            tmp = re.findall('count:.*', response.text)[0].strip()[:-1].split(':')[-1].strip().replace('"', '')
            max_num = int(tmp)
            next_url = response.url + '?page=' + str(num) + '&isAjax=1'
        else:
            max_num = response.meta['max-num']
            num = response.meta['num'] + 1
            next_url = response.url.replace(str(num - 1), str(num))

        if num <= max_num:
            # self.post_data(referer)
            yield scrapy.Request(url=next_url, meta={'_dys_lastPageCode': 'page_live,', 'referer': referer,
                                                     'cookies': True, 'num': num, 'max-num': max_num,
                                                     '_dys_refer_action_code': 'click_pagecode'},
                                 callback=self.parse_directory)

    @classmethod
    def post_data(self, url):
        t = time.time()
        t = str(int(t * 1000))
        multi = '[{"d":"","i":0,"rid":0,"u":"https://www.douyu.com/directory/game/wzry",' \
                '\"ru":"","ac":"click_pagecode","rpc":"","pc":"page_live","pt":1493209129299,' \
                '"oct":{},' \
                '"dur":0,"pro":"host_site","ct":"web","e":{"type":2,"pg":3,"rac":"click_pagecode"}}]'
        formdata = {'multi': multi, 'v': '1.5'}
        res = requests.post(url='https://dotcounter.douyucdn.cn/deliver/fish2', data=formdata, verify=False,
                            headers=MY_HEADERS)

    def closed(self, reason):
        self.logger.info(reason)
        self.logger.info(len(self.live_data))

    if __name__ == '__main__':
        from scrapy.cmdline import execute

        execute()
