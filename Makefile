SRC := $(wildcard *.cc)
EXECUTABLES := $(SRC:.cc=.x)

all: $(EXECUTABLES)

%.x: %.cc
	g++ -O3 -o $@ $<

clean:
	rm -f *.x

.PHONY: all clean