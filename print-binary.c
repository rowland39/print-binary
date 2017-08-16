#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <arpa/inet.h>

#define MAX_LINE 80
#define PROMPT "input> "

/*
 * See print-bits/print-bits.c in this directory  for an alternative method
 * that is also very interesting!
 */
const char *
byte_to_binary32(uint32_t x)
{
    static char b[36];
    b[0] = '\0';
    uint32_t z;
    int count = 1;

    for (z = 1 << 31; z > 0; z >>= 1) {
        strcat(b, ((x & z) == z) ? "1" : "0");

        if (count % 8 == 0 && count != 32)
            strcat(b, " ");

        count++;
    }

    return b;
}

int
main(void)
{
    char input[MAX_LINE];
    uint32_t number, old_number;
	int x, n;

    printf(PROMPT);

    while (fgets(input, MAX_LINE, stdin) != NULL) {
        /*
         * You can "number = (uint32_t)atol(input);" here instead, but using
         * strtol() will allow you to specify a base of 8, 10, or 16 as called
         * below depending on if you use a leading 0 or 0x. That's much better.
         */
        number = (uint32_t)strtol(input, NULL, 0);
        old_number = number;
        printf("\nHost Order:\t\t\t%#010x\n", number);

        // This is meant to show each byte as hexidecimal in the order the
		// bytes are stored in RAM. This is mostly interesting on a little
		// endian system.
    	printf("RAM Bytes in Order:\t\t");

    	for (n = 0; n < 4; n++) {
        	x = (number >> (8 * n)) & 0xff;
        	printf("%#04x ", x);
    	}

        printf("\n\n");
        number = old_number;

        printf("Unsigned\tSigned\t\t32-bit Binary\n");
        printf("--------\t------\t\t-------------\n");
        printf("%-8u\t%-8d\t%s\n\n", number, number, byte_to_binary32(number));
        number = htonl(number);
        printf("\nNetwork Order (on this host):\t%#010x\n\n", number);
        printf("Unsigned\tSigned\t\t32-bit Binary\n");
        printf("--------\t------\t\t-------------\n");
        printf("%-8u\t%-8d\t%s\n\n", number, number, byte_to_binary32(number));
        printf(PROMPT);
    }

    printf("\n");
    exit(EXIT_SUCCESS);
}
