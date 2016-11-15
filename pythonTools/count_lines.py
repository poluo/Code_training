import sys
import os
import re
def count_lines(path=os.getcwd()):
    mydir=path+os.sep
    print(mydir)
    lines=0
    sums=0
    with open('debug.log','w+') as fobj:
        fobj.write('Debug info:'+'\n')
        fobj.write('Print all files in current dir:'+'\n')
        for root,dirs,files in os.walk(mydir):
             for adir in dirs:
                 pass
                 #fobj.write(os.path.join(root,adir)+'\n')
             for file in files:
                 if '.c' in file or '.h' in file or '.py' in file:
                     
                     try:
                         with open(os.path.join(root,file),'rb') as f:
                             for i in f:
                                 lines=lines+1
                         fobj.write(os.path.join(root,file)+'  '+str(lines)+'\n')
                         sums=sums+lines
                         lines=0
                     except FileNotFoundError:
                         print(file)
                
        fobj.write('Print Over!!!'+'\n\n\n')
    print(sums)


if __name__=='__main__':
    count_lines()
