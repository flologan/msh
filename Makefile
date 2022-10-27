cc 		= gcc
cflags 	= -Wall
objs 	= main.o msh.o helpers.o
bin 	= msh

all: $(bin)

msh: $(objs)
	$(cc) $(cflags) $(objs) -o $(bin)

%.o: %.c
	$(cc) $(cflags) -c $< -o $@

clean:
	rm $(bin) $(objs)
