CXXFLAGS = -g -Wall -fmessage-length=0
SRCS = $(wildcard src/*.cpp)
OBJS = $(SRCS:%.cpp=%.o)
DEPS = $(SRCS:%.cpp=%.d)
CPPFLAGS += -MMD -MP
THIRDPARTYBUILDROOT = lib/build
INCDIRS = -I$(THIRDPARTYBUILDROOT)/include
LIBDIRS = -L$(THIRDPARTYBUILDROOT)/lib
LIBS = -lSDL2 -lSDL2_image -ldl -lm -lpthread -lluajit-5.1
TARGET = bloq

# Platform-specific garbage.
ifeq ($(shell uname -s),Darwin)
# clang (OS X) uses different means to specify c++11 support
CXXFLAGS += -std=c++11 -stdlib=libc++
# and we have to specify all the frameworks by hand
LIBS += -liconv -Wl,-framework,OpenGL -Wl,-framework,ForceFeedback -lobjc -Wl,-framework,Cocoa -Wl,-framework,Carbon -Wl,-framework,IOKit -Wl,-framework,CoreAudio -Wl,-framework,AudioToolbox -Wl,-framework,AudioUnit
ifeq ($(shell uname -m),x86_64)
# if building on 64bit OS X this is required for luajit to not segfault
LIBS += -Wl,-pagezero_size,10000 -Wl,-image_base,100000000
endif

else
# assume we are using g++
CXXFLAGS += -std=c++0x
LIBS += -lrt
endif

CXXFLAGS += $(INCDIRS)

all: $(TARGET)

$(TARGET): libs $(OBJS)
	$(CXX) $(CXXFLAGS) $(LIBDIRS) -o $(TARGET) $(OBJS) $(LIBS)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS) $(TARGET)

distclean: clean
	$(MAKE) -C lib clean

libs:
	$(MAKE) -C lib

.PHONY: libs clean distclean
