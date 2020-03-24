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

  FileHeader *fh = (FileHeader *)malloc(
      sizeof(FileHeader)); // Allocate memory for FileHeader
  if (fh) {
    read_header(in, fh); // read bytes into FileHeader
  }
  // If magic number is found in header. Start decompressing.
  if (fh->magic == MAGIC) {
    WordTable *wt = wt_create();     // create word table.
    uint8_t curr_sym = 0;            // current symbol
    uint16_t curr_code = 0;          // current code
    uint16_t next_code = START_CODE; // next code.

    struct stat outFileInfo;  // buffer for file data
    fstat(out, &outFileInfo); // pass to fstat to read in
    struct stat inFileInfo;
    fstat(in, &inFileInfo);

    while (read_pair(in, &curr_code, &curr_sym, blength(next_code)) ==
           true) { // While encoding pairs can still be read
      wt[next_code] = word_append_sym(
          wt[curr_code], curr_sym);    // append symbol to word in wordtable
      buffer_word(out, wt[next_code]); // write out word in wordtable to
                                       // decompressed file output.
      next_code++;                     // increment wordtable counter.
      if (next_code == MAX_CODE) {     // if max number of codes have been
                                       // assigned in wordtable.
        wt_reset(wt);                  // reset wordtable
        next_code = START_CODE;        // next_code set back to START_CODE
      }
    }
    flush_words(
        out); // Flush out remaining words in decompressed output buffer.
    if (display_stat) {         // if -v flag in passed in.
      fstat(out, &outFileInfo); // fill in stat buffer with information about
                                // decompressed file created.,
      fprintf(stderr, "Compressed file size: %ld bytes\n",
              inFileInfo.st_size); // print compressed file size.
      fprintf(stderr, "Uncompressed file size: %ld bytes\n",
              outFileInfo.st_size); // print decompressed file size/
      double comp_ratio =
          100 * (1 - (double)inFileInfo.st_size /
                         (double)outFileInfo.st_size); // compression ratio
      fprintf(stderr, "Compression ratio: %.2f%%\n",
              comp_ratio); // print compression ratio
    }

    wt_delete(wt); // delete word table
  } else {
    printf("Incorrect magic number.\n"); // if incorrect magic number read,
                                         // don't start compression.
    exit(-3);
  }
  free(fh);   // free memory for FileHeader
  close(out); // close output file
  close(in);  // close input file
  return 0;
}
