#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool contained(int s1, int e1, int s2, int e2) {
  // s1 ... e1
  // s2 ... e2

  if (s1 <= s2 && e1 >= e2) { return true; }
  if (s2 <= s1 && e2 >= e1) { return true; }
  return false;
}

bool overlap(int s1, int e1, int s2, int e2) {
  // s1 ... e1
  // s2 ... e2

  if (e1 < s2) { return false; }
  if (e2 < s1) { return false; }
  return true;
}

int main(int argc, char **argv) {
  FILE *inp = NULL;
  inp = fopen("four.txt", "r+");

  char *assignment = NULL;
  size_t line_read_len = 0;

  int t_f_c = 0;
  int t_f_c_a = 0;

  while (getline(&assignment, &line_read_len, inp) != -1) {
    int s1, s2, e1, e2;
    sscanf(assignment, "%d-%d,%d-%d", &s1, &e1, &s2, &e2);

    if (contained(s1, e1, s2, e2)) { t_f_c++; }
    if (overlap(s1, e1, s2, e2)) { t_f_c_a++; }
  }
  printf("Total containments: %d\n", t_f_c);
  printf("Total overlap: %d\n", t_f_c_a);
}
