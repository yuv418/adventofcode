#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binaryheap.h"

#define ELF_LIMIT 500

int main(int argc, char **argv) {
  FILE *inp;

  inp = fopen("one.txt", "r+");
  char *current_num;
  size_t line_read_len;

  int max_cal;
  int max_cal_elf;

  int current_cal;
  int current_cal_elf;

  // Predefining this limit is not the best idea but we would have to implement
  // a resizing PQ otherwise
  pq_t q = {
      .heap = malloc(ELF_LIMIT * sizeof(int)),
      .sz = ELF_LIMIT,
      .i = 1,
  };

  while (getline(&current_num, &line_read_len, inp) != -1) {
    if (strcmp(current_num, "\n") != 0) {
      current_cal += atoi(current_num);
      // printf("added %d, elf %d has %d calories\n", atoi(current_num),
      // current_cal_elf, current_cal);
    } else {
      // printf("finished elf %d, it has %d calories\n", current_cal_elf,
      // current_cal);
      insert(&q, current_cal);

      if (current_cal >= max_cal) {
        max_cal = current_cal;
        max_cal_elf = current_cal_elf;
      }

      current_cal = 0;
      current_cal_elf++;
    }
  }

  printf("Elf with the most calories is %d, that elf has %d cals\n",
         max_cal_elf + 1, max_cal);

  printf("Top 3 elves: \n");

  int rsum = 0;
  for (int i = 0; i < 3; i++) {
    int v = pop(&q);
    printf("%d. %d\n", i + 1, v);
    rsum += v;
  }
  printf("Total cals of top three elves: %d\n", rsum);
}
