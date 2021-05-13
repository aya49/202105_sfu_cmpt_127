# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Werror -Wfatal-errors -g


p1: p1.c p1intarr.c
	gcc $(CFLAGS) -o $@ p1.c p1intarr.c

p2: p2.c p2intarr.c
	gcc $(CFLAGS) -o $@ p2.c p2intarr.c

clean:
	rm -f p1 p2 *.o
