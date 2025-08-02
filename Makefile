CXX = g++
CXXFLAGS = -Wall -std=c++17 -fPIC
SRC_DIR = MessageLogLib
SOURCES = $(SRC_DIR)/Journal.cpp $(SRC_DIR)/Message.cpp
OBJECTS = $(SOURCES:.cpp=.o)
SHARED_LIB = libmessagelog.so

PRESENTATION_DIR = MessageLogPresentation
PRESENTATION_SOURCES = $(PRESENTATION_DIR)/Menu.cpp $(PRESENTATION_DIR)/main.cpp
PRESENTATION_OBJECTS = $(PRESENTATION_SOURCES:.cpp=.o)
EXECUTABLE = messagelog_app

all: $(SHARED_LIB) $(EXECUTABLE)

lib: $(SHARED_LIB)

exe: $(EXECUTABLE)

$(SHARED_LIB): $(OBJECTS)
	$(CXX) -shared -o $(SHARED_LIB) $(OBJECTS)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(PRESENTATION_DIR)/%.o: $(PRESENTATION_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@

$(EXECUTABLE): $(PRESENTATION_OBJECTS) $(OBJECTS) $(SHARED_LIB)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -L. -lmessagelog -o $(EXECUTABLE) $(PRESENTATION_OBJECTS) $(OBJECTS) -Wl,-rpath,.

clean:
	rm -f $(SRC_DIR)/*.o $(PRESENTATION_DIR)/*.o *.o $(SHARED_LIB) $(EXECUTABLE)