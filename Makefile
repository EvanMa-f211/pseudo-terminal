all: pseudo_terminal
pseudo_terminal.o: pseudo_terminal.c pseudo_terminal.h
	gcc -c pseudo_terminal.c -o pseudoterminal.o
command.o: command.c pseudo_terminal.h
	gcc -c command.c -o command.o
pseudo_terminal: pseudo_terminal.o command.o
	gcc -o pseudo_terminal pseudo_terminal.o command.o
clean:
	rm -f pseudo_terminal.o command.o
