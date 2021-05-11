# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Werror -Wfatal-errors -g


p1: p1test.c p1.c
	gcc $(CFLAGS) -o $@ p1test.c p1.c

p2: p2test.c p2.c
	gcc $(CFLAGS) -o $@ p2test.c p2.c

clean:
	rm -f p1 p2.1 p2 *.o
