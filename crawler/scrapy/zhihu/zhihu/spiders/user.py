# -*- coding: utf-8 -*-
import scrapy
import re


class UserSpider(scrapy.Spider):
    name = "user"
    allowed_domains = ["zhihu.com"]

    def start_requests(self):
        urls = self.settings.getlist('URL')
        for one in urls:
            yield scrapy.Request(url=one, callback=self.parse)

    def parse(self, response):
        text = response.text.replace('&quot;', '"')
        # self.logger.info(text)
        next_url = 'https:' + re.findall('"next":"http://.*desktop=True', text)[0].split(':')[2].replace('amp;','')
        self.logger.info(next_url)
        yield scrapy.Request(url=next_url, meta={'referer': response.url}, callback=self.parse_activities)

    def parse_activities(self, response):
        self.logger.info(response.text)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
