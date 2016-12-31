#!/usr/bin/python
# -*- coding: UTF-8 -*-

# **********************************************************
# * Author        : poluo
# * Email         : xxx@email.com
# * Create time   : 2016-12-30 11:26
# * Last modified : 2016-12-30 11:26
# * Filename      : test.py
# * Description   : 
# **********************************************************
from pymongo import *
client = MongoClient()
client = MongoClient("localhost",27017)

db = client.movie_datebase
collection = db.movie_info

def clear_db():
	res=collection.find()
	for i in res:
	    print(i)

def get_info_by_name(name):
	res=collection.find({'name':name})
	print('get {0} records'.format(res.count()))
	for i in res:
		print(i)

def get_info_by_score(score):
	#lt lower than
	#gt lower than
	res=collection.find({'score':{"$lt":score}}).sort('name')
	print('get {0} records'.format(res.count()))
	for i in res:
		print(i)
if __name__ == '__main__':
	get_info_by_name('秒速五厘米')
	get_info_by_score('6.3')