#include "hex_to_base64.h"
#include <stdio.h>

/**
 * Funciton that is responsible for converting a hexadecimal string that is
 * passed to the program as argument into a Base 64 encoded string.
 */
static uint8_t
*hex_to_base64(char *hex_str)
{
	uint8_t *bytes, *base64;

	bytes = hex_to_bytes((char *) hex_str);
	base64 = bytes_to_base64((char *) bytes);
	free(bytes);
	
	return base64;
}

int 
main(int argc, char **argv)
{
	size_t length = 0;	
	uint8_t *base64 = NULL;

	if (argc != 2) {
		printf("Invalid number of arguments passed to the program. " \
			"Aborting program.\n");
		exit(EXIT_FAILURE);
	}

	if ((length = strlen(argv[1])) % 2 != 0) {
		printf("Invalid hexadecimal string passed to the program. " \
			"Aborting program.\n");
		exit(EXIT_FAILURE);
	}

	base64 = hex_to_base64(argv[1]);
	
	if (base64 != NULL) {
		printf("original hexadecimal encoded string:\n\t%s\n", argv[1]);
		printf("base64 encoded string:\n\t%s\n", base64);
		free(base64);
	}

	exit(EXIT_SUCCESS);
}
