FLAGS = -pedantic-errors -std=c++11

event.o: event.cpp event.h
	g++ $(FLAGS) -c $<

main.o: main.cpp
	g++ $(FLAGS) -c $<

main: main.o d2boh.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f main main.o d2boh.o

.PHONY: clean
