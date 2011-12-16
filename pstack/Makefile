# Makefile for tigerc
# CS 441, Neil Moore
# 29 Apr 2000
#
# Requires GNU make: available on cslab as /usr/local/bin/make

.PHONY: depend clean mostlyclean pstmostlyclean tar all

YACC = bison -d -b y
LEX = flex
CXX = g++
CC = gcc

# Flags to use for both compiling and linking.
# See the top of symbtable.h for information on -DUSE_HASH_MAP
# and -DUSE_EXT_HASH_MAP.
CXXFLAGS = -g -Wall -pedantic
CFLAGS = -g -Wall -pedantic

# Flags that should be used for linking, but not for compiling.
LDFLAGS =
LIBS = -lfl

# Various files.
PSTOBJS = apmain.o apm.y.o apm.l.o
PSTHEADS = apm.h apname.h
BINS =api apd apm

all: $(BINS)

api: api.c $(PSTHEADS)
	$(CC) $(CFLAGS) $< -o $@ 

apd: apd.c $(PSTHEADS)
	$(CC) $(CFLAGS) $< -o $@ 

apm: $(PSTOBJS)
	$(CC) $(CFLAGS) $(PSTOBJS) -o $@ $(LDFLAGS) $(LIBS)

apm.y.c: apm.y
	$(YACC) -o apm.y.c $< 

apm.y.h: apm.y
	$(YACC) -o apm.y.c $<

apm.l.c: apm.l
	$(LEX) -oapm.l.c.old $<
	sed -e '/isatty/ d' < apm.l.c.old > apm.l.c
	-rm apm.l.c.old

clean: mostlyclean
	-rm -f $(BINS) $(PSTOBJS)

mostlyclean:
	-rm -f *.o apm.l.c apm.y.c apm.y.h

tar: $(TAR)


####### Implicit rules

.SUFFIXES: .cc

.cc.o:
	$(CXX) -c $(CXXFLAGS) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) -o $@ $<

####### Dependency generation

depend: $(GENSRCS) $(CXXSRCS)
	cp -f Makefile Makefile.bak
	$(CXX) -MM $(CXXSRCS) > depend.make
	$(CC) -MM $(GENSRCS) >> depend.make
	echo '/^# Do not delete this line/ +' > edscript
	echo '.,$$d' >> edscript
	echo 'r depend.make' >> edscript
	echo 'w' >> edscript
	ed Makefile < edscript
	rm edscript depend.make

# Do not delete this line---make depend depends on it.
#
