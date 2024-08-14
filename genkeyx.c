#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

/*
 * genkeyx (C)2024 by Jan-Piet Mens <jp@mens.de>
 * generate a SHA256 from 32 random bytes, and produce an XML
 * *.keyx file suitable for protecting a KeePassXC database
 * file.
 */

#define SIZE 32

/*
 * hash4 is a buffer long enough for the 4 left-most octets of the SHA256
 * string. line1 and line2 are strings which will receive the "pretty-printed"
 * octets of random data (32 bytes in total). Quoting the KeePassXC source code:
 *
 * Pretty-print hex value (not strictly necessary, but nicer to read and KeePass2 does it)
 */

bool keyx(char *hash4, char *line1, char *line2)
{
	unsigned char randbytes[SIZE];
	unsigned char shabuf[SIZE];
	char *tp = line1;
	int n;

	if (RAND_bytes(randbytes, SIZE) != 1) {
		fprintf(stderr, "Can't get RAND_bytes\n");
		return false;
	}

	if (SHA256(randbytes, SIZE, shabuf) == NULL) {
		fprintf(stderr, "Can't SHA256\n");
		return false;
	}

	/* The first 4 bytes from the SHA256 */
	for (n = 0, *hash4 = 0; n < 4; n++) {
		sprintf(hash4 + (n * 2), "%02X", shabuf[n]);
	}

	tp = line1;
	for (n = 0; n < SIZE; n++) {
		if (n > 0 && n % 4 == 0) {
			*tp++ = ' ';
			*tp = 0;
		}
		if (n > 0 && n % 16 == 0) {
			*tp = 0;
			tp = line2;
		}
		sprintf(tp, "%02X", randbytes[n]);
		tp += 2;
	}

	return true;
}

int main()
{
	static char hash4[10], line1[128], line2[128];

	keyx(hash4, line1, line2);

	/*
	 * Template the resulting XML; as I'm not going to add
	 * any special characters, nothing can possibly go wron--
	 */

	printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
<KeyFile>\n\
    <Meta>\n\
        <Version>2.0</Version>\n\
    </Meta>\n\
    <Key>\n\
        <Data Hash=\"%s\">\n\
            %s\n\
            %s\n\
        </Data>\n\
    </Key>\n\
</KeyFile>\n", hash4, line1, line2);

	return 0;
}
