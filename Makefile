CC = clang
CFLAGS = -Wall -g `llvm-config --cflags`
LDFLAGS = `llvm-config --libs` -lm

all: zen

zen: lex.yy.o zen.tab.o symbol_table.o codegen.o
	$(CC) $(CFLAGS) -o zen lex.yy.o zen.tab.o symbol_table.o codegen.o $(LDFLAGS)

zen.tab.c zen.tab.h: zen.y
	bison -d zen.y

lex.yy.c: zen.l zen.tab.h
	flex zen.l

zen.tab.o: zen.tab.c codegen.h symbol_table.h
	$(CC) $(CFLAGS) -c zen.tab.c

lex.yy.o: lex.yy.c
	$(CC) $(CFLAGS) -c lex.yy.c

symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

codegen.o: codegen.c codegen.h symbol_table.h
	$(CC) $(CFLAGS) -c codegen.c

clean:
	rm -f zen lex.yy.c zen.tab.c zen.tab.h *.o
