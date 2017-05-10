# -*- coding: utf-8 -*-
import scrapy


class InfoSpider(scrapy.Spider):
    name = "info"
    allowed_domains = ["maoyan.com"]
    start_urls = (
        'http://maoyan.com/films?',
    )
    count = 0

    def parse(self, response):
        movie_list = response.css('dl.movie-list > dd > div.channel-detail.movie-item-title')
        self.logger.info(response.text)
        for one in movie_list:
            title = one.css('::attr(title)').extract_first()
            href = one.css('a::attr(href)').extract_first()
            self.logger.info('{} {}'.format(title,href))
            yield scrapy.Request(url='http://maoyan.com' + href, callback=self.parse_movie,
                                 meta={'title': title, 'href': href, 'cookies': True})
        # next_page = response.css('div.movies-pager > ul.list-pager > li:nth-last-child(1) > a::attr(href)').extract_first()
        self.count += 1
        yield scrapy.Request(url='http://maoyan.com?offset=' + str(self.count * 30), callback=self.parse,
                             meta={'cookies': True})

    def parse_movie(self, response):
        Eng_name = response.css('div.celeInfo-right.clearfix > div.movie-brief-container > div::text').extract_first()
        title = response.meta.get('title')
        href = response.meta.get('href')
        self.logger.info('{} {} {}'.format(title, Eng_name, href))


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
