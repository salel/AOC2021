VARS_OLD := $(.VARIABLES)

SRC = $(wildcard *.cpp)
BIN = $(patsubst %.cpp, %, $(SRC))

all: $(BIN)

clean:
	rm -rf $(BIN)

% : %.cpp
	g++ -g -Wall -pedantic -Wextra -Wunreachable-code -Wconversion -Wshadow -std=c++17 -o $@ $<


vars:; $(foreach v, $(filter-out $(VARS_OLD) VARS_OLD,$(.VARIABLES)), $(info $(v) = $($(v)))) @#noop