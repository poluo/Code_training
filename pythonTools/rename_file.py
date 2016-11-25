import sys
import os
import re
def my_rename(path=os.getcwd()):
    mydir=path+os.sep
    print(mydir)
    with open('debug.log','w+') as fobj:
        fobj.write('Debug info:'+'\n')
        fobj.write('Print all files in current dir:'+'\n')
        for root,dirs,files in os.walk(mydir):
            for adir in dirs:
                pass
                 #fobj.write(os.path.join(root,adir)+'\n')
            for file in files:
                if '.mp3' in file and '-' in file:
                    try:
                        index=file.index('-')
                        new_name=file[0:5].strip()+".mp3"
                        try:
                        	os.renames(file,new_name)
                        	fobj.write(file+'renamed to '+new_name+'\n')
                        except FileExistsError as e:
                        	fobj.write(new_name+' exists error,delete '+file+'\n')
                        	os.remove(file)
                    except FileNotFoundError:
                        fobj.write(file+"not found error")
                
        fobj.write('Process Over!!!'+'\n\n\n')
    


if __name__=='__main__':
    my_rename()
