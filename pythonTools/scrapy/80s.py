import scrapy
import json


class MoviesSpider(scrapy.Spider):
    name = "80s_Movies_overall"
    tags = []
    base_url = 'http://www.80s.tw'
    length = 500
    # 电影 热门影片
    movie_list = []
    movie_count = 0
    ju_list = []
    ju_count = 0
    dm_list = []
    dm_count = 0
    zy_list = []
    zy_count = 0
    mv_list = []
    mv_count = 0
    # 短片 公开课
    other_list = []
    other_count = 0

    def start_requests(self):
        urls = [
            'http://www.80s.tw/',
        ]
        for url in urls:
            yield scrapy.Request(url=url, callback=self.parse)

    def parse(self, response):

        title = response.css('head > title::text')[0].extract()
        self.log('Title is %s' % title)
        self.parse_tags(response)
        for one_tag in self.tags:
            url = self.base_url + one_tag['link']
            yield scrapy.Request(response.urljoin(url), callback=self.parse_overall_info)

    def parse_tags(self, response):
        def get_tag():
            try:
                tag = one.css('a::text')[0].extract()
            except Exception:
                tag = one.css('a > span::text')[0].extract()
            return tag

        row_data = response.css('#nav > ul > li')
        ignored_value = ['/', '/zhuanti', '/top/last_update']
        for one in row_data:
            if one.css('a::attr(href)')[0].extract() in ignored_value:
                pass
            else:
                tmp_data = {
                    'link': one.css('a::attr(href)')[0].extract(),
                    'tag': get_tag()
                }
                self.tags.append(tmp_data)

    def parse_overall_info(self, response):
        # 电影 电视剧 动漫 综艺 公开课
        movie_set = response.css('body > div > div > div > ul.me1.clearfix > li')
        if len(movie_set) == 0:
            # 音乐 MV 视频短片
            movie_set = response.css('#block3 > div.clearfix.noborder.block1 > ul > li')
        if len(movie_set) == 0:
            # 热门影片
            movie_set = response.css('#block4_in > div')
        if len(movie_set) == 0:
            # 电影专题 最近更新
            pass
        for movie in movie_set:
            self.get_overall_info(movie)
        try:
            next_url = response.css('div.pager > a:nth-last-child(2)::attr(href)')[0].extract()
        except IndexError:
            next_url = None

        if next_url is not None:
            next_url = self.base_url + next_url
            self.log('another page')
            yield scrapy.Request(response.urljoin(next_url), callback=self.parse_overall_info)
        else:
            pass

    def closed(self, reason):
        self.export_last_info()
        print(reason)
        print("movie num={0} pages={1}".format(len(self.movie_list) + self.movie_count * self.length,
                                               self.movie_count + 1))
        print("mv num={0} pages={1}".format(len(self.mv_list) + self.mv_count * self.length, self.mv_count + 1))
        print("dm num={0} pages={1}".format(len(self.dm_list) + self.dm_count * self.length, self.dm_count + 1))
        print("ju num={0} pages={1}".format(len(self.ju_list) + self.ju_count * self.length, self.ju_count + 1))
        print("zy num={0} pages={1}".format(len(self.zy_list) + self.zy_count * self.length, self.zy_count + 1))
        print("other num={0} pages={1}".format(len(self.other_list) + self.other_count * self.length,
                                               self.other_count + 1))

    def export_last_info(self):
        with open('movie{0}.json'.format(self.movie_count), 'w') as fobj:
            json.dump(self.movie_list, fobj)

        with open('mv{0}.json'.format(self.mv_count), 'w') as fobj:
            json.dump(self.mv_list, fobj)

        with open('dm{0}.json'.format(self.dm_count), 'w') as fobj:
            json.dump(self.dm_list, fobj)

        with open('ju{0}.json'.format(self.ju_count), 'w') as fobj:
            json.dump(self.ju_list, fobj)

        with open('zy{0}.json'.format(self.zy_count), 'w') as fobj:
            json.dump(self.zy_list, fobj)

        with open('other{0}.json'.format(self.other_count), 'w') as fobj:
            json.dump(self.other_list, fobj)

    def get_overall_info(self, movie):
        tmp_data = {
            'name': movie.css('h3.h3 > a::text')[0].extract().strip(),
            'offset': movie.css('a::attr(href)')[0].extract(),
            'img_src': movie.css('a >img::attr(src)')[0].extract()
        }
        try:
            tmp_data['score'] = movie.css('a > span.poster_score::text')[0].extract()
        except IndexError:
            pass

        try:
            tmp_data['short_detail'] = movie.css('span.tip::text')[0].extract().strip()
        except IndexError:
            pass
        self.save_info(tmp_data)

    def save_info(self, tmp_data):
        info_type = tmp_data['offset']

        if 'movie' in info_type or 'hot' in info_type:
            self.movie_list.append(tmp_data)
            if len(self.movie_list) >= self.length:
                with open('movie{0}.json'.format(self.movie_count), 'w') as fobj:
                    json.dump(self.movie_list, fobj)
                self.movie_list = []
                self.movie_count += 1

        elif 'ju' in info_type:
            self.ju_list.append(tmp_data)
            if len(self.ju_list) >= self.length:
                with open('ju{0}.json'.format(self.ju_count), 'w') as fobj:
                    json.dump(self.ju_list, fobj)
                self.ju_list = []
                self.ju_count += 1

        elif 'dm' in info_type:
            self.dm_list.append(tmp_data)
            if len(self.dm_list) >= self.length:
                with open('dm{0}.json'.format(self.dm_count), 'w') as fobj:
                    json.dump(self.dm_list, fobj)
                self.dm_list = []
                self.dm_count += 1

        elif 'mv' in info_type:
            self.mv_list.append(tmp_data)
            if len(self.mv_list) >= self.length:
                with open('mv{0}.json'.format(self.mv_count), 'w') as fobj:
                    json.dump(self.mv_list, fobj)
                self.mv_list = []
                self.mv_count += 1

        elif 'zy' in info_type:
            self.zy_list.append(tmp_data)
            if len(self.zy_list) >= self.length:
                with open('zy{0}.json'.format(self.zy_count), 'w') as fobj:
                    json.dump(self.zy_list, fobj)
                self.zy_list = []
                self.zy_count += 1
        else:
            self.other_list.append(tmp_data)
            if len(self.other_list) >= self.length:
                with open('other{0}.json'.format(self.other_count), 'w') as fobj:
                    json.dump(self.other_list, fobj)
                self.other_list = []
                self.other_count += 1


if __name__ == '__main__':
    from scrapy.cmdline import execute
    execute()
