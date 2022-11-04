BUILDDIR := build
FLAGS = -pedantic-errors -std=c++11

$(BUILDDIR)/out.o: out.cpp out.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/mob.o: mob.cpp mob.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/event.o: event.cpp event.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	g++ $(FLAGS) -c $< -o $@

OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/event.o $(BUILDDIR)/mob.o $(BUILDDIR)/out.o

$(BUILDDIR)/main: $(OBJECTS)
	g++ $(FLAGS) $^ -o $@

clean_o:
	rm -f $(OBJECTS)

clean_a:
	rm -f $(BUILDDIR)/main $(OBJECTS)

clean:
	rm -f $(BUILDDIR)/main

.PHONY: clean clean_o clean_a
