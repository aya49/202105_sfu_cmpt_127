
all: t1 t2 t3 t4 t5

t1: main.c t1.c
	gcc -Wall -std=c99 -o $@ main.c t1.c

t2: main.c t2.c
	gcc -Wall -std=c99 -o $@ main.c t2.c

t3: main.c t3.c
	gcc -Wall -std=c99 -o $@ main.c t3.c

t4: main.c t4.c
	gcc -Wall -std=c99 -o $@ main.c t4.c

t5: main.c t5.c
	gcc -Wall -std=c99 -o $@ main.c t5.c

clean:
	rm -f t1 t2 t3 t4 t5 *.o
