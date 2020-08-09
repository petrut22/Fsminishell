build:
	gcc fsminishell.c -o fsminishell
clean: fsminishell
	rm fsminishell
run: fsminishell
	./fsminishell
