# -*- coding: utf-8 -*-
import scrapy
from taobao.items import GoodsItem


class DemoSpider(scrapy.Spider):
    name = "demo"
    allowed_domains = ["taobao.com"]
    start_urls = ['https://www.taobao.com/']

    def parse(self, response):
        selector = 'div.search-combobox > div.search-combobox-input-wrap > input'
        content = 'SSD'
        search_key = response.css(selector).extract_first()
        if search_key:
            self.logger.info('Found search key')
        yield scrapy.Request(url=response.url, callback=self.parse_content,
                             meta={'send_keyword': 1, 'content': content, 'selector': selector, 'selenium': 1})

    def parse_content(self, response):
        my_goods = GoodsItem()
        goods_list = response.css('#mainsrp-itemlist > div > div > div:nth-child(1) > div')
        for goods in goods_list:
            name = goods.css('div.row.row-2.title > a').extract_first()
            my_goods['name'] = name[name.find('</span>') + 7:name.find('</a>')].strip().replace('<span class="H">','').replace(
                '</span>', '')
            my_goods['price'] = goods.css(
                'div.row.row-1.g-clearfix > div.price.g_price.g_price-highlight > strong::text').extract_first()
            my_goods['sales'] = goods.css('div.row.row-1.g-clearfix > div.deal-cnt::text').extract_first()
            my_goods['shop_name'] = goods.css(
                'div.row.row-3.g-clearfix > div.shop > a > span:nth-child(2)::text').extract_first()
            my_goods['shop_url'] = goods.css('div.row.row-3.g-clearfix > div.shop > a::attr(href)').extract_first()
            self.logger.info(my_goods)
            yield my_goods
        next_page = '#mainsrp-pager > div > div > div > ul > li.item.next > a'
        if next_page:
            print('next page')
            yield scrapy.Request(url=response.url, callback=self.parse_content,
                                 meta={'click': 1, 'selector': next_page, 'selenium': 1})

if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
