
OPENSSL=/opt/homebrew/Cellar/openssl@1.1/1.1.1w/
OPENSSL=/usr/local/Cellar/openssl\@1.1/1.1.1w/
PANDOC=/usr/local/bin/pandoc


CFLAGS=-Wall -I$(OPENSSL)/include
LDFLAGS=-L $(OPENSSL)/lib -lcrypto

all: genkeyx

doc: genkeyx.1 genkeyx.md

genkeyx: genkeyx.c
	$(CC) $(CFLAGS) -o genkeyx genkeyx.c $(LDFLAGS)

clean:
	rm -f *.o
clobber: clean
	rm -f genkeyx

genkeyx.1: genkeyx.pandoc
	$(PANDOC) -s -w man -f markdown -o $@ $<

genkeyx.md: genkeyx.pandoc
	$(PANDOC) -s -w gfm -f markdown-smart -o $@ $<
