# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Wextra -Werror -Wfatal-errors -g


p1: p1.c
	gcc $(CFLAGS) -o $@ p1.c

p2.1: 2.1.c
	gcc $(CFLAGS) -o $@ p2.1.c

p2.2: 2.2.c
	gcc $(CFLAGS) -o $@ p2.2.c

p3: p3.c
	gcc $(CFLAGS) -o $@ p3.c

p4: p4.c
	gcc $(CFLAGS) -o $@ p4.c

clean:
	rm -f p1.c p2.1.c p2.2.c p3.c p4.c *.o
