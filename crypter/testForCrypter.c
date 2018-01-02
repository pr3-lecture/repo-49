#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc (warning)
#include "crypto.h"

int tests_run = 0;

#define mu_assert(message, test) do { if (!(test)) return message; } while (0)
#define mu_run_test(test) do { char *message = test(); tests_run++; \
                                if (message) return message; } while (0)

static char* encryptTest(keyName, testName, inputTest, outputTest) {
  KEY key = {1, keyName};
  const char* input = inputTest;
  char* output = (char*) malloc(sizeof(char) * (strlen(input)+1));
  encrypt(key, input, output);
  mu_assert(testName, strcmp(output, outputTest) == 0);
  free(output);
  return 0;
}

static char* decryptTest (keyName, testName, inputTest, outputTest){
  KEY key = {1, keyName};
  const char* input = inputTest;
  char* output1 = (char*) malloc(sizeof(char) * (strlen(input) + 1));
  char* output2 = (char*) malloc(sizeof(char) * (strlen(input) + 1));
  encrypt(key,input,output1);
  decrypt(key,output1,output2);
  mu_assert(testName, strcmp(output2, outputTest) == 0);
  free(output1);
  free(output2);
  return 0;
}

//Tests for crypt
static char* testNumberOne() {
  encryptTest("TPERULESTPERULESTPERULESTP", "First test","ABCDEFGHIJKLMNOPQRSTUVWXYZ","URFVPJB[]ZN^XBJCEBVF@ZRKMJ");
}

static char* testNumberTwo() {
  encryptTest("TPERULES", "Second test","ABC","URF");
}

static char* testNumberThree() {
  encryptTest("TPERULES", "Third test","ABCDEFGHIJKLMNOPQRSTUVWXYZ","URFVPJB[]ZN^XBJCEBVF@ZRKMJ");
}

//Tests for decrypt
static char* testNumberFour() {
  decryptTest("TPERULES", "Fourth test", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

static char* testNumberFive() {
  decryptTest("TPERULESTPERULESTPERULESTP", "Fifth test", "ABCDEFGHIJKLMNOPQRSTUVWXYZ", "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

static char* testNumberSix() {
  decryptTest("TPERULES", "Sixth test", "ABC", "ABC");
}

static char* allTests() {
  mu_run_test(testNumberOne);
  mu_run_test(testNumberTwo);
  mu_run_test(testNumberThree);
  mu_run_test(testNumberFour);
  mu_run_test(testNumberFive);
  mu_run_test(testNumberSix);
  return 0;
}

int main() {
  char *result = allTests();

  if (result != 0) printf("%s\n", result);
  else             printf("ALL TESTS PASSED\n");

  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
