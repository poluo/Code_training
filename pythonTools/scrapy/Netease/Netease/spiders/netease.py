import scrapy
import json
from bs4 import BeautifulSoup


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
        urls = urls[:30]

        for url in urls:
            yield scrapy.Request(url=url + 'proxy', callback=self.parse)

    def parse(self, response):
        soup = BeautifulSoup(response.text, 'lxml')
        raw_data = soup.find('ul', {'class': 'f-hide'})
        for one in raw_data.find_all('a'):
            try:
                temp_data = {
                    'song_id': one['href'],
                    'song_name': one.text,
                }
                self.data.append(temp_data)
            except IndexError:
                pass

    def closed(self, reason):
        print(len(self.data))
        self.log(self.data)


if __name__ == '__main__':
    from scrapy.cmdline import execute

    execute()
