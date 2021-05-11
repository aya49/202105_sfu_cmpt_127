# -Wextra turns on even more warnings
# -Werror treats warnings as if they were errors (stopping compilation)
# -Wfatal-errors causes compilation to stop after the first error
# -g adds debugging information to the file
CFLAGS = -Wextra -Werror -Wfatal-errors -g


t1: t1.c
	gcc $(CFLAGS) -o $@ t1.c

t2: t2.c t2mirror.c
	gcc $(CFLAGS) -o $@ t2.c t2mirror.c

t3: t3.c
	gcc $(CFLAGS) -o $@ t3.c

t4: t4.c
	gcc $(CFLAGS) -o $@ t4.c

submit:
	rm -f a.zip
	zip a.zip t1.c t1funcs.h t2mirror.c t3.c t4.c

clean:
	rm -f t1 t2 t3 t4 *.o
