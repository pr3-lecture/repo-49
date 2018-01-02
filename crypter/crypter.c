include "crypto.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc (warning)

/**
* increase output to a new size.
* @param input, delivers the values.
* @param output, gets the new size.
* @param newsize, the size to increase.
*/
void increase(const char* input, char* output, int newsize) {
  int i, j;
  for(i = 0, j = 0; i < newsize; i++, j++) {
    if (j == strlen(input)) {
      j = 0;
    }
    output[i] = input[j];
  }
}

/**
* uses the xor function
* @param key, key to encrypt and decrypt
* @param input,
* @param output,
*/
void xor(KEY key, const char* input, char* output) {
  char* longkey = (char*) malloc(sizeof(char) * (strlen(input) + 1));
  increase(key.chars, longkey, strlen(input));

  int i;
  for (i = 0; i < strlen(input); i++) {
    output[i]  = input[i]   - 'A' + 1; //
    longkey[i] = longkey[i] - 'A' + 1; // map to num for xor

    output[i] = output[i] ^ longkey[i];
    output[i] = output[i] + 'A' - 1;
  }
  output[i] = '\0'; // end for "new" string
  free(longkey);
}

/**
* Checks input for permitted characters
* @param permitted, allowed characters for input.
* @param input, input which need a check.
* @return true or false, if input has a illegal character.
*/
int illegalChars(const char* input, const char* permitted) {
  int i;
  for (i = 0; i < strlen(input); i++) {
    int searched = 0;
    int j;
    for (j = 0; j < strlen(permitted); j++) {
      if (input[i] == permitted[j]) {
        searched = 1;
        break;
      }
    }
    if (searched == 0)
      return 1;
  }
  return 0;
}

int encrypt(KEY key, const char* input, char* output) {
  if (strlen(key.chars) == 0)
    return E_KEY_TOO_SHORT;

  if (illegalChars(key.chars, KEY_CHARACTERS))
    return E_KEY_ILLEGAL_CHAR;

  if (illegalChars(input, MESSAGE_CHARACTERS))
    return E_MESSAGE_ILLEGAL_CHAR;


  xor(key, input, output);
  return 0;
}

int decrypt(KEY key, const char* cypherText, char* output) {
  if (strlen(key.chars) == 0)
    return E_KEY_TOO_SHORT;

  if (illegalChars(key.chars, KEY_CHARACTERS))
    return E_KEY_ILLEGAL_CHAR;

  if (illegalChars(cypherText, CYPHER_CHARACTERS))
    return E_CYPHER_ILLEGAL_CHAR;


  xor(key, cypherText, output);
  return 0;
}
