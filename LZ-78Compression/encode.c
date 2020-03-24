#include "code.h"
#include "endian.h"
#include "io.h"
#include "trie.h"
#include "word.h"
#include <ctype.h>
#include <fcntl.h>
#include <getopt.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#define BLOCK 4096
#define OPTIONS "i:o:v"

bool display_stat = false; // State variables to determine if compression
                           // statistics need to be printed.
int in = STDIN_FILENO;     // input file descriptor default to stdin.
int out = STDOUT_FILENO;   // output file descriptor default to stdout.

// Function to return bitlength of code passed in.
uint8_t blength(uint16_t next_code) {
  uint8_t bits = 0;
  if (next_code != 0) {
    bits = (log(next_code) / log(2)) + 1; // take log of number and add 1
  } else if (next_code == 0) {
    bits = 1; // if code is zero, number of bits is 0
  }
  return bits; // return number of bits.
}

int main(int argc, char **argv) {

  int choice = 0;

  while ((choice = getopt(argc, argv, OPTIONS)) != -1) {
    switch (choice) {
    case 'v': // flag for stats
      display_stat = true;
      break;
    case 'i':                      // flag for file to compress
      in = open(optarg, O_RDONLY); // open file as read-only with.
      if (in == -1) {
        printf("Failed to open file.\n");
        exit(-3);
      }
      break;
    case 'o':
      out = open(optarg, O_WRONLY | O_CREAT); // open or create as write-only
      break;
    default:
      printf("Invalid arguments\n"); // if invalid arguments are entered.
      exit(-3);
    }
  }

  struct stat outFileInfo;  // buffer for file data
  fstat(out, &outFileInfo); // pass to fstat to read in.
  struct stat inFileInfo;
  fstat(in, &inFileInfo);

  FileHeader *fh = (FileHeader *)calloc(
      1, sizeof(FileHeader)); // Allocate memory for FileHeader
  if (fh) {
    fh->magic = MAGIC;                   // set magic number
    fh->protection = inFileInfo.st_mode; // set protection bits
    write_header(out, fh);               // write header file.
  }
  TrieNode *root = trie_create();  // create trie with root node.
  TrieNode *curr_node = root;      // set current node to root node.
  TrieNode *prev_node = NULL;      // prev_node starts with NULL
  uint8_t curr_sym = 0;            // current symbol
  uint8_t prev_sym = 0;            // prev symbol.
  uint16_t next_code = START_CODE; // next code.

  // Loop over all symbols in file
  while (read_sym(in, &curr_sym) == true) {
    TrieNode *next_node = NULL; // Next_node
    if (curr_node) {
      next_node = trie_step(curr_node, curr_sym); // step through curr_node
    }
    if (next_node != NULL) { // if there are nodes to step through
      prev_node = curr_node; // set prev_node to curr_node
      curr_node = next_node; // set curr_node to next_node
    } else if (curr_node) {  // if next_node is NULL
      buffer_pair(out, curr_node->code, curr_sym,
                  blength(next_code)); // buffer the symbol with code and bit
                                       // length of next code.
      curr_node->children[curr_sym] =
          trie_node_create(next_code); // Add symbol to tree
      curr_node = root;                // set curr_node back to root node.
      next_code++;                     // increment next node.
    }
    if (next_code ==
        MAX_CODE) {           // If the max number of codes have been assigned.
      trie_reset(root);       // reset the trie
      curr_node = root;       // set curr_node back to root node.
      next_code = START_CODE; // set next_code back to START_CODE
    }
    prev_sym = curr_sym; // prev symbol becomes current symbol
  }
  if (curr_node != root) { // if current node isn't the root node.
    buffer_pair(out, prev_node->code, prev_sym,
                blength(next_code)); // buffer the symbol and code for the node.
    next_code = (next_code + 1) % MAX_CODE; // set next code.
  }
  buffer_pair(out, STOP_CODE, 0, blength(next_code)); // add stop code pair to
                                                      // file to indicate end of
                                                      // file encoding.
  flush_pairs(out); // flush remaining buffers to file.

  // printf("bit: %d\n",bwi);
  if (display_stat) {         // if -v flag is passed.
    fstat(out, &outFileInfo); // read information about compressed file made.
    fprintf(stderr, "Compressed file size: %ld bytes\n",
            outFileInfo.st_size); // print out compressed file size.
    fprintf(stderr, "Uncompressed file size: %ld bytes\n",
            inFileInfo.st_size); // print out decompressed file size.
    double comp_ratio =
        100 * (1 - (double)outFileInfo.st_size /
                       (double)inFileInfo.st_size); // compression ratio.
    fprintf(stderr, "Compression ratio: %.2f%%\n",
            comp_ratio); // print out compression ratio
  }

  close(out);        // close output file.
  close(in);         // close input file.
  trie_delete(root); // delete trie
  free(fh);          // free file header

  return 0;
}
