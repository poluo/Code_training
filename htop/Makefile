objects = main.o linux_info.o draw.o socket.o

htop : $(objects)
	cc -o htop $(objects) -lcurses

main.o : main.c draw.h main.h linux_info.h socket.h
	cc -c main.c 
linux_info.o : linux_info.c main.h linux_info.h
	cc -c linux_info.c
draw.o : draw.c linux_info.h draw.h
	cc -c draw.c
scoket.o : scoket.c scoket.h
	cc -c socket.c

.PHONY : clean
clean :
	rm htop $(objects)
