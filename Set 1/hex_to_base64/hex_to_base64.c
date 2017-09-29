/**
 * This source file contains the functions that are responsible for translating
 * a hexadecimal encoded string into an RFC 4648 base64 compliant encoded
 * string.
 *
 * Author: Matthew Bobrowski <mbobrowski@au1.ibm.com, mbobrowski@mbobrowski.org>
 */

#include "hex_to_base64.h"

static const uint8_t pad = '=';
const char base64_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};

/*
 * Utility function that calculates the length of a base64 encoded string based
 * on the length of the UTF-8 encoded string that is passed to the function as a
 * parameter
 */
static uint32_t
get_encoded_length(size_t byte_str_len)
{
	uint8_t padding = (byte_str_len % 3 ? 3 - (byte_str_len % 3) : 0);
	uint32_t encoded_length = 4 * ((float) (byte_str_len + padding) / 3);
	return encoded_length;
}

static uint8_t 
char_to_nibble(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 255;
}

uint8_t
*hex_to_bytes(char *hex_str)
{
	int i;
	uint8_t *p, *bytes;
	size_t length = strlen(hex_str) / 2;
	
	bytes = malloc(length + 1);

	for (i = 0, p = (uint8_t *) hex_str; i < length; i++) {
		bytes[i] = (char_to_nibble(*p) << 4) | char_to_nibble(*(p+1));
		p += 2;
	}

	bytes[length] = 0;

	return bytes;
}

char 
*bytes_to_base64(char *bytes)
{
    	uint32_t group = 0; 
    	size_t decoded_length = strlen(bytes);
    	size_t encoded_length = get_encoded_length(decoded_length);

    	char *base64 = malloc(encoded_length + 1);
    
	size_t index = 0;
        for (size_t i = 0; i < decoded_length; i += 3) {
           	
            	group = (uint32_t)bytes[i] << 16;
		
		if (i + 1 < decoded_length)
                	group |= (uint32_t)bytes[i+1] << 8;
            
            	if (i + 2 < decoded_length)
                	group |= (uint32_t)bytes[i+2];
            
            	// separate into 6 bit numbers using 111111 mask
            	base64[index++] = base64_alphabet[(uint8_t)(group >> 18) & 63];
         	base64[index++] = base64_alphabet[(uint8_t)(group >> 12) & 63];
            	base64[index++] = base64_alphabet[(uint8_t)(group >> 6) & 63];
            	base64[index++] = base64_alphabet[(uint8_t)(group >> 0) & 63];
        }
	
        uint8_t padding = (decoded_length % 3 ? 3 - (decoded_length % 3) : 0);
        while (padding > 0) {
            base64[encoded_length - padding] = pad;
            padding--;
        }

	base64[encoded_length] = 0;

        return base64;
}
