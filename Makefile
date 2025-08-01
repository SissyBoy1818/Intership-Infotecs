CC=gcc
SOURCES=MessageLogLib/Journal.cpp MessageLogLib/Journal.h MessageLogLib/Message.cpp MessageLogLib/Message.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=hello

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@