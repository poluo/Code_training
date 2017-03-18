# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import json
from scrapy.exceptions import DropItem


class JasonAmazonPipeline(object):
    def open_spider(self, spider):
        self.file = open('book.json', 'w')
        self.used_list = []

    def process_item(self, item, spider):
        if item['href'] not in self.used_list:
            line = json.dumps(dict(item)) + "\n"
            self.file.write(line)
            self.used_list.append(item['href'])
        else:
            raise DropItem("already in list: %s" % item)

    def close_spider(self, spider):
        self.file.close()
