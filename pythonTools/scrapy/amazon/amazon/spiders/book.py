# -*- coding: utf-8 -*-
from scrapy.spider import CrawlSpider, Rule
from scrapy.linkextractors import LinkExtractor
from amazon.items import AmazonItem


class BookSpider(CrawlSpider):
    name = "book"
    allowed_domains = ["amazon.cn"]
    start_urls = (
        'https://www.amazon.cn/%E5%9B%BE%E4%B9%A6/b?ie=UTF8&node=658390051',
    )
    contents_url = ('/s/ref=lp_\d{9}_nr_n.+',)
    books_url = ('/gp/product/.+', '/dp/.+')
    base_url = 'https://www.amazon.cn'
    rules = [
        # Rule(LinkExtractor(allow=contents_url), callback='parse_contents', follow=False),
        Rule(LinkExtractor(allow=books_url), callback='parse_book', follow=False),
    ]
    contents_count = 0
    books_count = 0

    def parse_contents(self, response):
        self.contents_count += 1

    def parse_book(self, response):
        self.books_count += 1
        my_item = AmazonItem()
        try:
            my_item['href'] = response.url
            my_item['name'] = response.css('#title > span:nth-child(1)::text').extract_first()
            my_item['time'] = response.css('#title > span:nth-child(3)::text').extract_first()
            my_item['score'] = response.css('#acrPopover::attr(title)').extract_first()
            my_item['comment_num'] = response.css('#acrCustomerReviewText::text').extract_first()
            my_item['discount'] = response.css('#soldByThirdParty > span:nth-child(3)::text').extract_first()
            my_item['publisher'] = response.css(
                'td.bucket > div.content > ul > li:nth-child(1)').extract_first()
            tmp = response.css('#byline > span')
            for one in tmp:
                flag = one.css('span.contribution > span::text').extract_first()
                if '作者' in flag:
                    my_item['author'] = one.css('a.a-link-normal::text').extract_first()
                elif '译者' in flag:
                    my_item['translator'] = one.css('a.a-link-normal::text').extract_first()
            tmp = response.css('#tmmSwatches > ul > li.swatchElement.selected')
            my_item['price'] = ''
            for one in tmp:
                my_item['price'] += '{}:{} /'.format(one.css('span > span > span > a > span::text').extract_first().strip(),
                                                  one.css('span > span > span > a > span > span::text').extract_first().strip())

            self.logger.debug(my_item)
        except Exception as e:
            self.logger.warning(e)
        else:
            pass
        finally:
            pass

    def closed(self, reason):
        self.logger.info('content count = {}'.format(self.contents_count))
        self.logger.info('books count = {}'.format(self.books_count))
        self.logger.info(reason)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
