CXX       := g++
CXX_FLAGS := -std=c++14 
# CXX_FLAGS += -ggdb

BIN     := bin
SRC     := src
INCLUDE := inc

LIBRARIES   :=
EXECUTABLE  := main

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/*
