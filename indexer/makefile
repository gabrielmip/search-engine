OBJ_DIR=./bin
SRC_DIR=./src
FLAGS=-std=c++11 -Wall -g -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx

all: prep build

# build: indexer search
build: indexer

# search:
# 	g++ -c $(SRC_DIR)/search.cpp $(FLAGS) -o $(OBJ_DIR)/search.o
# 	g++ $(OBJ_DIR)/search.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/file_iterator.o $(FLAGS) -o search

indexer: utils file_iterator run_iterator
	g++ -c $(SRC_DIR)/indexer.cpp $(FLAGS) -o $(OBJ_DIR)/indexer.o
	g++ $(OBJ_DIR)/indexer.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/file_iterator.o $(OBJ_DIR)/run_iterator.o $(FLAGS) -o indexer

utils:
	g++ -c $(SRC_DIR)/utils.cpp $(FLAGS) -o $(OBJ_DIR)/utils.o

file_iterator:
	g++ -c $(SRC_DIR)/file_iterator.cpp $(FLAGS) -o $(OBJ_DIR)/file_iterator.o

run_iterator:
	g++ -c $(SRC_DIR)/run_iterator.cpp $(FLAGS) -o $(OBJ_DIR)/run_iterator.o

prep:
	clear
	mkdir -p $(OBJ_DIR)
	rm -R data/runs
	rm -R data/merge
	mkdir -p data/docs
	mkdir -p data/runs
	mkdir -p data/merge
	mkdir -p data/index

clean:
	rm $(OBJ_DIR)/*.o indexer
