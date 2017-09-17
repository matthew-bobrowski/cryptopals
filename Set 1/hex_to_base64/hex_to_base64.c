/**
 * This source file contains the functions that are responsible for translating
 * a hexadecimal encoded string into a RFC 4648 base64 compliant encoded string.
 *
 * Author: Matthew Bobrowski <mbobrowki@mbobrowski.org, mbobrowski@au1.ibm.com>
 */

#include "hex_to_base64.h"

static const uint8_t pad = '=';
static const uint8_t base64_alphabet[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/'};

static uint32_t
get_encoded_length(size_t byte_str_len)
{
	return (uint32_t) (4 * (byte_str_len/3));
}

static uint8_t 
char_to_nibble(char c)
{
	if (c >= '0' && c <= '9') return c - '0';
	if (c >= 'a' && c <= 'f') return c - 'a' + 10;
	if (c >= 'A' && c <= 'F') return c - 'A' + 10;
	return 255;
}

static uint8_t
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

uint8_t
*bytes_to_base64(char *byte_str)
{
	int i;
	uint8_t *base64;
	size_t encoded_len, decoded_len;

	decoded_len = strlen(byte_str);
	encoded_len = get_encoded_length(decoded_len);
	base64 = malloc(encoded_len + 1);

	for (i = 0; i < decoded_len; i += 3) {
		
	}

	return base64;
}
