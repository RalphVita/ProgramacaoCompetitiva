# My third makefile

# Name of the project
PROJ_NAME=MoveBrackets

# .c files
C_SOURCE=$(PROJ_NAME).cpp


# Object files
OBJ=$(subst .cpp,.o,$(C_SOURCE))

# Compiler and linker
CC=g++

# Flags for compiler
CC_FLAGS=--std=c++11

# Command used at clean target
RM = rm -rf

#
# Compilation and linking
#
all: compila executa

compila:
	$(CC) -o exec $(C_SOURCE) $(CC_FLAGS)
	#g++ -o exec *.o -O2 --std=c++11
executa:
	./exec < $(PROJ_NAME)

clean:
	rm -f exec *.o
