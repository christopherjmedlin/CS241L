#include <stdio.h>

/*
 * Name: Christopher MEdlin
 * Date: 25 Sep 2020
 *
 * Outputs percentage of DNA bases in a sequence.
 */

double percentage(int base, int total) {
	return ((double) base / (double) total) * 100;
}

int main() {
	int bases = 0, a = 0, c = 0, g = 0, t = 0;
	char nextChar;

	while (nextChar = getchar(), nextChar != EOF) {
		switch (nextChar) {
			case 'A':
			case 'a': 
				a++; 
				break;
			case 'C':
			case 'c': 
				c++; 
				break;
			case 'G':
			case 'g': 
				g++; 
				break;
			case 'T':
			case 't': 
				t++; 
				break;
			case ' ':
			case '\n':
				// ignore whitespace and newlines
				continue;
			default:
				printf("Invalid character: %c\n", nextChar);
				return 1;		
		}
		bases++;
	}

	printf("The DNA sequence has %d bases\n", bases);
	printf("%6.2f%% of the bases are A\n", percentage(a, bases));
	printf("%6.2f%% of the bases are C\n", percentage(c, bases));
	printf("%6.2f%% of the bases are G\n", percentage(g, bases));
	printf("%6.2f%% of the bases are T\n", percentage(t, bases));
	
	return 0;
}
