# -*- coding: utf-8 -*-

# Define here the models for your scraped items
#
# See documentation in:
# http://doc.scrapy.org/en/latest/topics/items.html

import scrapy


class AirbnbItem(scrapy.Item):

    name = scrapy.Field()
    id = scrapy.Field()
    # equipment = scrapy.Field()
    # img = scrapy.Field()
    owner = scrapy.Field()
    owner_id = scrapy.Field()
    price = scrapy.Field()
