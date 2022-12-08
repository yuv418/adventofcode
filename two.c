#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WIN_VAL 6
#define PART_TWO 1

// Rock 1
// Scissors 2
// Paper 3
typedef enum rps_t { ROCK = 1, PAPER = 2, SCISSORS = 3 } rps;
typedef enum result_t { LOSE = 'X', DRAW = 'Y', WIN = 'Z' } result;

int det_win(enum rps_t mv1, enum rps_t mv2) {
  if (mv1 == mv2) { return 0; }

  switch (mv1) {
  case ROCK:
    if (mv2 == PAPER) return 2;
    if (mv2 == SCISSORS) return 1;
  case PAPER:
    if (mv2 == SCISSORS) return 2;
    if (mv2 == ROCK) return 1;
  case SCISSORS:
    if (mv2 == ROCK) return 2;
    if (mv2 == PAPER) return 1;
  default: return -1;
  }
}

int score(enum rps_t m) {
  switch (m) {
  case ROCK: return 1;
  case SCISSORS: return 2;
  case PAPER: return 3;
  }
}

enum rps_t find_move(enum rps_t mv1, enum result_t r) {
  if (r == DRAW) return mv1;
  switch (mv1) {
  case ROCK:
    if (r == WIN) return PAPER;
    if (r == LOSE) return SCISSORS;
  case PAPER:
    if (r == WIN) return SCISSORS;
    if (r == LOSE) return ROCK;
  case SCISSORS:
    if (r == WIN) return ROCK;
    if (r == LOSE) return PAPER;
  }
}

int main(int argc, char **argv) {
  FILE *inp = NULL;
  inp = fopen("two.txt", "r+");

  char *round = NULL;
  size_t line_read_len;

  int pl_sc;
  int op_sc;

  while (getline(&round, &line_read_len, inp) != -1) {
    char op_mv_c, pl_mv_c;
    sscanf(round, "%c %c", &op_mv_c, &pl_mv_c);

    enum rps_t op_mv, pl_mv;

    switch (op_mv_c) {
    case 'A': op_mv = ROCK; break;
    case 'B': op_mv = PAPER; break;
    case 'C': op_mv = SCISSORS; break;
    }

#ifdef PART_TWO

    enum result_t pl_r = pl_mv_c;
    pl_mv = find_move(op_mv, pl_r);

    // printf("Chose player move %d\n", pl_mv);

#else

    switch (pl_mv_c) {
    case 'X': pl_mv = ROCK; break;
    case 'Y': pl_mv = PAPER; break;
    case 'Z': pl_mv = SCISSORS; break;
    }

#endif

    int w = det_win(pl_mv, op_mv);

    if (w == 1) pl_sc += 6;
    else if (w == 2) op_sc += 6;
    else if (w == 0) {
      op_sc += 3;
      pl_sc += 3;
    }

    pl_sc += pl_mv;
    op_sc += op_mv;
  }
  printf("Player score is %d\n", pl_sc);
  printf("Opponent score is %d\n", op_sc);
}
