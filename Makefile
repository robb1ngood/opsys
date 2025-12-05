TARGET_EXEC := p3

SRC_FILES := $(wildcard src/*.c)

$(TARGET_EXEC): $(SRC_FILES)
	gcc -Wall $(SRC_FILES) -o $(TARGET_EXEC) -lm

.PHONY: run
run: $(TARGET_EXEC)
	./$(TARGET_EXEC)