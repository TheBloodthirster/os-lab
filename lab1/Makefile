CC = g++
PROG = test
OBJ = dllist.o

$(PROG): $(OBJ)
	$(CC) -o $(PROG) dllist-driver.cc $(OBJ)

$(OBJ): dllist.h
	$(CC) -c dllist.cc dllist.h

clean:
	rm -rf *.o *.gch $(PROG)
