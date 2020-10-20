/*********************************************************************************
 * Christopher Medlin
 * Program 06
 *
 * Decodes a message using a simple steganography algorithm
 ********************************************************************************/

#include <stdio.h>

/*********************************************************************************
 * Reads a number of spaces from standard input, and based on the number of spaces
 * read, modifies the character pointed to by c. If 1 space is read, c is appended 
 * with a 0 bit on the right, and if 2 spaces are read, c is appended with a 1 bit.
 * 
 * Returns 1 if c is modified, 0 if it is not modified, and -1 if 3 or more spaces
 * are read.
 *********************************************************************************/
int decode_bit(char *c) {
	int spaces = 0;

	// count number of spaces after the period
	while (getchar() == ' ') {
		spaces++;
	}

	switch (spaces) {
		case 0:
			break;
		case 1:
			*c <<= 1;
			return 1;
		case 2:
			*c <<= 1;
			*c += 1;
			return 1;
		default:
			return -1;
	}
	return 0;
}

int main() {
	char message[500] = {};
	int messageIndex = 0;
	// current char is the character being decoded in the message
	char currentChar = 0, c;
	int bits = 0;
	// stores the return value of decode_bit
	int modified;
	
	while ((c = getchar()) != EOF) {
		if (c == '.') {
			modified = decode_bit(&currentChar);
			if (modified == 1) {
				bits++;
			} else if (modified == -1) {
				break;
			}

			// if 8 bits have been read, store the character and begin
			// decoding a new one
			if (bits == 8) {
				message[messageIndex] = currentChar;
				messageIndex++;
				currentChar = 0;
				bits = 0;
			}
		}
	}
	
	// if we have reached EOF, it means there was no message end signifier,
	// and the program should return 2.
	if (c == EOF) {
		return 2;
	}
	
	// if number of bits not divisible by 8.
	if (bits % 8) {
		return 1;
	}

	printf("%s\n", message);
	return 0;
}
