#define BLOCK 4096
#include "io.h"
#include "bv.h"
#include "code.h"
#include "endian.h"
#include <ctype.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

static uint32_t bpi = 0;         // bit counter for writing encodings.
static BitVector *buffer = NULL; // Bitvector buffer to store encodings.
static uint8_t wbuff[BLOCK];     // Buffer to store decoded words
uint32_t bwi = 0;                // Byte index of the buffer(wbuff)

// Read header
void read_header(int infile, FileHeader *header) {
  read(
      infile, header,
      sizeof(
          FileHeader)); // Read size of FileHeader bytes from file to FileHeader
  if (is_little() == false) {              // If not little endian
    header->magic = swap32(header->magic); // Swap endianess
    header->protection = swap16(header->protection);
  }
  return;
}

// Write header
void write_header(int outfile, FileHeader *header) {
  if (is_little() == false) {              // If not little endian
    header->magic = swap32(header->magic); // swap endianess
    header->protection = swap16(header->protection);
  }
  write(outfile, header,
        sizeof(FileHeader)); // Write FileHeader set to output file
  return;
}

// Read next sym in file
bool read_sym(int infile, uint8_t *sym) {
  static int curr_index = 0;     // index in buffer
  static uint8_t *buffer = NULL; // buffer
  static int eof = 0;            // Index of end of file
  static int r_size = 0;         // Variable to store amount of bytes read
  // If buffer is empty, initialized. If buffer index reaches 4096 or end of
  // file.
  if (!buffer || curr_index == BLOCK || curr_index == eof) {
    if (buffer) {
      free(buffer);
      buffer = NULL;
    }
    buffer = (uint8_t *)calloc(BLOCK, sizeof(uint8_t)); // Reset buffer
    curr_index = 0;                                     // Reset buffer index
    if (buffer) {
      r_size = read(infile, buffer, BLOCK); // Read the next block of data.
      eof = r_size;                         // set eof file index
    }
  }
  if (r_size != 0) {
    if (r_size == BLOCK) {               // if a block is read
      *sym = buffer[curr_index];         // Grab symbol at buffer index.
      curr_index++;                      // Increment index
    } else if (eof < BLOCK && eof > 0) { // if end of file not reached yet
      if (curr_index < eof) {
        *sym = buffer[curr_index]; // read symbol from buffer.
        curr_index++;              // Increment index.
      }
    }
  } else {
    if (buffer) {
      free(buffer); // If nothing more can be read, free the buffer
      buffer = NULL;
    }
    return false; // Return false to indicate no more symbols can be read
  }

  return true; // Return true if more symbols can be read
}

// Flush pairs in buffer to file
void flush_pairs(int outfile) {
  if (buffer) {
    if (bpi % 8 == 0) {
      write(outfile, buffer->vector,
            bpi / 8); // Write the amount of bytes written
    } else {
      write(outfile, buffer->vector,
            bpi / 8 + 1); // If bytes not a multiple of 8 add one byte
    }
  }
  return;
}

