CXX       := g++
CXX_FLAGS := -std=c++14 
# CXX_FLAGS += -ggdb
CXX_FLAGS += -Wall

BIN     := bin
SRC     := src
INCLUDE := inc

LIBRARIES   :=
EXECUTABLE  := main

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp $(SRC)/**/*.cpp 
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) -I$(SRC)/request_mgr -I$(SRC)/event_mgr -I$(SRC)/state_machine $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/*
