import scrapy
import json


class NeteaseSpider(scrapy.Spider):
    name = "netease"
    data = [] 
    
    def start_requests(self):
        with open('./info/result_0.json') as fobj:
            tmp = json.load(fobj)
        urls = []
        head = "http://music.163.com"
        for one in tmp:
            urls.append(head + one['href'])
        self.log(len(urls))
        urls = urls[:50]

        for url in urls:
            yield scrapy.Request(url=url+'ajax', callback=self.parse)

    def parse(self, response):
        element = response.css("#song-list-pre-cache > div > div > table > tbody > tr")
        for one in element:
            try:
                tmp_a = one.css('span.txt > a')
                tmp_span = one.css('td:nth-of-type(4) > div > span > a')
                tmp_div = one.css('td:nth-of-type(5) > div > a')
                temp_data = {
                    'song_id': tmp_a.css('::attr(href)')[0].extract(),
                    'song_name': tmp_a.css('b::text')[0].extract(),
                    'song_length': one.css('span.u-dur::text')[0].extract(),
                    'singer_name': tmp_span.css('::text')[0].extract(),
                    'singer_id': tmp_span.css('::attr(href)')[0].extract(),
                    'album_name': tmp_div.css('::text')[0].extract(),
                    'album_id': tmp_div.css('::attr(href)')[0].extract()
                }
                self.data.append(temp_data)
                print(temp_data)
            except IndexError:
                pass
            break

    def closed(self, reason):
        self.log(reason)

if __name__ == '__main__':
    from scrapy.cmdline import execute
    execute()
