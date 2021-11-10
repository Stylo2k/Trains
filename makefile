CC     = gcc
CFLAGS = -O2 -std=c99 -pedantic -Wall -Wno-unused-result

graph: graphMain.c libGraph.c
	$(CC) $(CFLAGS) $^ -g -o $@
	
main: main.c libGraph.c dijkstra.c
	$(CC) $(CFLAGS) $^ -g -o $@

test: main
	./main < testCase1.txt

debug: main
	#valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s ./main < testCase1.txt
	valgrind --error-exitcode=111 --leak-check=full --track-origins=yes ./main < testCase1.txt

time: main
	time ./main < testCase1.txt

clean:
	rm main
	clear
