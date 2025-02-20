

# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++14

# Directories
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
GEN_DIR = $(BUILD_DIR)/gen
SRC_DIR = src
BIN_DIR = $(BUILD_DIR)/bin

# Targets (the binaries you want to produce)
MAINBINARY = CanDbMain
BINARY1 = CanLoadDb
BINARY2 = CanRmDb
BINARY3 = CanStart
BINARY4 = CanStop
BINARY5 = CanDbRegTxCbk
BINARY6 = CanDbRegRxCbk
BINARY7 = CanDbSetMsg
BINARY8 = CanDbSendMsg
BINARY9 = CanDbCycSendMsg
BINARY10 = CanDbStopMsg
BINARY11 = CanMapDbCh
COMMONBINARY = CanDbUtil

# Source files
SRC = $(SRC_DIR)/CanLoadDb.cpp $(SRC_DIR)/CanRmDb.cpp $(SRC_DIR)/CanStart.cpp \
      $(SRC_DIR)/CanStop.cpp $(SRC_DIR)/CanDbRegTxCbk.cpp $(SRC_DIR)/CanDbRegRxCbk.cpp \
      $(SRC_DIR)/CanDbSetMsg.cpp $(SRC_DIR)/CanDbSendMsg.cpp $(SRC_DIR)/CanDbCycSendMsg.cpp \
      $(SRC_DIR)/CanDbStopMsg.cpp $(SRC_DIR)/CanDbMain.cpp $(SRC_DIR)/CanMapDbCh.cpp

# Object files
OBJ = $(SRC:.cpp=.o)
OBJ = $(OBJ:%=$(OBJ_DIR)/%)

# Default target to compile all programs
all: $(MAINBINARY) $(BINARY1) $(BINARY2) $(BINARY3) $(BINARY4) \
     $(BINARY5) $(BINARY6) $(BINARY7) $(BINARY8) $(BINARY9) \
     $(BINARY10) $(BINARY11)
	 
	 @mkdir -p $(GEN_DIR)

# Rule to compile .cpp files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(OBJ_DIR)  # Ensure the object directory exists
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to build CanDbMain
$(MAINBINARY): $(OBJ_DIR)/CanDbMain.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbMain.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(MAINBINARY)

# Rule to build CanLoadDb
$(BINARY1): $(OBJ_DIR)/CanLoadDb.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanLoadDb.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY1)

# Rule to build CanRmDb
$(BINARY2): $(OBJ_DIR)/CanRmDb.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanRmDb.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY2)

# Rule to build CanStart
$(BINARY3): $(OBJ_DIR)/CanStart.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanStart.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY3)

# Rule to build CanStop
$(BINARY4): $(OBJ_DIR)/CanStop.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanStop.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY4)

# Rule to build CanDbRegTxCbk
$(BINARY5): $(OBJ_DIR)/CanDbRegTxCbk.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbRegTxCbk.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY5)

# Rule to build CanDbRegRxCbk
$(BINARY6): $(OBJ_DIR)/CanDbRegRxCbk.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbRegRxCbk.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY6)

# Rule to build CanDbSetMsg
$(BINARY7): $(OBJ_DIR)/CanDbSetMsg.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbSetMsg.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY7)

# Rule to build CanDbSendMsg
$(BINARY8): $(OBJ_DIR)/CanDbSendMsg.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbSendMsg.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY8)

# Rule to build CanDbCycSendMsg
$(BINARY9): $(OBJ_DIR)/CanDbCycSendMsg.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbCycSendMsg.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY9)

# Rule to build CanDbStopMsg
$(BINARY10): $(OBJ_DIR)/CanDbStopMsg.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanDbStopMsg.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY10)

# Rule to build CanMapDbCh
$(BINARY11): $(OBJ_DIR)/CanMapDbCh.o $(OBJ_DIR)/CanDbUtil.o
	@mkdir -p $(BIN_DIR)
	$(CXX) $(OBJ_DIR)/CanMapDbCh.o $(OBJ_DIR)/CanDbUtil.o -o $(BIN_DIR)/$(BINARY11)

# Clean up build artifacts
clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR) $(GEN_DIR)

.PHONY: all clean
