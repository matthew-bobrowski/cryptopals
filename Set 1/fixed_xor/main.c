/*
 * This source file contains the functions that are responsible for producing
 * the xor'd output value given two equal length hexdecimal encoded buffers.
 * This code has been purely written in order to solve the challenges posted on
 * the Cryptopals website. More information about the Fixed XOR challenge can be
 * found here <http://cryptopals.com/sets/1/challenges/2>.
 *
 * Author: Matthew Bobrowski <mbobrowski@mbobrowski.org, mbobrowski@au1.ibm.com>
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>

/*
 * Utility function that converts a hexdecimal character into a nibble.
 */
static uint8_t
char_to_nibble(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 225;
}

/*
 * Function that decodes a hexdecimal encoded string into a raw byte array.
 */
static uint8_t
*hex_to_bytes(char *hexadecimal, size_t *length)
{
	size_t i;
	uint8_t *p, *bytes;
	*length = strlen(hexadecimal) / 2;

	bytes  = malloc(*length + 1);

	if (bytes == NULL)
		return NULL;

	for (i = 0, p = (uint8_t *) hexadecimal; i < *length; i++) {
		bytes[i] = (char_to_nibble(*p) << 4) | char_to_nibble(*(p + 1));
		p += 2;
	}

	bytes[*length] = '\0';

	return bytes;
}

/*
 * Function that is responsible for caculating the xor value of two equal length
 * buffers.
 */
static uint8_t
*xor(char **input)
{
	size_t length, a_len, b_len;
	uint8_t *xor, *a, *b;

	a = hex_to_bytes(input[1], &a_len);
	b = hex_to_bytes(input[2], &b_len);

	if ((a == NULL) || (b == NULL))
		return NULL;

	length = ((a_len + b_len) / 2);
	xor = malloc(length + 1);

	if (xor == NULL)
		return NULL;

	for (size_t i = 0; i < length; i++) {
		xor[i] = a[i] ^ b[i];
	}

	free(a);
	free(b);

	xor[length] = '\0';

	return xor;
}

/*
 * Print byte array in hexadecimal format.
 */
static void
print_buffer(uint8_t *buffer)
{
	if (buffer == NULL) return;

	for (size_t i = 0, length = strlen((char *) buffer); i < length; i++) {
		printf("%02x", buffer[i]);
	}
	printf("\n");
}

int
main(int argc, char **argv)
{
	uint8_t *result = NULL;

	// check whether correct number of command line arguments passed to the
	// program
	if (argc != 3) {
		printf("Invalid number of arguments passed to the program. " \
			"Terminating program.\n");
		exit(EXIT_FAILURE);
	}

	// calculate length of buffers provided to program
	size_t a_len = strlen(argv[1]);
	size_t b_len = strlen(argv[2]);

	// determine whether the hexadecimal encoded buffers passed to the program are of equal length
	if (a_len != b_len) {
		printf("Buffers provided as arguments to the program are not" \
			" of equal length.\nTerminating program.\n");
		exit(EXIT_FAILURE);
	}

	// determine whether the arguments passed to the program are
	// hexadecimal encoded strings
	if ((a_len % 2 != 0) || (b_len % 2 != 0)) {
		printf("Buffers provided to the program don't appear to "  \
			"hexadecimal encoded. Please ensure that they're " \
			"valid.\n");
		exit(EXIT_FAILURE);
	}

	result = xor(argv);

	if (result == NULL) {
		printf("Error producing fixed xor valued string.\n");
		exit(EXIT_FAILURE);
	}

	print_buffer(result);

	free(result);
	exit(EXIT_SUCCESS);
}
