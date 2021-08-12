CC=gcc
# CFLAGS=-I
SRC_DIR=./src
BUILD_DIR=./target
SCHEDULER=scheduler

prepare:
	mkdir -p ${BUILD_DIR}

compile: prepare
	${CC} -o ${SCHEDULER} ${SCHEDULER}.c

build: compile

prune:
	rm -r ${BUILD_DIR}/
