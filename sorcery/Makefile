CXX = g++-5
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = main
OBJECTS = main.o card.o enchantment.o minion.o observer.o player.o ritual.o spell.o subject.o cardtype.o specifiability.o specificenchantments.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
