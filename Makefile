.PHONY: default
default: build

CC := gcc
C_INCLUDE_PATH := include
PROJECT_NAME := SATstis51
PROJECT_VERSION := 0.1

c_source_files := $(shell find src -name *.c)
c_object_files := $(patsubst src/%.c, build/%.o, $(c_source_files))

$(c_object_files): build/%.o : src/%.c
	@mkdir -p $(dir $@) && \
	$(CC) -Wall -c -I $(C_INCLUDE_PATH) $(patsubst build/%.o, src/%.c, $@) -o $@

.PHONY: build
build: $(c_object_files)
	@$(CC) -Wall -o $(PROJECT_NAME) $(c_object_files)

CLEAN:
	@rm -rfv build/
	@mkdir build
	@echo "CLEAN"