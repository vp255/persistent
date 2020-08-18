CXX                     := -g++ -std=c++2a
CXXFLAGS                := -pedantic-errors -Wall -Wextra -Werror -fconcepts
LDFLAGS                 := -L/usr/lib -lstdc++ -lm -pthread
BUILD                   := ./build
OBJ_DIR                 := $(BUILD)/objects
APP_DIR                 := $(BUILD)/apps
LIB_DIR                 := $(BUILD)/libraries
TARGET                  := testing
HOME                    := /home/vincentphan
CPPDIRS                 := $(HOME)/src/cpp
PERSISTENT_LIB_DIR      := $(CPPDIRS)/persistent
INCLUDE                 := -I$(CPPDIRS) -I/usr/local/lib/boost_1_73_0
PERSISTENT_LIB_SRC      := $(wildcard $(PERSISTENT_LIB_DIR)/*.cpp)           
PERSISTENT_TEST_SRC     := $(wildcard ./*.cpp)                               

all: build $(APP_DIR)/$(TARGET)

# Persistent library

PERSISTENT_OBJS := $(PERSISTENT_LIB_SRC:%.cpp=$(PERSISTENT_DIR)/%.o)

persistent_lib: $(PERSISTENT_OBJS)
	ar -crs $(LIB_DIR)/libpersistent.a $^

$(PERSISTENT_DIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)


# Testing application

PERSISTENT_TEST_OBJS  := $(PERSISTENT_TEST_SRC:%.cpp=$(OBJ_DIR)/%.o)


$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

$(APP_DIR)/$(TARGET): persistent_lib $(PERSISTENT_TEST_OBJS) # with static library
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $(PERSISTENT_TEST_OBJS) $(LDFLAGS) -L$(LIB_DIR) -lpersistent

.PHONY: all build clean debug

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIB_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*
	-@rm -rvf $(LIB_DIR)/*
