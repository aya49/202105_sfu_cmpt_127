# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Werror -Wfatal-errors -g


p1: p0name.c
	gcc $(CFLAGS) -o $@  p0name.c

p0random: p0random.c
	gcc $(CFLAGS) -o $@  p0random.c

clean:
	rm -f p1 p0random *.o
