SRC := GameOfLife.cpp
BIN := GameOfLife
LD := -lraylib -lm


all: build run 

build:
	clang++ $(SRC) -o $(BIN) $(LD) 

run: 
	./$(BIN)

clean: 
	rm -rf $(BIN)
