# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Werror -Wfatal-errors -g


p0: p0.c p0intarr.c
	gcc $(CFLAGS) -o $@ p0.c p0intarr.c

clean:
	rm -f p0 *.o
