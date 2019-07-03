CXX=g++
CXX_FLAGS=-W -Wall -c
LD_FLAGS=-lz -pthread
SOURCES=main.cpp signature.cpp utils.cpp
# here you provide paths to compiled boost libraries
OBJECTS=$(SOURCES:.cpp=.o /usr/lib/libboost_program_options.a /usr/lib/libboost_thread.a \
							/usr/lib/libboost_log.a /usr/lib/libboost_log_setup.a)
EXECUTABLE=multi

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LD_FLAGS) -o $@

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@

clean:
	rm -f *.o $(EXECUTABLE)
