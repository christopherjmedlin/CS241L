#include <stdio.h>
#include <string.h>

/*
 * Name: Christopher Medlin
 * Date: 11 Sep 2020
 *
 * Creates a hash out of a string.
 */

int main( int argc, char *argv[] ) {

  if ( argc != 2 ) {
    printf ( "You must enter a single word on the command line\n" );
    return 1;  // Error code for operating system
  }

  char *theData = argv[1];
  unsigned int hashCode = 0;

  // this variable is used to capture the leftmost 4 bits of the hashCode
  unsigned int leftMostFourBits = 0;
 
  /* PUT YOUR CODE BETWEEN THIS COMMENT AND THE CLOSING COMMENT BELOW  */

  // loop over each char in the given input string and
  // update the value of the hash code based on this char
  int i;
  for ( i = 0; i < strlen(theData); i++ ) {

    char nextChar = theData[i];
    
    // add ASCII value of character to the hash code.
    hashCode += nextChar;
    // shift to the rigt 10 bits to put the last 4 bits in positions 18-21
    leftMostFourBits = hashCode >> 10;
    // make all bits except 18-21 0.
    // 2^18 + 2^19 + 2^20 + 2^21 = 3932160
    leftMostFourBits &= 3932160; 
    
    if (i != strlen(theData) - 1) {
        hashCode <<= 4;
	hashCode ^= leftMostFourBits;
    } 
  }

  /* CLOSING COMMENT   */

  printf ( "The hash of %s = %u\n", argv[1], hashCode );

  return 0;   // success code returned to Operating System
}
