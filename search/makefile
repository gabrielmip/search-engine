OBJ_DIR=./bin
SRC_DIR=./src
FLAGS=-std=c++11 -Wall -g -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx `pkg-config --libs --cflags icu-uc icu-io`

all: prep build pagerank

build: search

pagerank:
	g++ $(SRC_DIR)/pagerank.cpp $(SRC_DIR)/graph.cpp $(FLAGS) -o pagerank

search: utils unigram # anchor
	g++ -c $(SRC_DIR)/search.cpp $(FLAGS) -o $(OBJ_DIR)/search.o
	g++ $(OBJ_DIR)/search.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/unigram_index.o $(FLAGS) -o search

utils:
	g++ -c $(SRC_DIR)/utils.cpp $(FLAGS) -o $(OBJ_DIR)/utils.o

unigram:
	g++ -c $(SRC_DIR)/unigram_index.cpp $(FLAGS) -o $(OBJ_DIR)/unigram_index.o

anchor:
	g++ -c $(SRC_DIR)/anchor_index.cpp $(FLAGS) -o $(OBJ_DIR)/anchor_index.o

prep:
	clear
	mkdir -p $(OBJ_DIR)
	mkdir -p logs

clean:
	rm $(OBJ_DIR)/*.o search
