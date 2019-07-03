CXX=g++
CXX_FLAGS=-W -Wall -c -std=c++11
SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=heap_test

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
