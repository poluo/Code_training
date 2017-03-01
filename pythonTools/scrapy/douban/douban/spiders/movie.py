# -*- coding: utf-8 -*-
import scrapy
import json
from douban.items import doubanmovieItem, doubanactressItem
import re

class Movie250Spider(scrapy.Spider):
    name = 'doubanmovie'
    allowed_domains = ["douban.com"]
    start_urls = [
        "https://movie.douban.com/j/search_subjects?type=movie&tag=%E8%B1%86"
        "%E7%93%A3%E9%AB%98%E5%88%86&sort=time&page_limit=20&page_start=" + str(i) for i in range(1)
        ]
    num = 0

    def parse(self, response):
        item = doubanmovieItem()

        item_list = json.loads(response.text)["subjects"]
        for one in item_list:
            item['name'] = one['title']
            item['score'] = one['rate']
            item['url'] = one['url']
            item['cover'] = one['cover']
            item['playable'] = one['playable']

            self.num += 1
            next_link = response.urljoin(item['url'] + '?from=subject-page')
            request = scrapy.Request(next_link, callback=self.parse_subject)
            request.meta['item'] = item
            yield request


    def parse_subject(self, response):
        item = response.meta['item']
        info = response.css('#info')
        item['release_time'] = info.css('span[property=\'v:initialReleaseDate\']::attr(content)').extract()

        item['duration'] = info.css('span[property=\'v:runtime\']::text').extract_first()
        item['country'] = re.findall('<span class="pl">制片国家/地区:</span>.+<br/>', response.text)[0].split('>')[-2].split('<')[0]
        item['language'] = re.findall('<span class="pl">语言:</span>.+<br/>', response.text)[0].split('>')[-2].split('<')[0]
        item['tag'] = info.css('span[property=\'v:genre\']::text').extract()
        item['actress_list']= info.css('a[rel=\'v:starring\']::attr(href)').extract()
        item['rate_num'] = response.css('span[property=\'v:votes\']::text').extract_first()
        print(item)

    def closed(self, reason):
        self.log(reason)
        self.log(self.num)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
