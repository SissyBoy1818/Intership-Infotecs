CXX = g++
CXXFLAGS = -Wall -std=c++17 -fPIC
SRC_DIR = MessageLogLib
SOURCES = $(SRC_DIR)/Journal.cpp $(SRC_DIR)/Message.cpp
OBJECTS = $(SOURCES:.cpp=.o)
SHARED_LIB = libmessagelog.so

all: $(SHARED_LIB)

$(SHARED_LIB): $(OBJECTS)
	$(CXX) -shared -o $(SHARED_LIB) $(OBJECTS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(SRC_DIR)/*.o *.o $(SHARED_LIB)