CXX=g++
CXXFLAGS= -Wall -std=c++11 -pedantic

all: prueba-auto prueba-consola

prueba-auto: prueba-auto.o cadena.o
	$(CXX) -o $@ $(CXXFLAGS) $^

prueba-consola: prueba-consola.o cadena.o
	$(CXX) -o $@ $(CXXFLAGS) $^

prueba-auto.o: cadena.h fct.h

prueba-consola.o: cadena.h

clean:
	$(RM) -f *~ *.o prueba-auto prueba-consola
