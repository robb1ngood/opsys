TARGET_EXEC := p2

SRC_FILES := $(wildcard src/*.c)

$(TARGET_EXEC): $(SRC_FILES)
	gcc -Wall -Wextra $(SRC_FILES) -o $(TARGET_EXEC) -lm

.PHONY: run
run: $(TARGET_EXEC)
	./$(TARGET_EXEC)