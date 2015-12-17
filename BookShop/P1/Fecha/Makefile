CXX=g++
CXXFLAGS= -Wall -std=c++98 -pedantic

all: prueba-auto prueba-consola

prueba-auto: prueba-auto.o fecha.o
	$(CXX) -o $@ $(CXXFLAGS) $^

prueba-consola: prueba-consola.o fecha.o
	$(CXX) -o $@ $(CXXFLAGS) $^

prueba-auto.o: fecha.h fct.h

prueba-consola.o: fecha.h

clean:
	$(RM) -f *~ *.o prueba-auto prueba-consola
 
