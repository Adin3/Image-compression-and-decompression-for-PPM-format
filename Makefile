# NEACSU ADRIAN - 314CD

build: main.o tree.o queue.o
	gcc -Wall -Werror -g main.o tree.o queue.o -o quadtree
	@echo "Build Program"

main.o: main.c tree.h functions.h
	gcc -Wall -Werror -g -c main.c -o main.o

tree.o: tree.c tree.h
	gcc -Wall -Werror -g -c tree.c -o tree.o

queue.o: queue.c queue.h
	gcc -Wall -Werror -g -c queue.c -o queue.o

clean:
	@echo "Clean Program"
	@rm -f quadtree main.o tree.o queue.o
