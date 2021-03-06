.PHONY: default
default: build

CC := g++
CPLUS_INCLUDE_PATH := include
OUT_NAME := SAT51
PROJECT_VERSION := 0.2

OPTI := -g # -Ofast -march=haswell # -g -O3 || -Ofast and no -g for better perf but can create errors
cpp_source_files := $(shell find src -name *.cpp)
cpp_object_files := $(patsubst src/%.cpp, build/%.o, $(cpp_source_files))

$(cpp_object_files): build/%.o : src/%.cpp
	@mkdir -p $(dir $@) && \
	g++ $(OPTI) -c -pthread -I $(CPLUS_INCLUDE_PATH) -lm $(patsubst build/%.o, src/%.cpp, $@) -o $@

.PHONY: build
build: $(cpp_object_files)
	@echo "[CPP Files] :"
	@echo $(cpp_source_files)
	@echo "[CPP OBJ Files] :"
	@echo $(cpp_object_files)
	@g++ $(OPTI) -o $(OUT_NAME) $(cpp_object_files) -lm

CLEAN:
	@rm -f OUT_NAME
	@rm -rfv build/
	@mkdir build
	@echo "CLEAN"