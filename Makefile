.PHONY: default
default: build

CC := gcc
C_INCLUDE_PATH := include
PROJECT_NAME := SAT51
PROJECT_VERSION := 0.1

OPTI := -g -O3 # -g -O3 || -Ofast and no -g for better perf but can create errors
c_source_files := $(shell find src -name *.c)
c_object_files := $(patsubst src/%.c, build/%.o, $(c_source_files))

$(c_object_files): build/%.o : src/%.c
	@mkdir -p $(dir $@) && \
	$(CC) -Wall $(OPTI) -c -I $(C_INCLUDE_PATH) $(patsubst build/%.o, src/%.c, $@) -o $@

.PHONY: build
build: $(c_object_files)
	@$(CC) -Wall $(OPTI) -o $(PROJECT_NAME) $(c_object_files)

CLEAN:
	@rm -rfv build/
	@mkdir build
	@echo "CLEAN"