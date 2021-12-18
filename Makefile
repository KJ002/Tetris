SRC 		= source
DEST		= build
BINARY		= tetris
CXX_FLAGS1 	= -pthread -std=c++20 -g
CXX_FLAGS2 	= -lraylib -lGL -lm -ldl
CXXC		= clang++
ASM_SRC		= ./source/*.asm
ASM_FLAGS	= -f elf64
AC			= nasm


all: compile

compile:
	@rm -rf ${DEST}
	@mkdir ${DEST}
	${CXXC} -c ${SRC}/*.cpp ${CXX_FLAGS1}
	${AC} ${SRC}/*.asm ${ASM_FLAGS}

	@mv ${SRC}/*.o ${DEST}
	@mv *.o ${DEST}
	${CXXC} ${DEST}/*.o ${CXX_FLAGS2} -o ${DEST}/${BINARY}

run: compile
	@./${DEST}/${BINARY}
