SRC_DIRS := .
BUILD_DIR := ../build

TARGET_1 := $(BUILD_DIR)/Quest_1

TARGETS := $(TARGET_1)

CC := gcc
FLAGS := -Wall -Wextra -Werror -std=c11 $(addprefix -I,$(SRC_DIRS))
FSAN_FLAGS := -fsanitize=leak -fsanitize=undefined -fsanitize=unreachable -fsanitize=address

SRCS := levels.c modules_db.c modules.c shared.c status_events.c
HDRS := database.h levels.h modules.h status_events.h

all: build_db

format:
	@clang-format -i $(SRCS)

build_db: $(TARGET_1)

$(TARGET_1): $(SRCS) $(HDRS)
	@$(MAKE) format
	@$(CC) $(FLAGS) -o $@ $(FSAN_FLAGS) $(SRCS)
	@echo "Build successful: $@"

clean:
	@find $(BUILD_DIR) -type f -name 'Quest*' -delete

rebuild: clean all
