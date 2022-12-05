BUILDDIR := build
MOBBUILD := mobbuild
FLAGS = -pedantic-errors -g --std=c++17 -lstdc++fs

$(BUILDDIR)/databases.o: databases.cpp databases.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/io.o: io.cpp io.h databases.h
	g++ $(FLAGS) -c $< -o $@ -lncursesw

$(BUILDDIR)/uielements.o: uielements.cpp uielements.h io.cpp io.h databases.h
	g++ $(FLAGS) -c $< -o $@ -lncursesw

$(BUILDDIR)/screens.o: screens.cpp screens.h io.cpp io.h uielements.cpp uielements.h databases.h
	g++ $(FLAGS) -c $< -o $@ -lncursesw

#$(BUILDDIR)/items.o: items.cpp items.h mob.cpp mob.h databases.h
#	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/mob.o: mob.cpp mob.h items.cpp items.h databases.h
	g++ $(FLAGS) -c $< -o $@ -lncursesw

$(BUILDDIR)/event.o: event.cpp event.h io.o databases.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/saveload.o: saveload.cpp saveload.h databases.h
	g++ $(FLAGS) -c $< -o $@

$(BUILDDIR)/main.o: main.cpp
	g++ $(FLAGS) -c $< -o $@

OBJECTS = $(BUILDDIR)/main.o $(BUILDDIR)/databases.o $(BUILDDIR)/io.o $(BUILDDIR)/uielements.o $(BUILDDIR)/mob.o $(BUILDDIR)/event.o ${BUILDDIR}/screens.o ${BUILDDIR}/saveload.o

$(BUILDDIR)/main: $(OBJECTS)
	g++ $(FLAGS) $^ -o $@ -lncursesw

${MOBBUILD}/mob: mob.cpp mob.h
	g++ ${FLAGS} $< -o $@ 

clean_o:
	rm -f $(OBJECTS)

clean_a:
	rm -f $(BUILDDIR)/main $(OBJECTS)

clean:
	rm -f $(BUILDDIR)/main

.PHONY: clean clean_o clean_a
