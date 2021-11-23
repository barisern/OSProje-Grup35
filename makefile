all: compile run

compile:
	gcc ./src/main.c -o ./bin/main
	
run:
	./bin/main