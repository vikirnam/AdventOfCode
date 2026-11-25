CC := gcc

SOURCE_DIR := src
INCLUDE_DIR := include
OUTPUT_DIR := target

OUTPUT := $(OUTPUT_DIR)/aocc

CFLAGS := -Wall -Wextra -Wpedantic -std=c99 -g

SOURCE_FILES := $(shell find $(SOURCE_DIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SOURCE_DIR)/%.c,$(OUTPUT_DIR)/obj/%.o,$(SOURCE_FILES))

DEPS := $(OBJECTS:.o=.d)

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(OBJECTS) -o $@

$(OUTPUT_DIR)/obj/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) -I$(INCLUDE_DIR) $(CFLAGS) -MMD -MP -c $< -o $@

run: $(OUTPUT)
	./$(OUTPUT) $(ARGS)

clean:
	rm -rf $(OUTPUT_DIR)

rebuild: clean all


-include $(DEPS)

.PHONY: all run clean rebuild
