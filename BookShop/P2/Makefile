# Makefile para la práctica 2, caso de uso 1 de la librería electrónica
# ©2009-2014 Los profesores de POO
#
#--- Parte configurable
# NOMBREALUMNO es el nombre del directorio donde el alumno guarda las prácticas
# de POO (C++). Dentro de ese directorio debe haber uno para cada práctica 
# llamado NOMBREPRACTICA, que será de la forma P<n>, siendo <n> el número 
# de práctica: P1, P2, etc.
# NOMBREALUMNO debería ser de la forma: Ap1_Ap2_NP 
# (Véanse las instrucciones de entrega).
NOMBREALUMNO   = "Diaz_Fuentes_Maria"
NOMBREPRACTICA = P2

# CADENADIR y FECHADIR son los directorios donde están respectivamente
# los Makefile, módulos objeto y cabeceras de Cadena y Fecha: 
# Makefile, cadena.{oh} y fecha.{oh}.
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
  CXXFLAGS = -g -Weverything -std=${STD} ${INCLUDES}
else
  CXXFLAGS = -g -pedantic -Wall -std=${STD} ${INCLUDES}
endif
# --- Fin parte configurable

INCLUDES  = -I${CADENADIR} -I${FECHADIR}
LOCALLIBS = cadena.o fecha.o
EXTLIBS   = -lcrypt
LIBS      = ${LOCALLIBS} ${EXTLIBS}
VPATH     = .:${CADENADIR}:${FECHADIR}

COMM_HDRS = usuario.h tarjeta.h articulo.h
COMM_SRCS = usuario.cpp tarjeta.cpp articulo.cpp luhn.cpp Makefile
COMM_OBJS = usuario.o tarjeta.o articulo.o luhn.o
MAIN_SRCS = $(COMM_SRCS) test-caso1-consola.cpp
MAIN_OBJS = $(COMM_OBJS) test-caso1-consola.o
MAIN_EXE  = test-caso1-consola
MAIN_SRCS = $(COMM_SRCS) test-caso1-auto.cpp
TEST_OBJS = $(COMM_OBJS) test-caso1-auto.o
TEST_EXE  = test-caso1-auto
SRCS      = $(MAIN_SRCS)
HDRS      = $(COMM_HDRS)

NOMBRETAR = ../../${NOMBREALUMNO}.tar.gz
NOMBREDIR = ${NOMBREALUMNO}/${NOMBREPRACTICA}

all: ${MAIN_EXE} ${TEST_EXE}

test-consola: ${MAIN_EXE}
	./$<

test-auto: ${TEST_EXE}
	./$<

${MAIN_EXE}: ${MAIN_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

${TEST_EXE}: ${TEST_OBJS} ${LOCALLIBS}
	${CXX} -o $@ ${LDFLAGS} $^ ${EXTLIBS}

${MAIN_OBJS}: ${COMM_HDRS}

${TEST_OBJS}: ${COMM_HDRS}

clean:
	${RM} ${RMFLAGS} ${MAIN_EXE} ${MAIN_OBJS} ${TEST_EXE} ${TEST_OBJS} \
			 ${LOCALLIBS} *.{aux,log,dvi,toc} *~ \#*
	make -C ${CADENADIR} clean
	make -C ${FECHADIR}  clean

# Esto lo deberían usar los alumnos a la hora de la entrega:
# crea el archivo .tar.gz en el directorio padre tras borrar lo sobrante.
dist: clean ${NOMBRETAR}

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

distclean: clean
	${RM} ${RMFLAGS} ${NOMBRETAR}

.PHONY: all clean dist distclean
