COLOR_RESET := \033[0m
COLOR_RED   := \033[31m
COLOR_GREEN := \033[32m
COLOR_YELLOW:= \033[33m
COLOR_BLUE  := \033[34m
COLOR_CYAN  := \033[36m
COLOR_BOLD  := \033[1m

CXX      := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -Werror -Iinclude -O3 -pthread

PREFIX   ?= /usr/local

LIBRARY_NAME := blackbox

all: examples

examples: bin/example_basic

bin/example_basic: examples/main.cpp include/$(LIBRARY_NAME)/Logger.hpp
	@mkdir -p bin
	$(CXX) $(CXXFLAGS) $< -o $@
	printf "$(COLOR_GREEN)[INFO] $(COLOR_RESET)Compiled $< to $@$(COLOR_RESET)\n"

install:
	mkdir -p $(DESTDIR)$(PREFIX)/include
	cp -r include/$(LIBRARY_NAME) $(DESTDIR)$(PREFIX)/include/
	printf "$(COLOR_GREEN)[INFO] $(COLOR_RESET)Installed $(COLOR_BOLD)$(LIBRARY_NAME)$(COLOR_RESET) $(COLOR_BOLD)to $(DESTDIR)$(PREFIX)/include/$(LIBRARY_NAME)$(COLOR_RESET)\n"

uninstall:
	rm -rf $(DESTDIR)$(PREFIX)/include/$(LIBRARY_NAME)
	printf "$(COLOR_GREEN)[INFO] $(COLOR_RESET)Uninstalled $(COLOR_BOLD)$(LIBRARY_NAME)$(COLOR_RESET) from $(COLOR_BOLD)$(DESTDIR)$(PREFIX)/include/$(LIBRARY_NAME)$(COLOR_RESET)\n"

clean:
	rm -rf bin/
	printf "$(COLOR_GREEN)[INFO] $(COLOR_RESET)Cleaned build artifacts$(COLOR_RESET)\n"

.PHONY: all examples tests install uninstall clean