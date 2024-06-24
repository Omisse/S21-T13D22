CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra

LC=clang-format
LFLAGS=-style=file:$(CLNGPATH) -i

CPPC=cppcheck
CPPCFLAGS=--enable=all --std=c11 --suppress=missingIncludeSystem --check-config

BPATH=build
SRCPATH=src
CLNGPATH:=materials/linters/.clang-format

NAMES_1=cipher.c
FILE_1=$(addprefix $(SRCPATH)/,$(NAMES_1))
OBJ_1=$(FILE_1:.c=.o)
OUT_1=$(BPATH)/cipher

.o:.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: cipher clean

dbg: cipher_debug clean run-leaks_1

run_1: cipher $(OUT_1)
	./$(OUT_1)

run-leaks_1: cipher $(OUT_1)
	leaks -atExit -- ./$(OUT_1)


cipher: $(OBJ_1)
	$(LC) $(LFLAGS) $(FILE_1)
	$(CPPC) $(CPPCFLAGS) $(FILE_1)
	$(CC) $(CFLAGS) $(OBJ_1) -o $(OUT_1)

cipher_debug: $(OBJ_1)
	$(LC) $(LFLAGS) $(FILE_1)
	$(CPPC) $(CPPCFLAGS) $(FILE_1)
	$(CC) $(CFLAGS) $(OBJ_1) -o $(OUT_1)

clean:
	rm src/*.o