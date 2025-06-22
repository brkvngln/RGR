CXX = g++
CXXFLAGS = -std=c++17 -fPIC -Wall -g

BUILD_DIR = project
BIN_DIR = $(BUILD_DIR)/bin
LIB_DIR = $(BUILD_DIR)/lib

EXEC = $(BIN_DIR)/rgrka

LIB_CODEWORD = $(LIB_DIR)/libcode_word.so
LIB_POLIBIUS = $(LIB_DIR)/libpolibius.so
LIB_RSA = $(LIB_DIR)/librsa.so

OBJ_CODEWORD = code_word.o
OBJ_POLIBIUS = polibius.o
OBJ_RSA = rsa.o
OBJ_MAIN = main.o
OBJ_MODES = modes.o

.PHONY: all clean

all: $(BUILD_DIR) $(EXEC) $(LIB_CODEWORD) $(LIB_POLIBIUS) $(LIB_RSA) $(OBJ_MODES)

$(BUILD_DIR):
	mkdir -p $(BIN_DIR) $(LIB_DIR)

LDFLAGS_LIB = -shared
LDFLAGS_MAIN = -ldl -L$(LIB_DIR) -Wl,-rpath=$(LIB_DIR)

$(EXEC): $(OBJ_MAIN) $(OBJ_MODES) $(LIB_CODEWORD) $(LIB_POLIBIUS) $(LIB_RSA)
	$(CXX) $(CXXFLAGS) $(OBJ_MAIN) $(OBJ_MODES) -o $@ -L$(LIB_DIR) -lcode_word -lpolibius -lrsa $(LDFLAGS_MAIN)

$(LIB_CODEWORD): $(OBJ_CODEWORD)
	$(CXX) $(CXXFLAGS) $(LDFLAGS_LIB) $(OBJ_CODEWORD) -o $@

$(LIB_POLIBIUS): $(OBJ_POLIBIUS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS_LIB) $(OBJ_POLIBIUS) -o $@

$(LIB_RSA): $(OBJ_RSA)
	$(CXX) $(CXXFLAGS) $(LDFLAGS_LIB) $(OBJ_RSA) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(OBJ_MAIN) $(OBJ_MODES) $(OBJ_CODEWORD) $(OBJ_POLIBIUS) $(OBJ_RSA)
