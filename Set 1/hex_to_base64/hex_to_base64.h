#ifndef	_HEX_TO_BASE64_H_
#define _HEX_TO_BASE64_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint8_t
*hex_to_bytes(char *hex_str);

uint8_t
*bytes_to_base64(char *byte_str);

#endif /* _HEX_TO_BASE64_H_ */
