CC=gcc
CXX=g++
RM=rm -f

SRCS=CodigoDemocratico.cpp Aplicacao.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: CodigoDemocratico

CodigoDemocratico: CodigoDemocratico.o Aplicacao.o
	$(CXX) CodigoDemocratico.o Aplicacao.o -o CodigoDemocratico

CodigoDemocratico.o: CodigoDemocratico.h CodigoDemocratico.cpp

Aplicacao.o: Aplicacao.cpp

clean:
	$(RM) $(OBJS)

dist-clean: clean
	$(RM) CodigoDemocratico
