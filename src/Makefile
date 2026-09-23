BIN := portifolio-server 
BUILD_DIR := ./build
SRC_DIRS := ./src

SRCS := $(wildcard src/*.c)
# SRCS := $(filter-out src/foo.c, $(SRCS))

OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CC=clang
CFLAGS:=$(CFLAGS) -std=gnu11 -O2 -Wall -Wextra -Isrc/ -MMD -MP -fcommon

$(BUILD_DIR)/$(BIN): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
