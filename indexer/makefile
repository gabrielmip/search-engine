OBJ_DIR=./bin
SRC_DIR=./src
FLAGS=-std=c++11 -Wall -g -I /usr/local/include/htmlcxx -L/usr/local/lib -lhtmlcxx

all: prep build

build: main
  g++ $(OBJ_DIR)/main.o $(OBJ_DIR)/utils.o $(FLAGS) -o indexer
  # g++ $(OBJ_DIR)/main.o $(OBJ_DIR)/crawler.o $(OBJ_DIR)/scheduler.o $(OBJ_DIR)/utils.o $(FLAGS) -o crawler

main: utils
  g++ -c $(SRC_DIR)/main.cpp $(FLAGS) -o $(OBJ_DIR)/main.o

utils:
  g++ -c $(SRC_DIR)/utils.cpp $(FLAGS) -o $(OBJ_DIR)/utils.o

prep:
  clear
  mkdir -p $(OBJ_DIR)

clean:
  rm $(OBJ_DIR)/*.o indexer
