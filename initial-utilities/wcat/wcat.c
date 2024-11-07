#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <limits.h>

// don't expect a line of a file to be > 1000 chars
#define MAX_LINE 1000

void print_usage() {
  printf("wcat: Pass a single relative filepath - print file to stdout.");
}

int main(int argc, char* argv[]) {
  if (argc != 2) {
    print_usage();
  }
  FILE* f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("File read error.");
    exit(1);
  }
  char* str = (char*) malloc(MAX_LINE);
  if (str == NULL) {
    printf("Memory for str not allocated.");
    exit(1);
  }
  while (fgets(str, MAX_LINE, f)) {
    printf("%s", str);
  }
  free(str);
  exit(0);
}
