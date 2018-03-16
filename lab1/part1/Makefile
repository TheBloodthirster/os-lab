CC = g++
PROG = test
OBJ = dllist.o dllist-driver.o

$(PROG): $(OBJ)
	$(CC) -o $(PROG) main.cpp $(OBJ)

dllist-driver.o: dllist-driver.h 
	$(CC) -c dllist-driver.cc dllist-driver.h

dllist.o: dllist.h 
	$(CC) -c dllist.cc dllist.h

clean:
	rm -rf *.o *.gch $(PROG)
