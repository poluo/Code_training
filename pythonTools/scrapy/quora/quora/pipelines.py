# -*- coding: utf-8 -*-

# Define your item pipelines here
#
# Don't forget to add your pipeline to the ITEM_PIPELINES setting
# See: http://doc.scrapy.org/en/latest/topics/item-pipeline.html
import json
import pymongo
import logging as logger
class FollowerPipeline(object):
    def open_spider(self, spider):
        url = 'mongodb://poluo:poluo123@115.28.36.253:27017/proxy'
        self.client = pymongo.MongoClient(url)
        self.db = self.client.proxy
        self.collection = self.db.quora_info

    def process_item(self, item, spider):
        self.collection.insert(dict(item))

    def close_spider(self, spider):
        self.client.close()
