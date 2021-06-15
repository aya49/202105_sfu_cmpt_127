# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS := -Wextra -Werror -Wfatal-errors -g


p1: p1.c p1funcs.c
	gcc $(CFLAGS) -o $@  p1.c p1funcs.c

p2: p2.c p2identical.c
	gcc $(CFLAGS) -o $@ p2.c p2identical.c

p3.2: p3.2.c
	gcc $(CFLAGS) -o $@ p3.2.c

p4: p4.c
	gcc $(CFLAGS) -o $@ p4.c

clean:
	rm -f p1 p2 p3.2 p4 *.o
