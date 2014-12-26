MINERVA_ROOT ?= /usr/local/minerva
BINDIR = /usr/local/bin

CFLAGS = -O2 -Wall -DDATA_DIR='"$(MINERVA_ROOT)"'
HEADERS = latin.h verb.h nominal.h nomtab.h verbtab.h part.h data.h

%.o: %.c $(HEADERS)
	$(CC) -c -o $@ $< $(CFLAGS) 

default: minerva

minerva: main.o latin.o verb.o nominal.o part.o data.o
	$(CC) -o $@ $^

makeindex: makeindex.o data.o
	$(CC) -o $@ $^

install: minerva makeindex
	mkdir -p $(MINERVA_ROOT)
	install minerva makeindex $(MINERVA_ROOT)
	install -m 644 *.dat $(MINERVA_ROOT)
	( cd $(MINERVA_ROOT); ./makeindex )
	ln -sf $(MINERVA_ROOT)/minerva $(BINDIR)
	install -m 644 minerva.txt $(MINERVA_ROOT)/

clean:
	rm -f *.o core minerva makeindex
