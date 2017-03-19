# -*- coding: utf-8 -*-
from scrapy.spider import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor
from amazon.items import AmazonItem
from bs4 import BeautifulSoup


class BookSpider(CrawlSpider):
    name = "book"
    allowed_domains = ["amazon.cn"]
    redis_key = 'book:start_urls'
    start_urls = (
        'https://www.amazon.cn/%E5%9B%BE%E4%B9%A6/b/ref=sa_menu_top_books_l1?ie=UTF8&node=658390051',
    )
    contents_url = ('/s/ref=lp_\d{9}_nr_n.+', '/s/ref=lp_\d{9}_pg_\d.+')
    books_url = ('/gp/product/.+', '.*/dp/.+')
    base_url = 'https://www.amazon.cn'
    rules = [
        Rule(LinkExtractor(allow=contents_url), callback='parse_contents', follow=True),
        Rule(LinkExtractor(allow=books_url, deny='.+/uedata/unsticky/.+'), callback='parse_book', follow=True),
    ]
    contents_count = 0
    books_count = 0

    def parse_contents(self, response):
        self.contents_count += 1

    def parse_book(self, response):
        self.books_count += 1
        yield self.parse_with_scrapy(response)

    def parse_with_bs4(self, response):
        my_item = AmazonItem()
        my_item['href'] = response.url
        my_soup = BeautifulSoup(response.text, 'lxml')
        try:
            my_item['name'] = my_soup.select('#title > span:nth-of-type(1)')
        except Exception as e:
            raise e
        my_item['time'] = my_soup.select('#title > span:nth-of-type(3)')
        my_item['score'] = my_soup.select('#acrPopover')
        my_item['comment_num'] = my_soup.select('#acrCustomerReviewText')
        my_item['discount'] = my_soup.select('#soldByThirdParty > span:nth-of-type(3)')
        my_item['publisher'] = my_soup.select(
            'td.bucket > div.content > ul > li:nth-of-type(1)')
        tmp = my_soup.select('#byline > span.author.notFaded')
        for one in tmp:
            flag = one.select('span.contribution > span')
            if not flag:
                self.logger.warning('{}'.format(response.url))
                raise AttributeError
            elif '作者' in flag:
                my_item['author'] = one.select('a.a-link-normal')
            elif '译者' in flag:
                my_item['translator'] = one.select('a.a-link-normal')

        tmp = my_soup.select('#tmmSwatches > ul > li.swatchElement.selected')
        my_item['price'] = ''
        for one in tmp:
            my_item['price'] += '{}:{} /'.format(
                one.select('span > span > span > a > span'),
                one.select('span > span > span > a > span > span'))
        return my_item

    def parse_with_scrapy(self, response):
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
            my_item['price'] += '{}:{} /'.format(
                one.css('span > span > span > a > span::text').extract_first().strip(),
                one.css('span > span > span > a > span > span::text').extract_first().strip())
        return my_item

    def closed(self, reason):
        self.logger.info('content count = {}'.format(self.contents_count))
        self.logger.info('books count = {}'.format(self.books_count))
        self.logger.info(reason)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
