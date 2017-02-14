import scrapy


class NeteaseSpider(scrapy.Spider):
    name = "Netease_Music_first"
    url_list = []
    playlists_overall_info = []

    def start_requests(self):
        urls = [
            'http://music.163.com/discover/playlist'
        ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):
        order_new_head = "http://music.163.com/discover/playlist/?order=hot&"
        order_hot_head = "http://music.163.com/discover/playlist/?order=new&"
        base_tail = "&limit=35&offset=0"

        raw_data = response.css("#cateListBox > div.bd > dl")
        for one in raw_data:
            links = one.css('dd > a::attr(href)').extract()
            for link in links:
                link = link[link.find('?') + 1:]
                hot_url = order_hot_head + link + base_tail
                new_url = order_new_head + link + base_tail
                self.url_list.append(hot_url)
                self.url_list.append(new_url)

        for url in self.url_list:
            yield scrapy.Request(response.urljoin(url), callback=self.parse_overall_info)
            break

    def closed(self, reason):
        print(self.url_list)
        print(reason)

    def parse_overall_info(self, response):
        playlists_row_data = response.css('ul > li')
        for one in playlists_row_data:
            try:
                tmp = {
                    "img": one.css('div.u-cover.u-cover-1 > img::attr(src)')[0].extract(),
                    "title": one.css('div.u-cover.u-cover-1 > a::attr(title)')[0].extract(),
                    "href": one.css('div.u-cover.u-cover-1 > a::attr(href)')[0].extract(),
                    "play_num": one.css('div.u-cover.u-cover-1 > div.bottom > span.nb::text')[0].extract(),
                }
            except IndexError:
                continue
            try:
                tmp["author"] = one.css('p:nth-of-type(2) > a::text')[0].extract()
            except Exception as e:
                self.log(e)
                pass
            self.playlists_overall_info.append(tmp)

        try:
            next_url = response.css('#m-pl-pager > div > a::attr(href)')[-1].extract()
        except IndexError:
            print("IndexError")
            next_url = None

        print(next_url)

        if next_url is not None:
            next_url = 'http://music.163.com/' + next_url
            self.log(next_url)
            yield scrapy.Request(response.urljoin(next_url), callback=self.parse_overall_info)
        else:
            pass


if __name__ == '__main__':
    from scrapy.cmdline import execute
    execute()