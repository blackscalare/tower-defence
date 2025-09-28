CC = g++
#CFLAGS = -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wconversion -std=c++17 -I/usr/local/include -Isrc -MMD -MP
CFLAGS = -Wall -Wextra -Wundef -Wshadow -Wpointer-arith -Wcast-align -Wconversion \
         -Wstrict-aliasing=2 -Wformat=2 -Wold-style-cast -Wnull-dereference \
         -Woverloaded-virtual -Wnon-virtual-dtor -Wdouble-promotion -Wfloat-equal \
         -Wpedantic -std=c++17 -I/usr/local/include -Isrc -MMD -MP
LDFLAGS = -L/usr/local/lib -lraylib -lm -lpthread -ldl -lrt -lX11

SRC_DIR = src
OBJ_DIR = build

#SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
SOURCES := $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

TARGET = tower_defence

BUILD ?= debug

ifeq ($(BUILD),release)
	CFLAGS += -O2 -DNDEBUG
else
	CFLAGS += -g -O0
endif

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	#@mkdir -p $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

-include $(DEPS)

.PHONY: all clean
