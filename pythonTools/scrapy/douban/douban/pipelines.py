# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html

import json


class DoubanPipeline(object):
    def open_spider(self, spider):
        self.fobj = open('data.json', 'w')

    def process_item(self, item, spider):
        line = json.dumps(dict(item)) + "\n"
        self.fobj.write(line)

    def colse_spider(self, spider):
        self.fobj.close()
