# Makefile

CXX        := g++
CXXFLAGS   := -std=c++20 -Wall -g -O0
LDFLAGS    := 
TARGET     := cc3k

# all .cc files in this directory
SRCS       := $(wildcard *.cc)
# corresponding .o files
OBJS       := $(SRCS:.cc=.o)
# all headers, so that any .h change re-triggers compilation of .cc
DEPS       := $(wildcard *.h)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# compile each .cc into .o, and recompile if any header changed
%.o: %.cc $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
