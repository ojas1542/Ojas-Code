#include "bv.h"
#include "sieve.h"
#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ByteSize 8
#define MaxSize 64
#define numAsciiBase 48
#define alpAsciiBase 87
#define OPTIONS "spn:"

bool isMersennePrime(BitVector *v,
                     uint32_t i);  // Check if number is a Mersenne prime
int fibonacci();                   // Return next fibonacci number
int lucas();                       // Return next lucas number
bool isPalindromePrime(char *num); // Check if string is a palindrome.
void base_change(
    uint32_t i, uint32_t base,
    char *base_changed); // Change to desired base and output as a string.
void printPrime(
    BitVector *v); // Print all prime numbers given the size of the bitvector.
void palindrome_print(BitVector *v, char *rep,
                      int base); // Print all palindromes in a given base.

int main(int argc, char **argv) {
  int choice = 0;
  uint32_t number_terms = 1000; // Default number of terms
  bool run_prime = false; // Bool variable to store true if -s flag is passed.
  bool run_palindrome =
      false; // Bool variable to store true if -p flag is passed.
  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 'n':
      // Checks for valid input. Otherwise program will not be run.
      if ((int)atoi(optarg) < 1) {
        printf("Please enter a number greater than 1\n");
        exit(-3);
      } else {
        number_terms = (uint32_t)atoi(optarg);
      }
      break;
    case 's':
      run_prime = true;
      break;
    case 'p':
      run_palindrome = true;
      break;
    default:
      break;
    }
  }
  BitVector *prime_list = bv_create(number_terms);
  if (prime_list != NULL) { // Check if pointer still exists.
    sieve(prime_list);
  }

  // Print prime numbers first then palindromes is both flags are entered(i.e
  // both bool vars a true)
  if (run_prime && run_palindrome) {
    printPrime(prime_list);
    printf("\n");
    char num[MaxSize]; // Declare string to be passed in.
    palindrome_print(prime_list, num, 2);
    printf("\n");

    palindrome_print(prime_list, num, 10);
    printf("\n");

    palindrome_print(prime_list, num, 14);
    printf("\n");

    palindrome_print(
        prime_list, num,
        31); // First letter of last name is U(21st letter). So 21+10 = 31
  } else if (run_prime) { // If only the -s flag is passed, print primes only.
    printPrime(prime_list);
  } else if (run_palindrome) { // If only the -p flag is passed, print
                               // palindromes only
    char num[MaxSize];         // Declare string to be passed in.
    palindrome_print(prime_list, num, 2);
    printf("\n");

    palindrome_print(prime_list, num, 10);
    printf("\n");

    palindrome_print(prime_list, num, 14);
    printf("\n");

    palindrome_print(prime_list, num, 31);
  }
  if (prime_list != NULL) { // Check if the pointer exists before deleting it.
    bv_delete(prime_list);
  }

  return 0;
}

bool isMersennePrime(BitVector *v, uint32_t i) {
  bool mersenne = false;
  double log_n1 = 0;
  double prime = (double)i + 1; // creaing the i+1 term
  if (bv_get_bit(v, i) == 1) {  // Check if number is prime.
    log_n1 = log(prime) /
             log(2); // taking log base 2 of i+1 using of change of bases rule.
    if (log_n1 == floor(log_n1)) { // Checking if result is a whole number in
                                   // which case it's a mersenne prime.
      mersenne = true;
    }
  }
  return mersenne; // return whether number inputted is a mersenne number.
}

int fibonacci() {
  // Static variables to hold the previous two fibonacci numbers through
  // multiple function calls
  static uint32_t n0 = 0;
  static uint32_t n1 = 1;
  // Compute the sum of the two previous numbers.
  uint32_t n = n0 + n1;
  // Set the new terms for the next call to function.
  n0 = n1;
  n1 = n;

  return n; // Return next fibonacci term
}

int lucas() {
  static uint32_t case2 = 2; // Special variable to ensure that 2 is returned
                             // when the function is first run.
  // Static variables to hold the previous lucas numbers through multiple
  // function calls.
  static uint32_t n0 = 2;
  static uint32_t n1 = 1;
  // If statement runs when function is called for the first time only to
  // return 2.
  if (case2 == 2) {
    case2 =
        0; // variable is modified so the if statement is never triggered again.
    return 2;
  }
  // compute the next lucas number.
  uint32_t n = n0 + n1;
  // Set the new terms for the next call to function
  n0 = n1;
  n1 = n;

  return n; // Return next lucas term
}

