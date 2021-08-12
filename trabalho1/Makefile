CC=gcc
CFLAGS=-Wall -Wextra -g
SRC_DIR=./src
BUILD_DIR=./target
DISPARADOR=disparador

prepare:
	mkdir -p ${BUILD_DIR}

compile: prepare
	${CC} -o ${BUILD_DIR}/${DISPARADOR} ${SRC_DIR}/${DISPARADOR}.c

build: compile

run: build
	${BUILD_DIR}/${DISPARADOR}

prune:
	rm -r ${BUILD_DIR}/
