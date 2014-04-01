#
#  Makefile for Matt 
#


LIBDIR =  -Wl,-rpath,-lm  -ltiff

CFLAGS = -g3 -Wno-deprecated

CC = g++

.SUFFIXES: .o .cpp

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<


ALL.O =  matt.o figio.o matrix.o

matt: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f $(ALL.O) matt *~
