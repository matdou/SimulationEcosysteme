CXX = g++
CXXFLAGS = -Wall -std=c++11
LDFLAGS = -lX11 -lpthread
INC_DIR = .

SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJDIR = obj
OBJS = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
BINDIR = bin
EXEC = $(BINDIR)/main

# Directory containing UImg.h and CImg.h
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
