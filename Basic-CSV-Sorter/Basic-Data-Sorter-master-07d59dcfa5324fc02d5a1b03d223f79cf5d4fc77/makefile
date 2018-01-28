all: sorter

sorter: sorter.c sorter.h
	gcc -o sorter sorter.c

test:
	cat movie_metadata.csv | ./sorter -c director_name > sorted.txt

clean:
	rm -f sorter
	rm -f *.o
	rm -f *.out
	rm -f *.txt