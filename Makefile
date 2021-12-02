CXX       := g++
CXX_FLAGS := -std=c++14 
# CXX_FLAGS += -ggdb
CXX_FLAGS += -Wall
CXX_FLAGS += -Wno-unused-private-field

BIN     := bin
SRC     := src
INCLUDE := inc
INC     := -I$(INCLUDE) -I$(SRC)/request_mgr -I$(SRC)/event_mgr -I$(SRC)/state_machine -I$(SRC)/state_machine/states

SOURCES=$(SRC)/*.cpp $(SRC)/**/*.cpp 
OBJECTS=$(SOURCES:.cpp=.o)

LIBRARIES   :=
EXECUTABLE  := main

.PHONY: all
all: clean $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXX_FLAGS) $(INC) $^ -o $@ $(LIBRARIES)

.PHONY: clean
clean:
	-rm -rf $(BIN)/*
