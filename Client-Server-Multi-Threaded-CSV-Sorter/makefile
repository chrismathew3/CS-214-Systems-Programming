serv:
	gcc -pthread -o server server.c
	./server -p 3490
cli:
	gcc -pthread -o client client.c
local:
	./client -c director_name -h localhost -p 3490 -d yerr1


ilab:
	./client -c director_name -h utility.cs.rutgers.edu -p 3490 -d yerr1

clean: 
	rm -f server
	rm -f client
	rm -f *.o
	rm -f *.out
	rm -f *.txt
	rm -f master.csv