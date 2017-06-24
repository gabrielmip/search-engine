OBJ_DIR=./bin
SRC_DIR=./src
FLAGS=-std=c++11 -Wall -g -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx `pkg-config --libs --cflags icu-uc icu-io`

all: prep build

build: indexer search pagerank

pagerank:
	g++ $(SRC_DIR)/pagerank.cpp $(SRC_DIR)/graph.cpp -o pagerank

search:
	g++ $(SRC_DIR)/search.cpp $(FLAGS) -o search

indexer: utils file_iterator run_iterator rank_run_iterator
	g++ -c $(SRC_DIR)/indexer.cpp $(FLAGS) -o $(OBJ_DIR)/indexer.o
	g++ $(OBJ_DIR)/indexer.o $(OBJ_DIR)/utils.o $(OBJ_DIR)/file_iterator.o $(OBJ_DIR)/run_iterator.o $(OBJ_DIR)/rank_run_iterator.o $(FLAGS) -o indexer

utils:
	g++ -c $(SRC_DIR)/utils.cpp $(FLAGS) -o $(OBJ_DIR)/utils.o

file_iterator:
	g++ -c $(SRC_DIR)/file_iterator.cpp $(FLAGS) -o $(OBJ_DIR)/file_iterator.o

run_iterator:
	g++ -c $(SRC_DIR)/run_iterator.cpp $(FLAGS) -o $(OBJ_DIR)/run_iterator.o

rank_run_iterator:
	g++ -c $(SRC_DIR)/rank_run_iterator.cpp $(FLAGS) -o $(OBJ_DIR)/rank_run_iterator.o

prep:
	clear
	mkdir -p $(OBJ_DIR)
	if [[ -d data/runs ]]; then rm -R data/runs; fi;
	if [[ -d data/runs_pagerank ]]; then rm -R data/runs_pagerank; fi;
	if [[ -d data/runs_anchortext ]]; then rm -R data/runs_anchortext; fi;
	rm -R data/merge
	mkdir -p data/docs
	mkdir -p data/runs
	mkdir -p data/runs_pagerank
	mkdir -p data/runs_anchortext
	mkdir -p data/merge
	mkdir -p data/index
	mkdir -p logs

clean:
	rm $(OBJ_DIR)/*.o indexer search pagerank
