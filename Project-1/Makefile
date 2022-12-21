CC = g++
CPPFLAGS = -O3 -std=c++11 -Wall -Wextra -Werror -lm
TESTS = $(wildcard tests/*.in)
SHELL := /bin/bash
MAKEFLAGS += -j

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: file
	./file

clean:
	rm file
	rm tests/*.out

.PHONY : test all %.test

test: $(TESTS)
	@echo -e "${GREEN}All tests passed${NC}"

%.in: file
	@./file < $*.in > $*.out
	@diff -q $*.out $*.ans || (echo -e "${RED}Test $*.in failed${NC}" && exit 1)
