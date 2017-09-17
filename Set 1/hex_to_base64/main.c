#include "hex_to_base64.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	uint8_t *plaintext;

	if (argc != 2) {
		printf("Invalid number of arguments passed to the program.\n");
		exit(EXIT_FAILURE);
	}

	plaintext = hex_to_bytes(argv[1]);
	
	/* Printing decoded hexadecimal text */
	printf("Decoded text = %s\n", plaintext);

	/* Free dynamically allocated resources */
	free(plaintext);

	exit(EXIT_SUCCESS);
}
