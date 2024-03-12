CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lX11 -lpthread

# Include directory for project headers
INC_DIR = -I.

# Source directory
SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)

# Object directory
OBJDIR = obj
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# Binary directory
BINDIR = bin
EXEC = $(BINDIR)/main

# Include directory for image headers
IMG_DIR = img
INC_DIR += -I$(IMG_DIR)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@ $(INC_DIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR)
