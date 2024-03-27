CXX = g++
CXXFLAGS = -Wall -std=c++14 -fsanitize=address
LDFLAGS = -lX11 -lpthread -fsanitize=address

# Directories
SRC_DIRS = src src/comportements src/capteurs
OBJ_DIR = obj
BIN_DIR = bin
IMG_DIR = img

# Include directories
INC_DIRS = $(SRC_DIRS) $(IMG_DIR)
INC_FLAGS = $(addprefix -I,$(INC_DIRS))

# Find all cpp files in the source directories
SRCS = $(foreach dir,$(SRC_DIRS),$(wildcard $(dir)/*.cpp))

# Object files have same name as cpp files, but with .o extension
OBJS = $(SRCS:%.cpp=$(OBJ_DIR)/%.o)

# Target executable
EXEC = $(BIN_DIR)/main

.PHONY: all clean

all: $(EXEC)

# Link object files to create the executable
$(EXEC): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Compile cpp files to object files
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
