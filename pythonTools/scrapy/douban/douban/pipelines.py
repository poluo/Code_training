# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

import json


class DoubanPipeline(object):
    def open_spider(self, spider):
        self.actress_count = 0
        self.actress_num = 0
        self.movie_count = 0
        self.movie_num = 0
        self.fobj_movie = open('movie_{}.json'.format(self.movie_count), 'w')
        self.fobj_actress = open('actress_{}.json'.format(self.actress_count), 'w')
        self.fobj_other = open('other.json','w')

    def process_item(self, item, spider):
        line = json.dumps(dict(item)) + "\n"
        if 'subject' in item['url']:
            self.movie_num += 1
            if self.movie_num > 1000:
                self.fobj_movie.close()
                self.movie_count += 1
                self.fobj_movie = open('movie_{}.json'.format(self.movie_count), 'w')
            self.fobj_movie.write(line)
        elif 'celebrity' in item['url']:
            self.actress_num += 1
            if self.actress_num > 1000:
                self.fobj_actress.close()
                self.actress_count += 1
                self.fobj_actress = open('actress_{}.json'.format(self.actress_count), 'w')
            self.fobj_actress.write(line)
        else:
            self.fobj_other.write(line)


    def colse_spider(self, spider):
        self.fobj_movie.close()
        self.fobj_actress.close()
        self.fobj_other.close()
