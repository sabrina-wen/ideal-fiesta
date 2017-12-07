all: semantics.c
	gcc semantics.c

run: all
	./a.out -c 432
	./a.out -v
	./a.out -c 23
	./a.out -r
