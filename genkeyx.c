#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

/*
 * genkeyx (C)2024 by Jan-Piet Mens <jp@mens.de>
 * generate a SHA256 from 32 random bytes, and produce an XML
 * *.keyx file suitable for protecting a KeePassXC database
 * file.
 */

#define SIZE 32

struct kx {
	char *hash4;		/* 4 left-most octets of SHA256 */
	char *line1;		/* line1 of pretty hex */
	char *line2;		/* line2 of pretty hex */
};

/*
 * hash4 is a buffer long enough for the 4 left-most octets of the SHA256
 * string. line1 and line2 are strings which will receive the "pretty-printed"
 * octets of random data (32 bytes in total). Quoting the KeePassXC source code:
 *
 * Pretty-print hex value (not strictly necessary, but nicer to read and KeePass2 does it)
 */

bool keyx(struct kx *kx)
{
	unsigned char randbytes[SIZE];
	unsigned char shabuf[SIZE];
	char *tp;
	int n;

	kx->hash4 = calloc(SIZE, sizeof(char));
	kx->line1 = calloc(SIZE*2, sizeof(char));
	kx->line2 = calloc(SIZE*2, sizeof(char));

	if (!kx->hash4 || !kx->line1 || !kx->line2) {
		fprintf(stderr, "ENOMEM\n");
		return false;
	}

	if (RAND_bytes(randbytes, SIZE) != 1) {
		fprintf(stderr, "Can't get RAND_bytes\n");
		return false;
	}

	if (SHA256(randbytes, SIZE, shabuf) == NULL) {
		fprintf(stderr, "Can't SHA256\n");
		return false;
	}

	/* The first 4 bytes from the SHA256 */
	for (n = 0, *kx->hash4 = 0; n < 4; n++) {
		sprintf(kx->hash4 + (n * 2), "%02X", shabuf[n]);
	}

	tp = kx->line1;
	for (n = 0; n < SIZE; n++) {
		if (n > 0 && n % 4 == 0) {
			*tp++ = ' ';
			*tp = 0;
		}
		if (n > 0 && n % 16 == 0) {
			*tp = 0;
			tp = kx->line2;
		}
		sprintf(tp, "%02X", randbytes[n]);
		tp += 2;
	}

	return true;
}

int main(int argc, char **argv)
{
	int ch;
	FILE *fp = stdout;
	struct kx kx;

	while ((ch = getopt(argc, argv, "o:")) != EOF) {
		switch (ch) {
			case 'o':
				if ((fp = fopen(optarg, "w")) == NULL) {
					perror(optarg);
					return 1;
				}
				break;
			default:
				fprintf(stderr, "Usage: %s [-o file]\n", *argv);
				return 1;
		}
	}

	if (keyx(&kx) == false) {
		fprintf(stderr, "%s: cannot generate keyx bits\n", *argv);
		return 1;
	}

	/*
	 * Template the resulting XML; as I'm not going to add
	 * any special characters, nothing can possibly go wron--
	 */

	fprintf(fp, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n\
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
</KeyFile>\n", kx.hash4, kx.line1, kx.line2);

	free(kx.hash4);
	free(kx.line1);
	free(kx.line2);
	return 0;
}
