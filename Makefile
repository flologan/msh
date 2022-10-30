# to build, type `make`
# to clean, type `make clean`

cc 		= gcc
cflags 	= -Wall
objs 	= main.o msh.o helpers.o
bin 	= msh

all: $(bin)

$(bin): $(objs)
	$(cc) $(cflags) $(objs) -o $@

%.o: %.c
	$(cc) $(cflags) -c $< -o $@

clean:
	rm -f $(bin) $(objs)
