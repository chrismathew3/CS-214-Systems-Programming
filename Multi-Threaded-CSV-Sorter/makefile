all: sorter

sorter: sorter.c sorter.h mergesort.c
	gcc -pthread -o sorter sorter.c

test:
	./sorter -d yerr -o yerr -c director_name
clean:
	rm -f sorter
	rm -f *.o
	rm -f *.out
	rm -f *.txt