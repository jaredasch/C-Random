all: dev_random.o
	gcc -o out dev_random.o

dev_random.o: dev_random.c
	gcc -c dev_random.c

run:
	./out

clean:
	rm out
	rm *.o