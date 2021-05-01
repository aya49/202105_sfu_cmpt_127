imgC: driver.c image.c
	gcc -std=c99 -o $@ driver.c image.c

img1: driver.cpp image.cpp
	g++ -o $@ driver.cpp image.cpp

img2: main.cpp image2.cpp
	g++ -o $@ main.cpp image2.cpp

img3: main.cpp image3.cpp
	g++ -o $@ main.cpp image3.cpp

# $ make clean
#  - removes files we built using the targets above
clean:
	rm -f img* *.o