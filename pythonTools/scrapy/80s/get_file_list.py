import os
import re
import json
def get_file_name(path=os.getcwd()):
    mydir=path+os.sep
    res=[]
    for root,dirs,files in os.walk(mydir):
        for adir in dirs:
            pass
        for file in files:
            res.append(file)
    with open('files.json','w') as fobj:
        json.dump(res,fobj)

if __name__ == '__main__':
    get_file_name()