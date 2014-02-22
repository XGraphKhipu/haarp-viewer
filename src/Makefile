#
CPP = gcc-4.4
P = -Wall -lcgi -lmysqlclient -ldl -O2
OBJECT = logfile.o report.o utils.o

ALL: report main

report: $(OBJECT)
	$(CPP) $(OBJECT) $(P) -o report.cgi

main: haarp.c 
	$(CPP) haarp.c $(P) -o haarp.cgi 

%.o: %.c %.h
	$(CPP) $(P) -c -o $@ $<

clean:
	rm -f *.cgi *.o
