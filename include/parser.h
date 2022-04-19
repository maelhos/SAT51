#pragma once
#include "stdinc.h"
#include "formula.h"
#include "string.h"

void printError(char* line, const char* mess, uint32_t lineNumber, uint32_t indexchar);
void gotoNextNonspace(uint32_t* index, char* buffFirstChar, char* line);
formula parse(FILE* f);
