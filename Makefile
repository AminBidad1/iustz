CC = g++
CFLAGS  = -g -Wall
export objects

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

%.o: libs/%.hpp libs/%.cpp %.gch
	$(CC) -fPIC -c $(CFLAGS) $(CPPFLAGS) libs/$*.cpp -o $*.o

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
