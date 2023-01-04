#include <stdlib.h>
#include <limits.h>
#include <string.h>

// Buffer sized for a decimal string of a `signed int`, 28/93 > log10(2)
#define SIGNED_PRINT_SIZE(object)  ((sizeof(object) * CHAR_BIT - 1)* 28 / 93 + 3)

char *itoa(int number, char *dest, size_t dest_size) {
	if (dest == NULL) {
		return NULL;
	}

	char buf[SIGNED_PRINT_SIZE(number)];
	char *p = &buf[sizeof buf - 1];

	// Work with negative absolute value
	int neg_num = number < 0 ? number : -number;

	// Form string
	*p = '\0';
	do {
		*--p = (char) ('0' - neg_num % 10);
		neg_num /= 10;
	} while (neg_num);
	if (number < 0) {
		*--p = '-';
	}

	// Copy string
	size_t src_size = (size_t) (&buf[sizeof buf] - p);
	if (src_size > dest_size) {
		// Not enough room
		return NULL;
	}
	return memcpy(dest, p, src_size);
}
