# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Werror -Wfatal-errors -g


t1: t1.c t1img.c
	gcc $(CFLAGS) -o $@ t1.c t1img.c

t2: t2.c t2img.c
	gcc $(CFLAGS) -o $@ t2.c t2img.c

t3: t3.c t3img.c
	gcc $(CFLAGS) -o $@ t3.c t3img.c

submit:
	rm -f a.zip
	zip a.zip t1.c t1img.c t2.c t2img.c t3.c t3img.c

clean:
	rm -f t1 t2 t3 *.o
