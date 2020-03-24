#include "stack.h"
#include <ctype.h>
#include <getopt.h>
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nAlphabets 26
#define OPTIONS "udmi:"

// Adjacency matrix to store all the existing paths.
int adj_matrix[nAlphabets][nAlphabets];
// Alphabet array to create an alphabet to value mapping of the characters.
const char alpha[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I',
                      'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                      'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

// Keeps track of the nodes visited during the seach by storing 1 for visited
// and 0 for unvisited for the index associated with the alphabetical junction.
int visited[100];
// Keeps track of the number of times path is found.
int path_count = 0;
// Based on the paths generated during the search, the length of the shortest
// path is stored here.
uint32_t last_length = nAlphabets;

// Following boolean variables store the instructions passed on by command line
// flags and arguments for use later in the program to produce desired output.
bool is_undirected =
    false;                // Set by -u flag to determine if graph is undirected.
bool is_directed = false; // Set by -d flag to determine if graph is
                          // directed.
bool both_entered = false; // Condition to check if both directed and undirected
                           // flags are entered.
bool z_exists = false; // Checks if the paths inputted by the file or user input
                       // stream contains a Z to see if a path exists.
bool a_exists = false; // Checks if the paths inputted by the file or user input
                       // stream contains a A to see if a path exists
bool valid_characters =
    true; // Checks if all characters inputted are valid alphabets.
bool print_mat =
    false; // Set by -m flag to determine if matrix should be printed.
bool path_inputted = false; // Determines whether path is inputted by text file
                            // or console input stream.
// Prints the path from the stack based on the output format specified
void path_print(Stack *s) {
  printf("Found path: ");
  // for loop iterates over stack and prints characters associated with values
  // on the stack.
  for (uint32_t k = 0; k < s->top; k++) {
    if (alpha[s->items[k]] != 'Z') {
      printf("%c -> ", alpha[s->items[k]]);
    } else {
      printf("Z");
    }
  }
  return;
}
// Helper function to return value associated with character.
int getAlphaIndex(char letter) {
  int index = 0;
  for (int x = 0; x < nAlphabets; x++) {
    if (alpha[x] == letter) {
      index = x;
    }
  }
  return index; // Return index which is the value associated with the element.
}

// Prints adjacency matrix in the specified format.
void printAdj() {
  if (valid_characters) {
    printf("  ");
    for (int a = 0; a < nAlphabets; a++) {
      printf("%c ", alpha[a]);
    }
    printf("\n");
    for (int k = 0; k < nAlphabets; k++) {
      printf("%c ", alpha[k]);
      for (int l = 0; l < nAlphabets; l++) {
        printf("%d ", adj_matrix[k][l]);
      }
      printf("\n");
    }
  }
}

// Function for taking input from a text file to create the adjancency matrix.
int TakeFileInput(FILE *path) {
  int success = 0; // determines if opening file was done successfully or not.
  // Temp variables to store pair of characters read on each line
  char vert1 = 'a';
  char vert2 = 'B';
  if (path) {
    while (fscanf(path, "%c%c\n", &vert1, &vert2) !=
           EOF) { // Read from file in format of char1char2
      if (isalpha(vert1) && isalpha(vert2)) {
        // For each of these statements, a 1 is stored to indicate an existing
        // path between characters. It's stored in the row and column index of
        // the values associated with the respective pair of characters. Default
        // matrix values are 0.
        if (is_undirected == true) {
          adj_matrix[getAlphaIndex(toupper(vert1))]
                    [getAlphaIndex(toupper(vert2))] = 1;
          adj_matrix[getAlphaIndex(toupper(vert2))]
                    [getAlphaIndex(toupper(vert1))] = 1;
        } else {
          adj_matrix[getAlphaIndex(toupper(vert1))]
                    [getAlphaIndex(toupper(vert2))] = 1;
        }
      } else {
        valid_characters = false;
        break;
      }
    }

    fclose(path); // Close file reading.
  } else {
    puts("Error: valid input file required"); // Error if file isn't found.
    success = -1;
  }
  // For loop iterating over matrix to see if there are any paths to Z.
  for (int q = 0; q < nAlphabets; q++) {
    if (adj_matrix[q][getAlphaIndex('Z')] == 1 ||
        adj_matrix[getAlphaIndex('Z')][q] == 1) {
      z_exists = true;
    }
  }
  // For loop iterating over matrix to see if the path search can start with A
  for (int q = 0; q < nAlphabets; q++) {
    if (adj_matrix[getAlphaIndex('A')][q] == 1 ||
        adj_matrix[q][getAlphaIndex('A')] == 1) {
      a_exists = true;
    }
  }

  return success; // Return value determined by if file was opened successfully.
}

// Function for creating adjacency matrix for user command line input stream.
void TakeConsoleInput() {
  char vert1 = 'a';
  char vert2 = 'B';
  while (fscanf(stdin, "%c%c\n", &vert1, &vert2) != EOF) {
    if (isalpha(vert1) && isalpha(vert2)) {
      if (is_undirected == true) {
        // For each of these statements, a 1 is stored to indicate an existing
        // path between characters. It's stored in the row and column index of
        // the values associated with the respective pair of characters. Default
        // matrix values are 0.
        adj_matrix[getAlphaIndex(toupper(vert1))]
                  [getAlphaIndex(toupper(vert2))] = 1;
        adj_matrix[getAlphaIndex(toupper(vert2))]
                  [getAlphaIndex(toupper(vert1))] = 1;
      } else {
        adj_matrix[getAlphaIndex(toupper(vert1))]
                  [getAlphaIndex(toupper(vert2))] = 1;
      }
    } else {
      valid_characters = false;
      break;
    }
  }
  // For loop iterating over matrix to see if there are any paths to Z.
  for (int q = 0; q < nAlphabets; q++) {
    if (adj_matrix[q][getAlphaIndex('Z')] == 1 ||
        adj_matrix[getAlphaIndex('Z')][q] == 1) {
      z_exists = true;
    }
  }

  // For loop iterating over matrix to see if there are paths starting with A.
  for (int q = 0; q < nAlphabets; q++) {
    if (adj_matrix[getAlphaIndex('A')][q] == 1 ||
        adj_matrix[q][getAlphaIndex('A')] == 1) {
      a_exists = true;
    }
  }
}

// Depth first search algorithim based on psedocode provided by Darrell Long in
// assigmnent pdf.
void dfs(uint32_t current, Stack *stack_path) {
  uint32_t *poper = 0;             // Pointer to store popped element.
  stack_push(stack_path, current); // Push current uint32_t element to stack.
  visited[current] = 1; // Set character associated with element to visited.
  // If the current value is the values associated with Z, then the length of
  // path is recorded, path is printed and number of paths generated is
  // incremented by 1.
  if (alpha[current] == 'Z') {
    if (stack_size(stack_path) <= last_length) {
      last_length = stack_size(stack_path);
    }
    path_print(stack_path);
    path_count++;
    printf("\n");
  } else {
    for (uint32_t k = 0; k < nAlphabets; k++) {
      if (adj_matrix[current][k] == 1 && visited[k] == 0 &&
          current != k) { // Iterates over all the values associated characters
                          // except the current character value.

        dfs(k, stack_path); // Recursion with the next value that has path from
                            // the current value.
      }
    }
  }
  stack_pop(stack_path, poper); // If no more paths can be visited at junction.
                                // Pop back to last junction with undiscovered
                                // edges.
  visited[current] = 0; // Make sure that algorithim can still reach that same
                        // junction mentioned above setting it to unvisited.
  return;
}

int main(int argc, char **argv) {
  FILE *path =
      stdin; // Initialize default file stream input to user input stream.
  Stack *node_path = stack_create();     // Create stack for junctions.
  for (int i = 0; i < nAlphabets; i++) { // Initialize adjacency matrix to 0
    for (int j = 0; j < nAlphabets; j++) {
      adj_matrix[i][j] = 0;
    }
  }
  // Initialize visited junction matrix to 0(unvisited)
  for (int m = 0; m < 100; m++) {
    visited[m] = 0;
  }
  // Enum value for directionality of graph as a mutually exclusive state.
  int choice = 0;

  // While loop to read and parse file argument and flags passed through command
  // line during execution.
  while ((choice = getopt(argc, argv, OPTIONS)) !=
         -1) { // switch case between types of flags
    switch (choice) {
    case 'u':
      is_undirected = true;
      break;
    case 'd':
      is_directed = true;
      break;
    case 'm':
      print_mat = true; // Set bool variable if -m flag was passed.
      break;
    case 'i': // cite darrel long
      path_inputted = true;
      path = fopen(optarg, "r"); // name of file set to the only non-option
                                 // argument passed in by the command line.
                                 // Based on Darrell Long's Code on Piazza. Open
                                 // as read-only.
      if (path == NULL) {
        perror(optarg); // error if file can't be opened.
        exit(1);
      }
      break;
    default:
      printf("Invalid arguments\n"); // if invalid arguments are entered.

      break;
    }
  }

  // Throw error if both -u and -d flags are entered.
  if (is_directed && is_undirected) {
    printf("Error: Both -u and -d flags not accepted\n");
    exit(-1);
  } else if (!is_undirected && !is_directed) {
    is_undirected = true;
  }
  // If the condition of the if statement is true then adjacency matrix is
  // created from file input. Otherwise, determined by user-input.
  if (path_inputted) {
    TakeFileInput(path);
  } else {
    TakeConsoleInput();
  }

  // If print_mat variable is true based on if the -m flag was passed, then
  // print the matrix.
  if (print_mat) {
    printAdj();
  }
  // If valid characters were passed and a path was found. Then run the dfs
  // function to find all paths
  if (valid_characters == true) {
    if (z_exists == true && a_exists == true) {
      dfs(0, node_path);
      printf("Number of paths found: %d\n", path_count);
      printf("Length of shortest path found: %d", last_length);
      printf("\n");
    } else {
      printf("No paths found!\n");
    }
  } else {
    printf("Nodes must be between the range of A-Z!\n");
  }
  // Delete stack object after use.
  stack_delete(node_path);
  return 0;
}
