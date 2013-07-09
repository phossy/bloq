CXXFLAGS = -O2 -g -Wall -fmessage-length=0
SOURCES = $(wildcard src/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
LIBS =
TARGET = bloq

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): deps $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
	make -C lib clean

deps:
	make -C lib

.PHONY: deps clean
