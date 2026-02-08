CXX = g++
CXXFLAGS = -std=c++14 -Wall -Wextra -I$(SRC_DIR)

# Directories
SRC_DIR = src
BUILD_DIR = build

# Sources common to all executables (only including existing .cpp files)
COMMON_SRCS = $(SRC_DIR)/University.cpp $(SRC_DIR)/Department.cpp $(SRC_DIR)/Course.cpp \
              $(SRC_DIR)/Student.cpp $(SRC_DIR)/Teacher.cpp $(SRC_DIR)/TA.cpp

# Object files for common sources
COMMON_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(COMMON_SRCS))

# Output names
TARGET = cms_app
POPULATE_TARGET = populate_data

# Default Target
all: directories $(BUILD_DIR)/$(TARGET).exe $(BUILD_DIR)/$(POPULATE_TARGET).exe
	@echo "Build complete: $(BUILD_DIR)/$(TARGET).exe"

# Create Build Directory
directories:
	mkdir -p $(BUILD_DIR)

# Link Main App
$(BUILD_DIR)/$(TARGET).exe: $(BUILD_DIR)/main.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Link Populate Tool
$(BUILD_DIR)/$(POPULATE_TARGET).exe: $(BUILD_DIR)/populate_data.o $(COMMON_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile Source Files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main program
run: all
	./$(BUILD_DIR)/$(TARGET).exe

clean:
	rm -rf $(BUILD_DIR)
	@echo "Cleaned build directory."

help:
	@echo "CMS - Build Options:"
	@echo "  make          - Build all executables"
	@echo "  make run      - Build and run main app"
	@echo "  make clean    - Remove build artifacts"

.PHONY: all clean directories run help
