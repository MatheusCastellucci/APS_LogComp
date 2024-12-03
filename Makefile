CC = clang
CFLAGS = -Wall -g -Wno-unused-function `llvm-config --cflags`
LDFLAGS = `llvm-config --libs core executionengine interpreter analysis native` -lm

all: sensei

sensei: lexer.o parser.o ast.o codegen.o
	$(CC) $(CFLAGS) -o sensei lexer.o parser.o ast.o codegen.o $(LDFLAGS)

lexer.o: lexer.c parser.h ast.h
	$(CC) $(CFLAGS) -c lexer.c

parser.o: parser.c parser.h ast.h
	$(CC) $(CFLAGS) -c parser.c

parser.h: parser.y
	bison -d -o parser.c parser.y

lexer.c: lexer.l
	flex -o lexer.c lexer.l

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c

codegen.o: codegen.c codegen.h ast.h
	$(CC) $(CFLAGS) -c codegen.c

clean:
	rm -f sensei lexer.c parser.c parser.h *.o
