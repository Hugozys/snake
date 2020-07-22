CXXFLAGS = -std=gnu++11 -Wall -Werror -pedantic
DFLAGS = -MMD
CC = g++
DEBUG = -ggdb3
LIBS = -lncurses -ltinfo -lmenu
SRCS = $(wildcard *.cc)
OBJS = $(patsubst %.cc, %.o, $(SRCS))

snake: $(OBJS)
	$(CC) $^ -o $@ $(LIBS)

%.o: %.cc
	$(CC) $(CXXFLAGS) $(DEBUG) -c $< $(DFLAGS) -o $@

.PHONY: clean

-include *.d

clean:
	rm -f *~ snake *.o *.d log* UNKNOWN.INFO
