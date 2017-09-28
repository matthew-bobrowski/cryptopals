#include "hex_to_base64.h"
#include <stdio.h>

int main(int argc, char **argv)
{

	static const char *result = "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t";
	static const char *input =
"49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368727f6f6d";

	uint8_t *bytes = NULL;
	uint8_t *base64 = NULL;

	if (argc != 2) {
		printf("Invalid number of arguments passed to the program.\n");
		exit(EXIT_FAILURE);
	}

	/* TODO: 
	 * Perform some validation tests on command line argument passed
 	 * to function.
	 */
	bytes = hex_to_bytes(argv[1]);

	if (bytes == NULL) {
		printf("Hexadecimal string has not been decoded correctly. Aborting\n");
		free(bytes);
		exit(EXIT_FAILURE);
	}

	base64 = bytes_to_base64((char *) bytes);

	printf("Hexadecimal input string:\n\t%s\n", input);	
	printf("Expected result:\n\t%s\n", result);
	printf("Program result:\n\t%s\n", base64);
	free(bytes);
	free(base64);

	exit(EXIT_SUCCESS);
}
