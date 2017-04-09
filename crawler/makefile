OBJ_DIR=./bin
SRC_DIR=./src
FLAGS=-std=c++11 -Wall -lpthread -lresolv
UNAME_S := $(shell uname -s)
TOP := $(shell pwd)
ifeq ($(UNAME_S),Linux)
    FLAGS += $(TOP)/src/chilkat/lib/libchilkat.so
endif
ifeq ($(UNAME_S),Darwin)
    FLAGS += src/chilkat/lib/libchilkat.a
endif

all: prep build

build: main crawler scheduler
	g++ $(OBJ_DIR)/main.o $(OBJ_DIR)/crawler.o $(OBJ_DIR)/scheduler.o $(FLAGS) -o crawler

main: crawler
	g++ -c $(SRC_DIR)/main.cpp $(FLAGS) -o $(OBJ_DIR)/main.o

crawler: scheduler
	g++ -c $(SRC_DIR)/crawler.cpp $(FLAGS) -o $(OBJ_DIR)/crawler.o

scheduler:
	g++ -c $(SRC_DIR)/scheduler.cpp $(FLAGS) -o $(OBJ_DIR)/scheduler.o

prep:
	clear
	mkdir -p $(OBJ_DIR)
	mkdir -p ./documents

clean:
	rm $(OBJ_DIR)/*.o crawler