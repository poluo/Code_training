# -*- coding: utf-8 -*-
import scrapy
import json
from douban.items import doubanmovieItem, doubanactressItem
import re


class Movie250Spider(scrapy.Spider):
    name = 'doubanmovie'
    allowed_domains = ["douban.com"]
    tag_list = ['%E8%B1%86%E7%93%A3%E9%AB%98%E5%88%86', ]
    start_urls = [
        "https://movie.douban.com/j/search_subjects?type=movie&tag={0}&sort=time&" \
        "page_limit=20&page_start={1}".format(tag, num) for tag in tag_list for num in range(1)
        ]
    num = 0

    def start_requests(self):
        for url in self.start_urls:
            yield scrapy.Request(url, meta={'dont_redirect': True,
                                            'handle_httpstatus_list': [302]}, callback=self.parse)

    def parse(self, response):


        try:
            item_list = json.loads(response.text)["subjects"]
        except Exception as e:
            self.log(e)
            self.log(response.text)

        for one in item_list:
            item = doubanmovieItem()
            item['name'] = one['title']
            item['score'] = one['rate']
            item['url'] = one['url']
            item['cover'] = one['cover']
            item['playable'] = one['playable']

            self.num += 1
            next_link = response.urljoin(item['url'] + '?from=subject-page')
            request = scrapy.Request(next_link, callback=self.parse_subject)
            request.meta['item'] = item
            self.log(item)
            yield request
            break

    def parse_subject(self, response):
        item = response.meta['item']
        info = response.css('#info')
        item['release_time'] = info.css('span[property=\'v:initialReleaseDate\']::attr(content)').extract()

        item['duration'] = info.css('span[property=\'v:runtime\']::text').extract_first()
        item['country'] = re.findall('<span class="pl">制片国家/地区:</span>.+<br/>', response.text)[0].split('>')[-2].split('<')[0]
        item['language'] = re.findall('<span class="pl">语言:</span>.+<br/>', response.text)[0].split('>')[-2].split('<')[0]
        item['tag'] = info.css('span[property=\'v:genre\']::text').extract()
        item['actress_list'] = info.css('a[rel=\'v:starring\']::attr(href)').extract()
        item['rate_num'] = response.css('span[property=\'v:votes\']::text').extract_first()
        self.log('response from {} {}'.format(response.url,item))
        yield item
        for url in item['actress_list']:
            next_link = response.urljoin(url)
            new_request = scrapy.Request(next_link, callback=self.parse_actress)
            yield new_request
            break

    def parse_actress(self, response):
        item = doubanactressItem()
        item['url'] = response.url
        item['name'] = response.css('#content > h1::text').extract_first()
        info_list = response.css('#headline > div.info > ul > li')
        for one in info_list:
            if one.css('span::text').extract_first() == '性别':
                item['sex'] = ''.join(one.css('::text').extract()).replace('性别:', '').strip()
            if one.css('span::text').extract_first() == '出生日期':
                item['birthday'] = ''.join(one.css('::text').extract()).replace('出生日期:', '').strip()
            if one.css('span::text').extract_first() == '出生地':
                item['birthplace'] = ''.join(one.css('::text').extract()).replace('出生地:', '').strip()
        item['movie_list'] = []
        info_list = response.css('div.info')
        for one in info_list:
            tmp = one.css('a::attr(href)').extract_first()
            if 'subject' in tmp:
                item['movie_list'].append(tmp)
        self.log('response from {} \n item ={}'.format(response.url, item))

    def closed(self, reason):
        self.log(reason)
        self.log(self.num)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
