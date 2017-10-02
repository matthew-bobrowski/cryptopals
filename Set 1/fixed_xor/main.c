/**
 * Author: Matthew Bobrowski <mbobrowski@mbobrowski.org, mbobrowski@au1.ibm.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

static uint8_t
char_to_nibble(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 225;
}

uint8_t
*hex_to_bytes(char *hex)
{
	size_t i;
	uint8_t *p, *bytes;
	size_t length = strlen(hex) / 2;

	bytes  = malloc(length + 1);

	for (i = 0, p = (uint8_t *) hex; i < length; i++) {
		bytes[i] = (char_to_nibble(*p) << 4) | char_to_nibble(*(p + 1));
		p += 2;
	}

	bytes[length] = 0;

	return bytes;
}

uint8_t
*xor(char *hex_a, char *hex_b)
{
	// This function is still not completed. Further work needs to be performed
	size_t i, a_len, b_len, length;
	uint8_t *a, *b, *xor;

	a = hex_to_bytes(hex_a);
	b = hex_to_bytes(hex_b);

	a_len = strlen(a);
	b_len = strlen(b);

	length = ((a_len + b_len) / 2);
	xor = malloc(length + 1);

	if (xor == NULL) return NULL;

	for (i = 0; i < length; i++) {
		xor[i] = a[i] ^ b[i];
	}

	xor[length] = 0;

	return xor;
}

int
main(int argc, char **argv)
{
	uint8_t *fixed_xor;

	if (argc != 3) {
		printf("Invalid number of arguments passed to the program. " \
			"Terminating program.\n");
		exit(EXIT_FAILURE);
	}

	// argv[1] and argv[2] should both be hexadecimal encoded. Basic check performed on length of the two buffers provided.
	size_t a_length = strlen(argv[1]);
	size_t b_length = strlen(argv[2]);

	if ((a_length % 2 != 0) || (b_length % 2 != 0)) {
		printf("Invalid hexadecimal string provided to the program. " \
			"Terminating program\n");
		exit(EXIT_FAILURE);
	}

	// check whether the two buffers provided are of equal length. If unequal terminate program.
	if (a_length != b_length) {
		printf("Buffers provided to the program must be of equal length. Terminating program.\n");
		exit(EXIT_FAILURE);
	}

	fixed_xor = xor(argv[1], argv[2]);

	for (size_t i = 0, length = strlen(fixed_xor); i < length; i++) {
		printf("%" PRIxLEAST8, (fixed_xor[i] & 0xFF));
	}
	printf("\n");

	exit(EXIT_SUCCESS);
}
