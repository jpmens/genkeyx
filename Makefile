
OPENSSL=/opt/homebrew/Cellar/openssl@1.1/1.1.1w/


CFLAGS=-Wall -I$(OPENSSL)/include
LDFLAGS=-L $(OPENSSL)/lib -lcrypto

all: genkeyx

genkeyx: genkeyx.c
	$(CC) $(CFLAGS) -o genkeyx genkeyx.c $(LDFLAGS)

clean:
	rm -f *.o
clobber: clean
	rm -f genkeyx

