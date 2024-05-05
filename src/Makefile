
.PHONY : all install clean rebuild run style tests dvi

CXX := g++
CXXFLAGS= -Wall -Wextra -Werror -std=c++17
GTEST_FLAGS= -lgtest_main -pthread -lgtest
GCOV=--coverage

OS := $(shell uname -s)

OPEN = open
ifeq ($(OS), Linux)
	OPEN = google-chrome
endif
ifeq ($(OS), Darwin)
	IGNORE_ERR=--ignore-errors inconsistent --ignore-errors mismatch
endif


SRC_DIR := .
EXTENSIONS := cc cpp h
# Функция для обнаружения файлов с заданными расширениями в директории и ее поддиректориях
find_files = $(foreach ext,$(EXTENSIONS),$(wildcard $(1)/*.$(ext))) $(foreach d,$(wildcard $(1)/*),$(call find_files,$(d)))
SRC_FILES := $(call find_files,$(SRC_DIR))

# Фильтрация только файлов с расширением .cc
CC_FILES := $(filter-out ./gui/desktop/main.cc ./gui/desktop/SnakeView.cc, $(filter %.cc,$(SRC_FILES)))

TEST_SRC := tests/unit_tests.cc

MSG=Minor bug fixes
BRANCH=$(shell git branch --show-current)

all: install tests dvi run

install: uninstall clean
	mkdir ../build
	cd ../build && cmake .. && make 3dViewer

rebuild:
	cd ../build && make 3dViewer && ./3dViewer

run:
	cd ../build && ./3dViewer

dvi:
	cd ../dvi && $(OPEN) dvi.html

uninstall:
	rm -rf ../build

gcov_report: clean
	$(CXX) $(CXXFLAGS) $(GCOV) $(GTEST_FLAGS)  $(TEST_SRC) Controller/controller.cc Model/*.cc -o report
	./report
	gcov *.gcno *.gcda
	lcov --capture --directory . --output-file coverage.info --no-external $(IGNORE_ERR)
	genhtml coverage.info --output-directory coverage_report
	$(OPEN) ./coverage_report/index.html
	rm -rf *.gcda *.gcno *.info report *.gcov

clean:
	clear
	rm -rf test
	rm -rf *.gcda *.gcno *.info report *.gcov coverage_report ../3dViewer.tgz ../3dViewer
	make style

dist: install
	mkdir -p 3dViewer
	touch 3dViewer/Makefile
	echo ".PHONY: all dvi \nall: dvi run\nrun:\n\tcd build && ./3dViewer\ndvi:\n\topen dvi/dvi.html" >> 3dViewer/Makefile
	cp -R ../build ../dvi 3dViewer/
	tar cvzf 3dViewer.tgz 3dViewer/
	mv 3dViewer.tgz ../
	rm -rf 3dViewer/


style:
	@cp ../materials/linters/.clang-format .
	clang-format -n $(SRC_FILES)
	clang-format -i $(SRC_FILES)
	@rm -rf .clang-format

# Ниже три цели для сборки google test. (1 - стандартная через терминал, 2 - cmake, 3 - cmake)
tests:
	$(CXX) $(CXXFLAGS) $(TEST_SRC) Model/*.cc Controller/controller.cc $(GTEST_FLAGS) -o test
	./test

google_test:
	cd .. && cmake -S . -B build && cmake --build build && cd build && ctest

debug_gtest: clean
	mkdir ../build
	cd ../build && cmake .. && make unit_test && ./unit_test

run_test:
	cd ../build && ctest
	cd ../build && ./unit_test


# Usage example: make push MSG="write here what was added"
push: clean
	git add ..
	git commit -m "$(BRANCH): $(MSG)"
	git push origin $(BRANCH)

# Run Docker and test program on leaks
docker:
	docker build -f Dockerfile/dockerfile -t my_image .
	docker run -d -p 80:80 --name my_container my_image bash -c "ls && cd /TEST_VALGRIND/src && make tests && valgrind ./test"
	docker logs -f my_container
	docker stop my_container
	docker rm my_container
	docker rmi my_image

brew_install:
ifeq ($(OS), Linux)
	sudo apt install -y lcov
endif
ifeq ($(OS), Darwin)
	sh ./brew/installbrew.sh
	brew install lcov
endif


