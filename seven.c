
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

// 14 for part 2, 4 for part 1
#define SEQ_STRING 14

typedef struct fsnode {
  bool is_dir;

} fsnode_t;

int main(int argc, char **argv) {
  FILE *inp = NULL;
  inp = fopen("six.txt", "r+");

  char *l;
  size_t line_read_len;

  while (getline(&l, &line_read_len, inp) != -1) {}
}
