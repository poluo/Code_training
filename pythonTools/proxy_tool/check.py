import logging
import sys
from pymongo import MongoClient
import json
from validate import Validator
logging.basicConfig(format="%(asctime)s - %(levelname)s - %(message)s", level=logging.INFO)

def clean():
    logging.info('start clean')
    client = MongoClient('mongodb://poluo:poluo123@127.0.0.1:27017/proxy')
    db = client.proxy
    collection = db.proxy_list
    for one in collection.find():
        collection.remove(one)
    logging.info('db clean finish')
def db(result):
    logging.info('start insert')
    client = MongoClient('mongodb://poluo:poluo123@127.0.0.1:27017/proxy')
    db = client.proxy
    collection = db.proxy_list
    for one in result:
        collection.insert(one)
    logging.info('db insert finish')
def check():
    ip_all=[]
    with open('proxy.json','r',encoding='utf8') as fobj:
        for one in fobj:
            ip=json.loads(one)
            ip_all.append(ip)
    validator = Validator("https://www.douban.com/", 10, 4, 200)
    logging.info("Load proxy ip, total: %s", len(ip_all))
    result_tmp = validator.run(ip_all)
    result=[]
    for one in result_tmp:
        if one["speed"] > 8:
            pass
        else:
            result.append(one)
    logging.info("validator run finished")
    logging.info(len(result))
    result = sorted(result, key=lambda x: x["speed"])
    return  result

if __name__ == '__main__':
    result=check()
