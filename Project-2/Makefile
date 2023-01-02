CC = g++
CPPFLAGS = -O3 -std=c++11 -Wall -Wextra -Werror -lm
TESTS = $(wildcard tests/*.in)
SHELL := /bin/bash
MAKEFLAGS += -j

RED = \033[0;31m
GREEN = \033[0;32m
NC = \033[0m

all: p2
	./p2

clean:
	rm p2
	rm tests/*.out

.PHONY : test all %.test

test: $(TESTS)
	@echo -e "${GREEN}All tests passed${NC}"

%.in: p2
	@./p2 < $*.in > $*.out
	@diff -q $*.out $*.ans || (echo -e "${RED}Test $*.in failed${NC}" && exit 1)
