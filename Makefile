CXXFLAGS = -O2 -g -Wall -fmessage-length=0
SOURCES = $(wildcard src/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
LIBS =
TARGET = bloq

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all: $(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)

deps:

.PHONY: clean
