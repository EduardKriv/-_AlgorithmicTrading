.PHONY: all install uninstall clean dvi dist
PROJECT_NAME = AlgorithmicTrading

CC = g++ -O3 -std=c++17
WARN = -Wall -Werror -Wextra
CPPCHECK_FLAGS = --enable=all --language=c++ --std=c++17 --suppress=missingInclude --suppress=unusedFunction
TEST_LIB = -lgtest

SOURCES_C := model/*.cc
SOURCES_H := model/*.h \
			controller/*.h \

OS = $(shell uname)

all: clean install

clean:
	rm -f *.o *.gcno *.gcda *.info *.out */.clang-format .clang-format
	rm -rf ./report/ *.dSYM
	@clear

test: clean
	$(CC) $(SOURCES_C) test.cc $(TEST_LIB) -o test.out
	./test.out

build:
	@rm -rf ./build
	@mkdir -p ./build/
	cmake -S . -B ./build
	cmake --build ./build

install: clean uninstall build
	mkdir -p $(HOME)/$(PROJECT_NAME)
	cp -rf ./build/$(PROJECT_NAME).app $(HOME)/$(PROJECT_NAME)/
	cp -rf ./resources $(HOME)/$(PROJECT_NAME)
	make clean
ifeq ($(OS),Darwin)
	@open $(HOME)/$(PROJECT_NAME)/
endif

uninstall:
	rm -rf $(HOME)/$(PROJECT_NAME)/

dist: clean
	@mkdir -p ../$(PROJECT_NAME).zip

	@cp -rf ./controller ../$(PROJECT_NAME).zip/controller
	@cp -rf ./model ../$(PROJECT_NAME).zip/model
	@cp -rf ./view ../$(PROJECT_NAME).zip/view
	@cp -rf ./documentation ../$(PROJECT_NAME).zip/documentation
	@cp -rf ./resources ../$(PROJECT_NAME).zip/resources

	@cp -rf ./CMakeLists.txt ../$(PROJECT_NAME).zip/
	@cp -rf ./main.cpp ../$(PROJECT_NAME).zip/
	@cp -rf ./Makefile ../$(PROJECT_NAME).zip/

	@cd ..; tar -cvzf $(PROJECT_NAME).tar.gz $(PROJECT_NAME).zip
	@cp ../$(PROJECT_NAME).tar.gz $(HOME)
	@rm -rf ../$(PROJECT_NAME).zip
	@rm -rf ../$(PROJECT_NAME).tar.gz
ifeq ($(OS),Darwin)
	@open $(HOME)/
endif

dvi:
	makeinfo --html -o documentation/ documentation/documentation.texi
ifeq ($(OS),Darwin)
	open -a "Google Chrome.app" documentation/index.html
endif

clang:
	@cp ../materials/linters/.clang-format ./
	@clang-format -i */*.cc
	@clang-format -i */*.h
	clang-format -n */*.cc
	clang-format -n */*.h

cppcheck:
	@cppcheck $(CPPCHECK_FLAGS) view/*.cc view/*.cpp controller/* model/*

leaks:
	$(CC) $(SOURCES_C) test.cc $(TEST_LIB) -o test.out
	CK_FORK=no leaks --atExit -- ./test.out

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes ./test.out
