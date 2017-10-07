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

static uint8_t
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

	bytes[length + 1] = '\0';

	return bytes;
}

static void
print(uint8_t *buffer)
{
	if (buffer == NULL) return;

	for (size_t i = 0, length = strlen((char *) buffer); i < length; i++) {
		printf("%02x", buffer[i]);
	}
	printf("\n");
}

static uint8_t
*xor(char **input)
{
	size_t length, a_len, b_len;
	uint8_t *xor, *a, *b;

	a = hex_to_bytes(input[1]);
	b = hex_to_bytes(input[2]);

	size_t a_length = strlen(input[1]) / 2;
	size_t b_length = strlen(input[2]) / 2;

	length = ((a_length + b_length) / 2);

	xor = malloc(length + 1);

	for (size_t i = 0; i < length; i++) {
		xor[i] = a[i] ^ b[i];
	}

	xor[length] = '\0';

	free(a);
	free(b);

	return xor;
}

int
main(int argc, char **argv)
{
	uint8_t *result = NULL;

	if (argc != 3) {
		printf("Invalid number of arguments passed to the program. " \
			"Terminating program.\n");
		exit(EXIT_FAILURE);
	}

	result = xor(argv);

	if (result == NULL)
		exit(EXIT_FAILURE);

	print(result);

	free(result);

	exit(EXIT_SUCCESS);
}
