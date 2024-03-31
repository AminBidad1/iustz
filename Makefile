CC = g++
CFLAGS  = -g -Wall
export dependencies
export objects

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

%.o: libs/%.hpp libs/%.cpp %.gch $(dependencies)
	$(CC) -fPIC -c $(CFLAGS) $(CPPFLAGS) libs/$*.cpp -o $*.o $(dependencies)

%.gch: libs/%.hpp
	$(CC) -fPIC -c $(CFLAGS) $(CPPFLAGS) libs/$*.hpp -o $*.gch 

main: main.o $(objects)
	$(CC) $(CFLAGS) -o main main.o $(objects)

run: main
	./main

clean:
	rm -f main main.o

clear:
	rm -f main *.o
