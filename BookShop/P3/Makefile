# Makefile para el caso 3 de la LIBRERÍA
# ©2010-2014 Los profesores de POO
#
# --- Parte configurable ---
#
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las
# prácticas de POO (C++). Dentro de ese directorio debe haber uno para
# cada práctica llamado NOMBREPRACTICA, que será de la forma P<n>,
# siendo <n> el número de práctica: P0, P1, etc.

NOMBREALUMNO   = Diaz_Fuentes_Maria
NOMBREPRACTICA = P3

# CADENADIR y FECHADIR son los directorios donde están respectivamente
# los módulos objeto y cabeceras de Cadena y Fecha: cadena.{oh} y fecha.{oh}.
DIRFECHACADENA=P1
CADENADIR= ../${DIRFECHACADENA}/Cadena
FECHADIR = ../${DIRFECHACADENA}/Fecha

# ¿Compilador C++ de LLVM (clang++) o de GNU (g++)?
#CXX      = clang++
CXX	 = g++

# ¿Qué estándar seguir?
# ansi o c++98 o c++03: estándar de 1998, corregido en 2003
# c++0x: borrador del estándar de 2011
# c++11: estándar actual de 2011
# c++1y: sgute. revisión (¿2014-2017?)
STD=c++11

ifeq (${CXX},clang++)
  CXXFLAGS = -g -Wall -std=${STD} ${INCLUDES}
else
  CXXFLAGS = -g -pedantic -Wall -std=${STD} ${INCLUDES}
endif

# --- Fin parte configurable

INCLUDES  = -I${CADENADIR} -I${FECHADIR}
LOCALLIBS = ${CADENADIR}/cadena.o ${FECHADIR}/fecha.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${CADENADIR}:${FECHADIR}

COMM_SRCS = usuario.cpp tarjeta.cpp articulo.cpp \
	pedido.cpp pedido-articulo.cpp luhn.cpp
MAIN_SRCS = $(COMM_SRCS) test-caso3-consola.cpp
MAIN_OBJS = $(MAIN_SRCS:.cpp=.o)
MAIN_EXE  = test-caso3-consola
TEST_SRCS = $(COMM_SRCS) test-caso3-auto.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXE  = test-caso3-auto

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

## OBJETIVOS PRINCIPALES #######################################################

.PHONY: all clean dist distclean test-consola test-auto

all: ${MAIN_EXE} ${TEST_EXE}

test-consola: ${MAIN_EXE}
	./$<

test-auto: ${TEST_EXE}
	./$<

clean:
	${RM} ${RMFLAGS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
		*.d *.{aux,log,dvi,toc} *~ \#*
	(cd ${FECHADIR}; make clean)
	(cd ${CADENADIR}; make clean)

## COMPILACIÓN #################################################################

${MAIN_EXE}: ${MAIN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

${TEST_EXE}: ${TEST_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

# Detección automática de dependencias en código fuente C++ con GCC C++ #

%.d: %.cpp
	@$(CXX) -MM $(CXXFLAGS) $< > $@
	@sed -ri 's,($*)\.o[ :]*,\1.o $@ : ,g' $@

-include $(MAIN_SRCS:.cpp=.d) $(TEST_SRCS:.cpp=.d)

## EMPAQUETADO #################################################################

${NOMBRETAR}: ${SRCS} ${HDRS}
ifeq ($(strip $(NOMBREALUMNO)),)
	@echo ""
	@echo "ATENCIÓN: debe definir en el Makefile la variable NOMBREALUMNO"
	@echo "con el nombre del directorio superior a este."
	@echo " Vea las instrucciones de entrega de las prácticas."
else
	tar -cvz -C../.. -f ${NOMBRETAR} ${NOMBREDIR} \
				${NOMBREALUMNO}/${DIRFECHACADENA}
endif

# Esto lo deberían usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: clean ${NOMBRETAR}

distclean: clean
	${RM} ${RMFLAGS} ${NOMBRETAR}

