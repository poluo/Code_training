# -*- coding: utf-8 -*-
import scrapy
from maoyan.items import MovieOverallItem


class InfoSpider(scrapy.Spider):
    name = "info"
    allowed_domains = ["maoyan.com"]
    start_urls = (
        'http://maoyan.com/films?',
    )
    count = 0

    def parse(self, response):
        movie_list = response.css('div.channel-detail.movie-item-title')
        for one in movie_list:
            title = one.css('::attr(title)').extract_first()
            href = one.css('a::attr(href)').extract_first()
            yield MovieOverallItem({'name': title, 'href': href})
            self.logger.info(title + href)
            # yield scrapy.Request(url='http://maoyan.com' + href, callback=self.parse_movie,
            #                     meta={'title': title, 'href': href, 'cookies': True})
        self.count += 1
        next_page = 'http://maoyan.com/films?offset' + str(self.count * 30)
        if self.count < 3:
            yield scrapy.Request(url=next_page, callback=self.parse,
                                 meta={'cookies': True})

    def parse_movie(self, response):
        English_name = response.css(
            'div.celeInfo-right.clearfix > div.movie-brief-container > div::text').extract_first()
        title = response.meta.get('title')
        href = response.meta.get('href')
        self.logger.info('{} {} {}'.format(title, English_name, href))


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
