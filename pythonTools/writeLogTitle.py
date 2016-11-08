import sys
import os
def writeLogTitle(path=os.getcwd()):
    print(path)
    os.chdir(path)
    if os.path.exists('debug.log'):
        with open('debug.log','r') as fobj:
            firstline=fobj.readline()
            if "Debug info:" in firstline:
                is_should_write=False
            else:
                is_should_write=True
                
    else:
        is_should_write=True
    if is_should_write:
        mydir=path+os.sep
        with open('debug.log','w+') as fobj:
            fobj.write('Debug info:'+'\n')
            fobj.write('Print all files in current dir:'+'\n')
            for root,dirs,files in os.walk(mydir):
                for adir in dirs:
                    fobj.write(os.path.join(root,adir)+'\n')
                for file in files:
                    fobj.write(os.path.join(root,file)+'\n')
            fobj.write('Print Over!!!'+'\n\n\n')

        
       
    
