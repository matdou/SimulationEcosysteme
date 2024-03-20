CXX = g++
CXXFLAGS = -Wall -std=c++14 -fsanitize=address
LDFLAGS = -lX11 -lpthread -fsanitize=address

# Include directories for project headers
INC_DIR = -I. -Isrc -Isrc/comportements -Isrc/capteurs

# Source directories
SRCDIR = src
SRCDIR2 = src/comportements
SRCDIR3 = src/capteurs
SRCS = $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR2)/*.cpp) $(wildcard $(SRCDIR3)/*.cpp)

# Object directory
OBJDIR = obj
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(notdir $(SRCS)))

# Binary directory
BINDIR = bin
EXEC = $(BINDIR)/main

# Include directory for image headers
IMG_DIR = img
INC_DIR += -I$(IMG_DIR)

vpath %.cpp $(SRCDIR) $(SRCDIR2) $(SRCDIR3)

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(BINDIR)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule for compiling any .cpp to an .o
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC_DIR) -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(BINDIR)
