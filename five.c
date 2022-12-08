#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stack.h"

#define PART_TWO 0

int main(int argc, char **argv) {
  FILE *inp = NULL;
  inp = fopen("five.txt", "r+");

  char *l = NULL;
  size_t line_read_len = 0;

  lln_t **s_s = {NULL};
  int s_w = 0;

  while (getline(&l, &line_read_len, inp) != -1) {
    if (strstr(l, "[")) {
      int line_len = strlen(l);
      l[line_len - 1] = "\0";
      line_len--;

      if (s_s == NULL) {
        s_w = ((line_len + 1) / 4);
        printf("s_w is %d\n", s_w);
        s_s = malloc(s_w * sizeof(lln_t *));
        memset(s_s, 0, sizeof(lln_t *));
      }
      printf("line %s line_len %d\n", l, line_len);

      for (int i = 1; i < line_len; i += 4) {
        int r_i = (i - 1) / 4;
        if (l[i] != ' ') {
          printf("%d %c\n", r_i, l[i]);
          enq(&s_s[r_i], (void *)l[i]);
        }
      }
    } else if (strstr(l, "move")) {
      int num, src, dest;
      sscanf(l, "move %d from %d to %d", &num, &src, &dest);
      printf("move %d from %d to %d\n", num, src, dest);

      src--;
      dest--;

#ifdef PART_TWO
      lln_t *d = NULL;
#endif
      for (int i = 0; i < num; i++) {
        char p = (char)pop(&s_s[src]);
#ifdef PART_TWO
        push(&d, (void *)p);
// printf("Popped %c\n", p);
#else
        push(&s_s[dest], p);
#endif
      }
#ifdef PART_TWO
      for (int i = 0; i < num; i++) {
        char p = (void *)pop(&d);
        push(&s_s[dest], (void *)p);
      }
#endif

    } else {
    }
  }

  char msg[s_w + 1];
  for (int i = 0; i < s_w; i++) {
    p_s(&s_s[i]);
    msg[i] = pop(&s_s[i]);
  }
  msg[s_w] = '\0';
  printf("Message is %s\n", msg);
}
