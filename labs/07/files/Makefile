# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Wextra -Werror -Wfatal-errors -g


all:  p1.1 p1.2 p1.3 p1.4 p1.5 p2list

p1.1: p1.c p1.1.c
	gcc $(CFLAGS) -o $@ p1.c p1.1.c

p1.2: p1.c p1.2.c
	gcc $(CFLAGS) -o $@ p1.c p1.2.c

p1.3: p1.c p1.3.c
	gcc $(CFLAGS) -o $@ p1.c p1.3.c

p1.4: p1.c p1.4.c
	gcc $(CFLAGS) -o $@ p1.c p1.4.c

p1.5: p1.c p1.5.c
	gcc $(CFLAGS) -o $@ p1.c p1.5.c

p2list: p1.c p2list.c
	gcc $(CFLAGS) -o $@ p1.c p2list.c

clean:
	rm -f p1.1 p1.2 p1.3 p1.4 p1.5 p2list *.o