bool isPalindromePrime(char *num) {
  // If string is empty, return false.
  if (num == NULL) {
    return false;
  }
  int left = 0; // Variable to keep track of array index moving left to right
  int right =
      strlen(num) -
      1; // Variable to keep of track of array index moving right to left.
  while (left < right) { // While loop runs till the left and right variables
                         // move to the center of string.
    if (toupper(num[right]) !=
        toupper(num[left])) { // If characters on each side(when moving inward)
                              // aren't same then string can't be palindrome.
      return false;
    }
    left += 1;  // increment right moving index.
    right -= 1; // decrement left moving index.
  }
  return true; // return true if characters are the same for each iteration of
               // the comparision of left and right.
}

void base_change(uint32_t i, uint32_t base, char *base_changed) {
  // Store index in quotient
  uint32_t quotient = i;
  uint32_t remainder = 0;
  // iterator variable for storing each character in an array..
  uint32_t iterator = 0;
  while (quotient != 0) {
    remainder = quotient % base;
    quotient /= base;
    if (remainder >= 10) { // check if remained is greater than or equal to 10
      base_changed[iterator] =
          remainder + alpAsciiBase; // if condition is true than store the
                                    // remainder as corresponding alphabet(i.e:
                                    // a: 10 b: 11..) using ascii conversion.
    } else {
      base_changed[iterator] =
          remainder + numAsciiBase; // Otherwise store the remainder as a
                                    // character using ascii conversion.
    }
    iterator++; // Increment counter to move the next array index.
  }
  base_changed[iterator] = '\0'; // After the base representation is stored,
                                 // append a null character so the string is
                                 // terminated.
  // String is never reversed since that wouldn't matter for checking if it's a
  // palindrome.

  return;
}

void printPrime(BitVector *v) {
  uint32_t num_true_f =
      0; // Used to store the lucas number at each while loop iteration.
  uint32_t num_true_l =
      0; // Used to store the fibonacci number at each while loop iteration.
  for (uint32_t i = 2; i < bv_get_len(v);
       i++) {                    // For loop iteration over bitvector elements/
    if (bv_get_bit(v, i) == 1) { // Check if number is prime.
      printf("%u: prime", i);    // Print prime
      // If number is mersenne then print mersenne.
      if (isMersennePrime(v, i) == true) {
        printf(", ");
        printf("mersenne");
      }

      if (num_true_l == i) { // if number at last lucas function call is equal
                             // to i then print lucas.
        printf(", ");
        printf("lucas");
      } else {
        while (num_true_l < i) { // While loop iterating till value of for-loop
                                 // iterator variable.
          num_true_l =
              lucas(); // Function call return value stored for checking.
          if (num_true_l == i) { // If return value is the value of the iterator
                                 // variable, then the prime number is a lucas
                                 // number too
            printf(", ");
            printf("lucas");
          }
        }
      }

      if (num_true_f == i) { // if number at last fibonacci function call is
                             // equal to i then print fibonacci
        printf(", ");
        printf("fibonacci");
      } else {
        while (num_true_f < i) { // While loop iterating till value of for-loop
                                 // iterator variable.
          num_true_f =
              fibonacci(); // Function call return value stored for checking.
          if (num_true_f == i) { // If return value is the value of the iterator
                                 // varibale, then the prime number is a
                                 // fibonacci number too
            printf(", ");
            printf("fibonacci");
          }
        }
      }

      printf("\n"); // New line to move to next prime
    }
  }
  return;
}

void palindrome_print(BitVector *v, char *rep, int base) {
  printf("Base %d\n", base);
  printf("---- -\n");
  for (uint32_t i = 0; i < bv_get_len(v);
       i++) { // For-loop iterating over all bitvector values.
    if (bv_get_bit(v, i) == 1) { // Check if number is prime.
      base_change(i, base, rep); // Run base change for given input base, value,
                                 // and string passed in for modification.
      if (isPalindromePrime(rep) ==
          true) { // If string is a palidrome then print base 10 representation
                  // and base representation which number is a palindrome.
        printf("%u = %s\n", i, rep);
      }
    }
  }
  return;
}
