CXX_SRC 	= ./source/*.cpp
CXX_FLAGS 	= -lraylib -lGL -lm -pthread -ldl -std=c++20
CXX_COMPILER	= clang++
DEST		= build
BINARY		= tetris

all: compile

compile:
	@mkdir -p ${DEST}
	${CXX_COMPILER} ${CXX_SRC} ${CXX_FLAGS} -o ${DEST}/${BINARY}
