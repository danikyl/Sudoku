all:	clean main.o
	@gcc -O2 -o main sudoku.o main.o -lm

main.o:	main.c sudoku.c
	@cc -c sudoku.c main.c -I.

run:
	@./main

clean:
	@find -name '*~' | xargs rm -rf {}
	@find -name '*o' | xargs rm -rf {}