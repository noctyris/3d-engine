CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -ggdb3 -Iinc $(shell pkg-config --cflags sdl3)
LDFLAGS = $(shell pkg-config --libs sdl3) -lm

SRC_DIR = ./
OBJ_DIR = build
BIN = launch

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

run: all
	./$(BIN)

clean:
	rm -rf $(OBJ_DIR) $(BIN)

.PHONY: all clean run
