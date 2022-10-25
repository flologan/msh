cc = gcc
cflags = -Wall
tgts = msh main.o msh.o helpers.o

msh: main.o msh.o helpers.o
	$(cc) $(cflags) main.o msh.o helpers.o -o msh

main.o: main.c msh.h helpers.h
	$(cc) -c main.c

msh.o: msh.c msh.h helpers.h
	$(cc) -c msh.c

helpers.o: helpers.c msh.h helpers.h
	$(cc) -c helpers.c

clean:
	rm $(tgts)
