CXX = g++
CXXFLAGS = -Wall -I include
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# Найти все файлы .cpp в папке src и заменить их на соответствующие файлы .o в папке obj
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

EXECUTABLE = $(BIN_DIR)/g--

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
