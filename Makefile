CXXFLAGS = -O2 -g -Wall -fmessage-length=0
SOURCES = $(wildcard src/*.cpp)
OBJS = $(SOURCES:.cpp=.o)
THIRDPARTYBUILDROOT = lib/build
INCDIRS = -I$(THIRDPARTYBUILDROOT)/include
LIBDIRS = -L$(THIRDPARTYBUILDROOT)/lib
LIBS = -lSDL2 -lSDL2_image -ldl -lm -lpthread -lluajit-5.1
TARGET = bloq

# Platform-specific garbage.
ifeq ($(shell uname -s),Darwin)
# clang (OS X) uses different means to specify c++11 support
CXXFLAGS += -std=c++11 -stdlib=libc++
LIBS += -liconv -Wl,-framework,OpenGL -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit
else
# assume we are using g++
CXXFLAGS += -std=c++0x
LIBS += -lrt
endif

all: $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCDIRS) -c -o $@ $<

$(TARGET): deps $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBDIRS) -o $(TARGET) $(OBJS) $(LIBS)

clean:
	$(RM) $(OBJS) $(TARGET)

distclean: clean
	$(MAKE) -C lib clean

deps:
	$(MAKE) -C lib

.PHONY: deps clean distclean
