BUILDDIR := build
FLAGS = -pedantic-errors -std=c++11

$(BUILDDIR)/io.o: io.cpp io.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/mob.o: mob.cpp mob.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/event.o: event.cpp event.h io.o
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/saveload.o: saveload.cpp saveload.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	g++ $(FLAGS) -c $< -o $@

OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/event.o $(BUILDDIR)/mob.o $(BUILDDIR)/io.o $(BUILDDIR)/saveload.o

$(BUILDDIR)/main: $(OBJECTS)
	g++ $(FLAGS) $^ -o $@

clean_o:
	rm -f $(OBJECTS)

clean_a:
	rm -f $(BUILDDIR)/main $(OBJECTS)

clean:
	rm -f $(BUILDDIR)/main

.PHONY: clean clean_o clean_a
