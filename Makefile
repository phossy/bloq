CXXFLAGS = -O2 -g -Wall -fmessage-length=0 -std=gnu++0x
SOURCES = $(wildcard src/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
THIRDPARTYBUILDROOT = lib/build
INCDIRS = -I$(THIRDPARTYBUILDROOT)/include
LIBDIRS = -L$(THIRDPARTYBUILDROOT)/lib
LIBS = -lSDL2 -lSDL2_image -ldl -lm -lpthread -lrt
TARGET = bloq

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c -o $@ $<

$(TARGET): deps $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBDIRS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	rm -f $(OBJS) $(TARGET)
	make -C lib clean

deps:
	make -C lib

.PHONY: deps clean
