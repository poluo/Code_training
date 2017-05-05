import sys
import os
import re
def count_lines(path=os.getcwd()):
    mydir=path+os.sep
    print(mydir)
    lines=0
    comment_line = 0
    blank_line = 0
    sums=0
    with open('debug.log','w+') as fobj:
        fobj.write('Debug info:'+'\n')
        fobj.write('Print all files in current dir:'+'\n')
        for root,dirs,files in os.walk(mydir):
             for adir in dirs:
                 pass
                 #fobj.write(os.path.join(root,adir)+'\n')
             for file in files:
                 if '.py' in file:
                     try:
                         with open(os.path.join(root,file),'r') as f:
                             for i in f:
                                lines += 1
                                if i.strip() == '':
                                    print('space',lines,file)
                                    blank_line += 1
                                elif i.strip()[0] == '#':
                                    comment_line += 1
                                    print('comment',lines,file)
                         fobj.write(os.path.join(root,file)+'lines ={} blank= {} comment={}'.format(lines,blank_line,comment_line)+'\n')
                         sums=sums+lines
                         lines=0
                     except FileNotFoundError:
                         print(file)
                
        fobj.write('Print Over!!!'+'\n\n\n')
    print(sums)


if __name__=='__main__':
    count_lines()
