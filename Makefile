.PHONY: default
default: build

RED := \033[0;31m
GREEN := \033[0;32m
BLUE := \033[0;34m
NC := \033[0m

CC := g++
CPLUS_INCLUDE_PATH := include
OUT_NAME := SAT51
OUT_TEST_NAME := SAT51_TEST
PROJECT_VERSION := 0.2

OPTI := -g -O3 -march=haswell # -Ofast -march=haswell # -g -O3 || -Ofast and no -g for better perf but can create errors
cpp_source_files := $(shell find src -name *.cpp)
cpp_object_files := $(patsubst src/%.cpp, build/%.o, $(cpp_source_files))

$(cpp_object_files): build/%.o : src/%.cpp
	@mkdir -p $(dir $@) && \
	g++ $(OPTI) -c -pthread -I $(CPLUS_INCLUDE_PATH) -lm $(patsubst build/%.o, src/%.cpp, $@) -o $@

.PHONY: build
build: $(cpp_object_files)
	@printf "${BLUE}[-] CPP Files:\n${NC}"
	@echo $(cpp_source_files)
	@printf "${BLUE}[-] CPP OBJ Files:\n${NC}"
	@echo $(cpp_object_files)
	@g++ $(OPTI) -o $(OUT_NAME) $(filter-out build/test.o, $(cpp_object_files)) -lm
	@printf "${GREEN}[+] Build MAIN Success\n${NC}"

.PHONY: build_test
build_test: $(cpp_object_files)
	@printf "${BLUE}[-] CPP Files:\n${NC}"
	@echo $(cpp_source_files)
	@printf "${BLUE}[-] CPP OBJ Files:\n${NC}"
	@echo $(cpp_object_files)
	@g++ $(OPTI) -o $(OUT_TEST_NAME) $(filter-out build/main.o, $(cpp_object_files)) -lm
	@printf "${GREEN}[+] Build TEST Success\n${NC}"

CLEAN:
	@rm -f OUT_NAME
	@rm -rfv build/
	@mkdir build
	@printf "${BLUE}CLEAN\n${NC}"