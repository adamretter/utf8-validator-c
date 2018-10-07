/**
 * Simple command line driver for https://github.com/lemire/fastvalidate-utf-8
 *
 * Command line driver by Adam Retter <adam.retter@googlemail.com>
 *
 * Apache 2.0 License
 */
#include "simdutf8check.h"
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define EXIT_UTF8_INVALID 2
#define EXIT_IO_ERROR 4

void show_usage(const char *exe_name) {
  printf("UTF8 Validator (C edition) version: 1.0\n");
  printf("Usage: %s <filename>\n", exe_name);
}

int main(int argc, const char *argv[]) {
  int fd, ret;
  size_t len_file;
  struct stat st;
  char *addr;

  bool result;

  clock_t start, stop;

  if (argc < 2) {
    show_usage(argv[0]);
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
    show_usage(argv[0]);
    return EXIT_SUCCESS;
  }

  start = clock();

  if ((fd = open(argv[1], O_RDONLY)) < 0) {
    perror("Error in file opening");
    return EXIT_IO_ERROR;
  }

  if ((ret = fstat(fd, &st)) < 0) {
    perror("Error in fstat");
    return EXIT_IO_ERROR;
  }

  len_file = st.st_size;

  if ((addr = mmap(NULL, len_file, PROT_READ, MAP_PRIVATE, fd, 0)) ==
      MAP_FAILED) {
    perror("Error in mmap");
    return EXIT_IO_ERROR;
  }

  printf("Validating: %s\n", argv[1]);

  result = validate_utf8_fast(addr, len_file);

  if (munmap(addr, len_file) == -1) {
    perror("Error in munmap");
  }

  if (close(fd)) {
    perror("Error in close");
  }

  stop = clock();
  double elapsed_ms = (((double)stop - start) / CLOCKS_PER_SEC) * 1000;

  printf("Valid %s (took %fms)\n", result ? "OK" : "FAILED", elapsed_ms);

  return result ? EXIT_SUCCESS : EXIT_UTF8_INVALID;
}
