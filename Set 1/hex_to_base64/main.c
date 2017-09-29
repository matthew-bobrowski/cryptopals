#include "hex_to_base64.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	
	char *base64 = NULL;

	if (argc != 2) {
		printf("Invalid number of arguments passed to the program.\n");
		exit(EXIT_FAILURE);
	}

	base64 = bytes_to_base64(argv[1]);

	printf("base64 encoded string:\n\t%s\n", base64);

	free(base64);

	exit(EXIT_SUCCESS);
}
