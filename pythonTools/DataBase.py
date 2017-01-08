from pymongo import *

class DB_operation(object):
    """docstring for DB_operation"""
    def __init__(self, arg):
        self.collection = arg
    def clear(self):
        res = self.collection.find()
        for one in res:
            self.collection.remove(one)
    def show_all(self):
        res = self.collection.find()
        for one in res:
            print(one)
    def find(self):
        res = self.collection.find()
        return res
    def insert(self,arg):
        self.collection.insert(arg)
    def remove(self,arg):
        self.collection.remove(arg)

class DB_movie(object):
    """docstring for DB_movie"""
    def __init__(self):
        client = MongoClient()
        client = MongoClient('localhost',27017)
        db = client.database
        collection = db.collection
        self.operator=DB_operation(collection)

    

class DB_proxy(object):
    """docstring for DB"""
    def __init__(self):
        client = MongoClient()
        client = MongoClient('localhost',27017)
        db = client.proxies
        collection = db.proxies
        self.operator=DB_operation(collection)

if __name__ == '__main__':
    test=DB_movie()
    test.operator.show_all()
    

        
    
