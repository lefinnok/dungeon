BUILDDIR := build
FLAGS = -pedantic-errors -g

$(BUILDDIR)/io.o: io.cpp io.hpp databases.hpp
	g++ $(FLAGS) -c $< -o $@ -lncursesw

$(BUILDDIR)/mob.o: mob.cpp mob.h databases.hpp
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/event.o: event.cpp event.hpp io.o databases.hpp
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/saveload.o: saveload.cpp saveload.hpp databases.hpp
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	g++ $(FLAGS) -c $< -o $@

OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/event.o $(BUILDDIR)/mob.o $(BUILDDIR)/io.o $(BUILDDIR)/saveload.o

$(BUILDDIR)/main: $(OBJECTS)
	g++ $(FLAGS) $^ -o $@ -lncursesw

clean_o:
	rm -f $(OBJECTS)

clean_a:
	rm -f $(BUILDDIR)/main $(OBJECTS)

clean:
	rm -f $(BUILDDIR)/main

.PHONY: clean clean_o clean_a
