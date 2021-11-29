CXX       := g++
CXX_FLAGS := -std=c++14 
# CXX_FLAGS += -ggdb
CXX_FLAGS += -Wall

BIN     := bin
SRC     := src
INCLUDE := inc
INC     := -I$(INCLUDE) -I$(SRC)/request_mgr -I$(SRC)/event_mgr -I$(SRC)/state_machine -I$(SRC)/state_machine/states

SOURCES=$(SRC)/*.cpp $(SRC)/**/*.cpp 
OBJECTS=$(SOURCES:.cpp=.o)

LIBRARIES   :=
EXECUTABLE  := main

all: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SOURCES)
	$(CXX) $(CXX_FLAGS) $(INC) $^ -o $@ $(LIBRARIES)

clean:
	-rm -rf $(BIN)/*
