from validate import Validator
import requests
import pymongo
import time

class Proxy(object):

    def __init__(self):
        self.client = pymongo.MongoClient('mongodb://poluo:poluo123@115.28.36.253:27017/proxy')
        self.db = self.client.proxy
        self.collection = self.db.proxy_list
        self.validate = Validator('https://movie.douban.com',10,2,10)
        self.run_count = 1
        self.threadhold = 10
        self.cycle_time = 60 #seconds

    def get_proxy(self):
            tid = '555947027942665'
            num = 50
            url = 'http://tvp.daxiangdaili.com/ip/?tid={}&num={}&category=2&delay=5&protocol=https&ports=80,8080,3128'.format(tid, num)
            ip_all = []
            result = requests.get(url)
            result = result.text.split('\n')
            for one in result:
                if one != '':
                    ip = {
                        'ip': one.split(':')[0].strip(),
                        'port': one.split(':')[1].strip()
                    }
                    ip_all.append(ip)
            if len(ip_all) == 0:
                print('NO PROXY AVAILABLE')
            else:
                print('update proxy')
            return ip_all

    def insert(self,result):
        for i in result:
            self.collection.insert(i)
            print(i) 
    def get_length(self):
        count = 0
        for one in self.collection.find():
            count += 1
        return count
        
    def run(self):
        while self.run_count:
            self.run_count -= 1
            start = time.time()
            while self.get_length() < self.threadhold:
                ip_all = self.get_proxy()
                tmp=self.validate.run(ip_all)
                result = []
                for one in tmp:
                    if one['speed'] <10:
                        result.append(one)
                if len(result):
                    self.insert(result)
                    break
                else:
                    print('no valid')
            time.sleep(self.cycle_time-(time.time()-start))

if __name__ == '__main__':
    my_proxy=Proxy()
    my_proxy.run()
