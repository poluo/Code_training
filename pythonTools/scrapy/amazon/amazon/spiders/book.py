# -*- coding: utf-8 -*-
import scrapy
from amazon.items import AmazonItem


class BookSpider(scrapy.Spider):
    name = "book"
    allowed_domains = ["amazon.cn"]
    base_url = 'https://www.amazon.cn'
    books_count = 0
    valid_stytle = ['margin-left: 6px', 'margin-left: 14px', 'margin-left: 22px', 'margin-left: -2px']

    def start_requests(self):
        urls = [
            'https://www.amazon.cn/s/ref=lp_658390051_nr_n_1?fst=as%3Aoff&rh=n%3A658390051%2Cn%3A%21658391051%2Cn%3A658393051&bbn=658391051&ie=UTF8&qid=1490104448&rnid=658391051',
        ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        content_list = response.css('#refinements > div.categoryRefinementsSection > ul > li')
        next_link_list = []

        for one in content_list:
            style = one.css('::attr(style)').extract_first()
            if style in self.valid_stytle:
                link = one.css('a::attr(href)').extract_first()
                next_link_list.append(link)
                self.logger.debug(link)
                self.logger.debug(one.css('span.refinementLink::text').extract_first())
        if len(next_link_list) == 0:
            self.logger.debug('no deeper link,start crawl page')
            # self.parse_page(response) # why not work
            yield scrapy.Request(response.url, callback=self.parse_page, dont_filter=True)
        else:
            self.logger.debug(len(next_link_list))
            for one in next_link_list:
                self.logger.debug('go on deeper {}'.format(one))
                yield scrapy.Request(self.base_url + one, callback=self.parse)

    def parse_page(self, response):
        books_url = []
        tmp_list = response.css(
            'li.s-result-item.celwidget  > div > div > div > div.a-fixed-left-grid-col.a-col-right > div.a-row.a-spacing-small > div:nth-child(1) > a')
        for one in tmp_list:
            link = one.css('::attr(href)').extract_first()
            books_url.append(link)
            self.logger.debug('new book {}'.format(one.css('::attr(title)').extract_first()))
        for one in books_url:
            self.books_count += 1
            try:
                yield scrapy.Request(one, callback=self.parse_book)
            except ValueError:
                pass

        link = response.css('#pagnNextLink::attr(href)').extract_first()
        if link:
            self.logger.debug('next page {}'.format(link))
            yield scrapy.Request(self.base_url + link, callback=self.parse_page)

    def parse_book(self, response):
        my_item = AmazonItem()
        my_item['href'] = response.url
        try:
            my_item['name'] = response.css('#title > span:nth-child(1)::text').extract_first()
        except Exception as e:
            self.logger.warning('{} {}'.format(response.url, e))
            return None
        my_item['time'] = response.css('#title > span:nth-child(3)::text').extract_first()
        my_item['score'] = response.css('#acrPopover::attr(title)').extract_first()
        my_item['comment_num'] = response.css('#acrCustomerReviewText::text').extract_first()
        my_item['discount'] = response.css('#soldByThirdParty > span:nth-child(3)::text').extract_first()
        my_item['publisher'] = response.css(
            'td.bucket > div.content > ul > li:nth-child(1)').extract_first()
        tmp = response.css('#byline > span.author.notFaded')
        for one in tmp:
            flag = one.css('span.contribution > span::text').extract_first()
            if not flag:
                raise AttributeError
            elif '作者' in flag:
                my_item['author'] = one.css('a.a-link-normal::text').extract_first()
            elif '译者' in flag:
                my_item['translator'] = one.css('a.a-link-normal::text').extract_first()

        tmp = response.css('#tmmSwatches > ul > li.swatchElement.selected')
        my_item['price'] = ''
        for one in tmp:
            try:
                my_item['price'] += '{}:{} /'.format(
                    one.css('span > span > span > a > span::text').extract_first().strip(),
                    one.css('span > span > span > a > span > span::text').extract_first().strip())
            except AttributeError:
                pass
        return my_item

    def closed(self, reason):
        self.logger.info('books count = {}'.format(self.books_count))
        self.logger.info(reason)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
