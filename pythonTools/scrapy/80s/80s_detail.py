import scrapy
import json


class MoviesSpider(scrapy.Spider):
    name = "80s_Movies_detail"
    result = []
    path = './info/'
    length = 490
    count = 0

    with open('./info/files.json', 'r') as fobj:
        file_list = json.load(fobj)

    def start_requests(self):
        tmp = 0
        for file_name in self.file_list:
            tmp += 1
            if tmp < 8:
                continue
            with open(self.path + file_name, 'r') as fobj:
                urls = json.load(fobj)
            for url in urls:
                url = "http://www.80s.tw" + url['offset']
                yield scrapy.Request(url=url, callback=self.parse)
            with open('{0}_result.json'.format(file_name[:file_name.find('.')]), 'w') as fobj:
                json.dump(self.result, fobj)
            self.result = []
            self.count += 1
            print(self.count)

    def closed(self, reason):
        print(reason)
        print(len(self.result))

    def parse(self, response):
        tmp_data = {}
        tmp_data['name'] = response.css('#minfo > div.info > h1::text')[0].extract().strip()
        tmp_data['img'] = response.css('#minfo > div.img > img::attr(src)')[0].extract().strip()
        try:
            tmp_data['short_description'] = response.css('#minfo > div.info > '
                                                         'span:nth-child(4)::text')[0].extract().strip()
        except IndexError:
            try:
                tmp_data['short_description'] = response.css('#minfo > div.info > span:nth-child(3)::text')[
                    0].extract().strip()
            except IndexError:

                tmp_data['short_description'] = response.css('#minfo > div.info > span:nth-child(5)::text')[0].extract().strip()
        try:
            tmp_data['long_description'] = response.xpath('//*[@id="movie_content"]/text()')[1].extract().strip()
            tmp = response.css('#minfo > div.info > span > a')
            actors = []
            for one in tmp:
                actors.append(one.xpath('text()')[0].extract())
            tmp_data['actors'] = actors
        except IndexError:
            pass
        info = response.css('#minfo > div.info > div > span.span_block')
        for one in info:
            try:
                tmp = one.css('a::text')[0].extract().strip()
            except IndexError:
                one.xpath('text()').extract()
                try:
                    tmp = one.xpath('text()')[-1].extract().strip()
                except IndexError:
                    print(one)
            try:
                tmp_data[one.css('span.font_888::text')[0].extract()] = tmp
            except IndexError:
                pass
        info = response.css('span.xunlei.dlbutton1')
        i = 1
        for one in info:
            tmp_data['download_link{0}'.format(i)] = one.css('a::attr(href)')[0].extract()
            i += 1
        print(tmp_data)
        self.result.append(tmp_data)


if __name__ == '__main__':
    from scrapy.cmdline import execute
    execute()
