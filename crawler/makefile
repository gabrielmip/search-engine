UNAME_S := $(shell uname -s)
TOP := $(shell pwd)
ifeq ($(UNAME_S),Linux)
    FLAGS += $(TOP)/chilkat/lib/libchilkat.so
endif
ifeq ($(UNAME_S),Darwin)
    FLAGS += chilkat/lib/libchilkat.a
endif

crawler: main.o
	g++ -std=c++11 main.o $(FLAGS) -o crawler

main.o: main.cpp chilkat/include/CkSpider.h
	g++ -std=c++11 -c main.cpp

clean:
	rm *.o crawler