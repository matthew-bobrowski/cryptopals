/**
 * This source code file contains functions that are responsible for encoding a
 * hexadecimal string into an RFC 4648 <https://tools.ietf.org/html/rfc4648>
 * US-ASCII Base 64 encoded string. This challenge was sourced from the Matasano
 * Cryptopals challenge sets <http://cryptopals.com/sets/1/challenges/1>.
 *
 * Author: Matthew Bobrowski <mbobrowski@mbobrowski.org, mbobrowski@au1.ibm.com>
 */

#include "hex_to_base64.h"

static const uint8_t pad = '=';
static const uint8_t base64_alphabet[] = 
				{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
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
 * parameter.
 */
static uint32_t
get_encoded_length(size_t length)
{
	uint8_t padding = (length % 3 ? 3 - (length % 3) : 0);
	return (uint32_t) 4 * ((float) (length + padding) / 3);
}

/**
 * Utility function that converts a hexadecimal character representation into
 * their nibble equivalent.
 */
static uint8_t 
char_to_nibble(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 255;
}

/**
 * Function that converts a hexadecimal string into raw bytes.
 */
uint8_t
*hex_to_bytes(char *hex)
{
	int i;
	uint8_t *p, *bytes;
	size_t length = strlen(hex) / 2;
	
	bytes = malloc(length + 1);

	for (i = 0, p = (uint8_t *) hex; i < length; i++) {
		bytes[i] = (char_to_nibble(*p) << 4) | char_to_nibble(*(p + 1));
		p += 2;
	}

	bytes[length] = 0;

	return bytes;
}

/**
 * Function that converts a raw encoded byte string into a US-ASCII Base 64
 * encoded string that conforms to the RFC4648 Base 64 encoding specification.
 */
uint8_t
*bytes_to_base64(char *bytes)
{
    	uint32_t group = 0; 
    	size_t decoded_length = strlen(bytes);
    	size_t encoded_length = get_encoded_length(decoded_length);
	uint8_t *base64 = malloc(encoded_length + 1);
    
	size_t index = 0;
        for (size_t i = 0; i < decoded_length; i += 3) {
            	
		// build 24-bit group	
            	group = (uint32_t) bytes[i] << 16;
		
		if (i + 1 < decoded_length)
                	group |= (uint32_t) bytes[i + 1] << 8;
            
            	if (i + 2 < decoded_length)
                	group |= (uint32_t) bytes[i + 2];
            
            	// separate into 6 bit numbers using 111111 mask
            	base64[index++] = base64_alphabet[(uint8_t) (group >> 18) & 63];
         	base64[index++] = base64_alphabet[(uint8_t) (group >> 12) & 63];
            	base64[index++] = base64_alphabet[(uint8_t) (group >> 6) & 63];
            	base64[index++] = base64_alphabet[(uint8_t) (group >> 0) & 63];
        }

	// calculate number of pad characters and append to base64 string	
        uint8_t padding = (decoded_length % 3 ? 3 - (decoded_length % 3) : 0);
        while (padding > 0) {
            base64[encoded_length - padding] = pad;
            padding--;
        }

	base64[encoded_length] = 0;

        return base64;
}
