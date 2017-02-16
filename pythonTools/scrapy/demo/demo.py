import scrapy


class QuotesSpider(scrapy.Spider):
    name = "quotes"
    count = 0
    authors = []

    def start_requests(self):
        urls = [
            'http://quotes.toscrape.com/page/1/',
        ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        self.count += 1
        page = response.url.split("/")[-2]
        self.log('Saved file %s' % page)
        title = response.css('title::text')[0].extract()
        # response.css('title::text').re(r'Q\w+')
        # title = response.xpath('/html/head/title/text()')[0].extract()
        self.log('Title is %s' % title)
        row_data = response.css('body > div > div:nth-child(2) > div.col-md-8 > div.quote')
        for one in row_data:
            yield {
                'quote': one.css('span.text::text').extract(),
                'author': one.css('small.author::text').extract()
            }
        for author in response.css('div.quote '
                                   '> span:nth-child(2) > a::attr(href)').extract():
            author = 'http://quotes.toscrape.com' + author
            yield scrapy.Request(response.urljoin(author), callback=self.parse_author)
        next_url = response.css('body > div > div:nth-child(2) > div.col-md-8 > nav > ul '
                                '> li.next > a::attr(href)')[0].extract()
        if next_url is not None and self.count < 10:
            next_url = response.urljoin(next_url)
            yield scrapy.Request(next_url, callback=self.parse)

    def parse_author(self, response):
        yield {
            'name': response.css('body > div > div.author-details > h3::text')[0].extract(),
            'Born_data': response.css('body > div > div.author-details > p:nth-child(2) > '
                                      'span.author-born-date::text')[0].extract(),
            'Born_location': response.css('body > div > div.author-details > p:nth-child(2) >'
                                          ' span.author-born-location::text')[0].extract(),
            'Description': response.css('body > div > div.author-details > div::text')[0].extract()
        }


if __name__ == '__main__':
    from scrapy.cmdline import execute
    execute()