// Buffer pairs
void buffer_pair(int outfile, uint16_t code, uint8_t sym, uint8_t bitlen) {
  if (buffer == NULL) { // Initialize buffer if NULL.
    buffer = bv_create(
        BLOCK * 8); // Initialize as bitvector with number of bits in a block.
  }
  if (buffer) { // if buffer exists.
    // Set code bits
    for (int i = 0; i < bitlen; i++) { // Iterate over bits for code
      uint16_t cpy = code;             // Save code to temp
      // Mask the bit at index i.
      uint16_t masking = 1 << (i % bitlen);
      uint16_t masked = cpy & masking;
      uint16_t bit = masked >> (i % bitlen);
      // if bit masked is 1, set it in buffer
      if (bit == 1 && bpi < BLOCK * 8 && buffer->vector) {
        bv_set_bit(buffer, bpi);
      }
      // if bit masked is 0, clr it in buffer.
      else if (bit == 0 && bpi < BLOCK * 8 && buffer->vector) {
        bv_clr_bit(buffer, bpi);
      }
      // increment bit index of buffer.
      bpi++;
      // If buffer is full, write it to file. Reset buffer index.
      if (bpi == 8 * BLOCK && buffer->vector) {
        write(outfile, buffer->vector, BLOCK);
        bpi = 0;
      }
    }
    // Set symbol bits
    for (int k = 0; k < 8; k++) { // Iterate over bits in sym(fixed at 8 bits)
      uint8_t cpy = sym;          // Save symbol to temp
      // Mask the bit at index k
      uint8_t masking = 1 << (k % 8);
      uint8_t masked = cpy & masking;
      uint8_t bit = masked >> (k % 8);
      // if bit masked is 1, set it in buffer.
      if (bit == 1 && bpi < BLOCK * 8 && buffer->vector) {
        bv_set_bit(buffer, bpi);
      }
      // if bit masked is 0, clr it in buffer.
      else if (bit == 0 && bpi < BLOCK * 8 && buffer->vector) {
        bv_clr_bit(buffer, bpi);
      }
      // increment but index of buffer.
      bpi++;
      // If buffer is full, write it to file, Reset buffer index.
      if (bpi == BLOCK * 8) {
        write(outfile, buffer->vector, BLOCK);
        bpi = 0;
      }
    }
    // Write buffer if last buffered pair fits end of buffer. Reset index.
    if (bpi == BLOCK * 8) {
      write(outfile, buffer->vector, BLOCK);
      bpi = 0;
    }
  }
  return;
}

// Read pairs written out.
bool read_pair(int infile, uint16_t *code, uint8_t *sym, uint8_t bitlen) {
  static uint32_t index = 0;        // buffer index
  *code = 0;                        // Set passed in value to 0
  *sym = 0;                         // Set passed in value to 0
  static BitVector *rbuffer = NULL; // buffer to read to
  uint16_t c = 0;                   // temp code var
  uint8_t s = 0;                    // temp sym var
  // initialize buffer if empty
  if (rbuffer == NULL) {
    rbuffer = bv_create(8 * BLOCK); // Size of bits in block
    if (rbuffer && rbuffer->vector) {
      read(infile, rbuffer->vector, BLOCK); // Read to buffer
    }
  }
  if (rbuffer && rbuffer->vector) {
    // iterate over bit length code.
    for (int i = 0; i < bitlen; i++) {
      uint8_t bit = bv_get_bit(rbuffer, index); // Get bit at index
      if (bit == 1) {
        c |= (1 << (i % bitlen)); // if bit is 1, set in temp variable
      }
      index++; // increment bit index
      // if buffer is full, reset index and read to buffer
      if (index == BLOCK * 8) {
        read(infile, rbuffer->vector, BLOCK);
        index = 0;
      }
    }
    *code = c; // set passed in variable to code set
    // If stop code is read, stop reading pairs
    if (*code == STOP_CODE) {
      return false; // Return false to indicate no more pairs can be read.
    }
    // Iterate over 8 bits of symbol
    for (int k = 0; k < 8; k++) {
      uint8_t bit = bv_get_bit(rbuffer, index); // Get bit at index.
      if (bit == 1) {
        s |= (1 << (k % 8)); // if bit is 1, set in temp variable
      }
      index++; // increment bit index.
      // if buffer is full, reset index and read to buffer.
      if (index == BLOCK * 8) {
        read(infile, rbuffer->vector, BLOCK);
        index = 0;
      }
    }
    *sym = s; // set passed in variable to symbol set.

    // if buffer is full, reset it and read.
    if (index == BLOCK * 8) {
      read(infile, rbuffer->vector, BLOCK);
      index = 0;
    }
  }
  return true; // Return true to indicate more pairs can be read.
}

// buffer words to write to decompressed file
void buffer_word(int outfile, Word *w) {
  // Iterate over length of word to buffer
  for (uint32_t k = 0; k < w->len; k++) {
    if (bwi < BLOCK) {         // if byte index is less than a block
      wbuff[bwi] = w->syms[k]; // write symbol to buffer at byte index.
    }
    bwi++; // increment byte index.
    // if buffer is full, write out to file and reset index.
    if (bwi == BLOCK) {
      write(outfile, wbuff, BLOCK);
      bwi = 0;
    }
  }
  return;
}

// wriet buffer to file with no condition.
void flush_words(int outfile) {
  write(outfile, wbuff,
        bwi); // Write byte index amount of bytes to decompressed file.
  return;
}
