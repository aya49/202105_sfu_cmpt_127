# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS := -Werror -Wfatal-errors -g


t0: t0.c t0img.c
	gcc $(CFLAGS) -o $@ t0.c t0img.c

submit:
	rm -f a.zip
	zip a.zip t0.c t0img.c

clean:
	rm -f t0 *.o
