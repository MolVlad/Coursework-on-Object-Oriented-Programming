.PHONY: all clean install uninstall
all: test
clean:
	rm -rf test *.o
test.o: test.cpp 
	g++ -c -Weffc++ -o test.o test.cpp
vector2.o: vector2.cpp
	g++ -c -Weffc++ -o vector2.o vector2.cpp
test: test.o vector2.o
	g++ test.o vector2.o -o test
install: 
	install ./game/usr/local/bin
uninstall:
	rm -rf /usr/local/bin/test
