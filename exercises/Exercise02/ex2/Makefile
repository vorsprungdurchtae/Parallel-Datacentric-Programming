EXECUTABLE := kmeans.exe
SRC := kmeans.cpp
PLOT := make-gif.plt

# INPUT_DIR needs to be set according to your local file placement
INPUT_DIR := input

CXX ?= icpc
FLAGS_FAST = -O3 -ip -xhost -fp-model fast=2 -std=c++11
FLAGS_DEBUG = -O0 -g -std=c++11 -Wall -Wextra

build: help

help:
	@echo
	@echo '  Usage:'
	@echo '    make <target>'
	@echo
	@echo '  Targets:'
	@echo '    debug         Build for debugging'
	@echo '    release       Build for performance'
	@echo '    run-small     Run kmeans for the small data set'
	@echo '    run-large     Run kmeans for the large data set'
	@echo '    vis-small     Generate small.gif for the small data set'
	@echo '    vis-large     Generate large.gif for the large data set'
	@echo '    clean         Clean-up of generated files'
	@echo

debug:
	${CXX} ${FLAGS_DEBUG} ${SRC} -o ${EXECUTABLE}

release:
	${CXX} ${FLAGS_FAST} ${SRC} -o ${EXECUTABLE}

run-small: release
	./${EXECUTABLE} ./input/small.in 1000 5 20

run-large: release
	./${EXECUTABLE} ./input/large.in 1000000 5000 50

vis-small:
	gnuplot -c ./${PLOT} ./input/small.in result.out small.gif

vis-large:
	gnuplot -c ./${PLOT} ./input/large.in result.out large.gif

clean:
	${RM} ${EXECUTABLE} *.out *.gif

.PHONY: clean build debug release run-small run-large vis-small vis-large
