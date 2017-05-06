# -*- coding: utf-8 -*-
import scrapy


class UserSpider(scrapy.Spider):
    name = "user"
    allowed_domains = ["reddit.com"]
    start_urls = ['https://www.reddit.com/user/athleticthighs']

    def parse(self, response):
       site_table = response.css('#siteTable > div')
       for one in site_table:
          data_type = one.css('::attr(data-type)').extract_first()
          if data_type == 'link':
            url = one.css('::attr(data-url)').extract_first()
            title = one.css('div.entry.unvoted > p.title > a::text').extract_first()
            time = one.css('div.entry.unvoted > p.tagline > time::attr(datetime)').extract_first()
            num = one.css('div.midcol.unvoted > div.score.unvoted::text').extract_first()
            tag = one.css('div.entry.unvoted > p.tagline > a::attr(href)').extract()[-1]
            data = {'type':data_type,'url':url,'title':title,'num':num,'tag':tag,'time':time}
            self.logger.info('Got data {}'.format(data))
          elif data_type == 'comment':
            tmp = one.css('p.parent > a.title')
            url = tmp.css('::attr(href)').extract_first()
            title = tmp.css('::text').extract_first()
            tag = one.css('p.parent > a.subreddit.hover::attr(href)').extract()[-1]
            time = one.css('div.entry.unvoted > p > time::attr(datetime)').extract_first()
            comment = one.css('div.usertext-body.may-blank-within.md-container > div.md > p::text').extract()
            num = one.css('div.midcol.unvoted > div:nth-child(1)::text').extract_first()
            data = {'type':data_type,'url':url,'title':title,'num':num,'tag':tag,'time':time,'comment':comment}
            self.logger.info('Got data {}'.format(data))
          else:
            pass
