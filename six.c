
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

// 14 for part 2, 4 for part 1
#define SEQ_STRING 14

int main(int argc, char **argv) {
  FILE *inp = NULL;
  inp = fopen("six.txt", "r+");

  char *l = NULL;
  size_t line_read_len = 0;

  // dont feel like adding
  int table[130] = {0};
  int a;

  while (getline(&l, &line_read_len, inp) != -1) {}
  int len = strlen(l);
  l[len - 1] = "\0";
  len--;

  for (int i = 0; i < len; i++) {
    bool q = true;
    for (int j = 0; j < SEQ_STRING; j++) {
      table[l[i + j]]++;
      if (table[l[i + j]] > 1) {
        q = false;
        break;
      }
    }
    if (q) {
      a = i;
      break;
    }
    memset(table, 0, sizeof(table));
  }

  printf("%s\n", l);
  printf("%d\n", a + SEQ_STRING);
}
