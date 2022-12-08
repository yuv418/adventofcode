#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  FILE *inp;
  inp = fopen("three.txt", "r+");

  char *compartments = NULL;
  size_t line_read_len;

  int t_p = 0;

  while (getline(&compartments, &line_read_len, inp) != -1) {
    int c_l = strlen(compartments);
    // Remove newline
    compartments[c_l - 1] = "\0";
    c_l--;

    // printf("compartment %s len %d\n", compartments, c_l);

    // Split rucksacks
    // int *rs1 = malloc((c_l / 2) * sizeof(int));
    // int *rs2 = malloc((c_l / 2) * sizeof(int));

    int rs1[52] = {0};
    int rs2[52] = {0};

    int pri_add;

    for (int i = 0; i < c_l; i++) {
      // lowercase
      int v;
      if (compartments[i] >= 97) {
        v = compartments[i] - 97;
      }
      // uppsercase
      else {
        v = compartments[i] - 65 + 26;
      }

      if (i >= c_l / 2) {
        if (rs1[v]) { pri_add = v + 1; }
      } else {
        rs1[v]++;
      }
    }
    // printf("pri_add is %d total %d\n", pri_add, t_p);
    t_p += pri_add;
  }
  printf("Total priority %d\n", t_p);
}
