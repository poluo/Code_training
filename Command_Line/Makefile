INC=-I/usr/include/python2.7

all:main.c cmd_list.c keyproc.c log.c  platform.c
	gcc $^ -o test -I/usr/include/python2.7 -lpython2.7

clean:
	rm -rf test