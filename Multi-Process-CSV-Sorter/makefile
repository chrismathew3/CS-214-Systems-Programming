all: sorter

sorter: sorter.c sorter.h mergesort.c
	gcc -o sorter sorter.c

test:
	./sorter -c director_name -d /Users/chrismathew/Desktop/School/"Fall 2017"/"Systems Programming"/"Project 1"/"Project 2 Test"/"Test copy 512 items" -d /Users/chrismathew/Desktop/School/"Fall 2017"/"Systems Programming"/"Project 1"/Output
clean:
	rm -f sorter
	rm -f *.o
	rm -f *.out
	rm -f *.txt