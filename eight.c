
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum vis { UNCHECKED, VISIBLE, HIDDEN } vis_t;
typedef enum dir { UP, DOWN, LEFT, RIGHT } dir_t;

// #define DEBUG

// This is not a real tree.
typedef struct tree {
  int val;
  bool visible;
  vis_t dir_vis[4];
} tree_t;

int total_visible = 0;

int max_direction(tree_t **matrix, int i, int j, int grid_size, dir_t dir) {
  int i1 = i, j1 = j;
  int max = 1;
  while (!((i1 < 0 || i1 == grid_size) || (j1 < 0 || j1 == grid_size))) {
    if (matrix[i1][j1].val > max) { max = matrix[i1][j1].val; }

    switch (dir) {
    case UP: i1 -= 1; break;
    case DOWN: i1 += 1; break;
    case LEFT: j1 -= 1; break;
    case RIGHT: j1 += 1; break;
    }
  }
  return max;
}
int visible_trees(tree_t **matrix, int i, int j, int grid_size, dir_t dir) {
  int orig_tree_height = matrix[i][j].val;

  int i1 = i, j1 = j;
  switch (dir) {
  case UP: i1 -= 1; break;
  case DOWN: i1 += 1; break;
  case LEFT: j1 -= 1; break;
  case RIGHT: j1 += 1; break;
  }

  int visible = 0;
  while (!((i1 < 0 || i1 == grid_size) || (j1 < 0 || j1 == grid_size))) {
    if (matrix[i1][j1].val >= orig_tree_height) {
      visible++;
      goto end;
    }

    switch (dir) {
    case UP: i1 -= 1; break;
    case DOWN: i1 += 1; break;
    case LEFT: j1 -= 1; break;
    case RIGHT: j1 += 1; break;
    }
    visible++;
  }
end:
  return visible;
}
void check_direction(tree_t **matrix, int i, int j, int grid_size, dir_t dir) {
  // Calculate piece directly 1 to the direction specified
  int i1 = i, j1 = j;
  switch (dir) {
  case UP: i1 -= 1; break;
  case DOWN: i1 += 1; break;
  case LEFT: j1 -= 1; break;
  case RIGHT: j1 += 1; break;
  }
  // Check if out of bounds, and if so mark as visible from the given direction
  if ((i1 < 0 || i1 == grid_size) || (j1 < 0 || j1 == grid_size)) {
    goto visible;
    return;
  }

  // If the current node's direction is unchecked we check it
  if (matrix[i1][j1].dir_vis[dir] == UNCHECKED)
    check_direction(matrix, i1, j1, grid_size, dir);

  // If the node is checked, then we can check if the current node is visible
  if (matrix[i1][j1].dir_vis[dir] == VISIBLE &&
      matrix[i][j].val > matrix[i1][j1].val) {
    goto visible;
  } else {
    // Edge case where all the nodes in the given direction are less than the
    // current node
    //
    int max_in_dir = max_direction(matrix, i1, j1, grid_size, dir);
    if (matrix[i][j].val > max_in_dir) {
#ifdef DEBUG
      printf("DEBUG: Adding %d %d from edge case\n", i, j);
#endif
      goto visible;
    }

    matrix[i][j].dir_vis[dir] = HIDDEN;
    return;
  }

visible:
  matrix[i][j].dir_vis[dir] = VISIBLE;
  if (!matrix[i][j].visible) {
#ifdef DEBUG
    printf("DEBUG: matrix[%d][%d] = %d is visible\n", i, j, matrix[i][j].val);
#endif
    total_visible++;
  }
  matrix[i][j].visible = true;
}

int main(int argc, char **argv) {
  FILE *inp = NULL;
  inp = fopen("eight.txt", "r+");

  char *l = NULL;
  size_t line_read_len = 0;

  tree_t **tree_matrix;
  int grid_size;

  int row = 0;
  while (getline(&l, &line_read_len, inp) != -1) {
    grid_size = strlen(l);
    l[grid_size - 1] = "\0";
    grid_size--;

    if (tree_matrix == NULL) {
#ifdef DEBUG
      printf("DEBUG: Grid size is %d\n", grid_size);
#endif
      tree_matrix = calloc(grid_size, sizeof(int *));
      for (int i = 0; i < grid_size; i++) {
        tree_matrix[i] = calloc(grid_size, sizeof(tree_t));
      }
    }
    for (int i = 0; i < grid_size; i++) {
      tree_matrix[row][i].val = l[i] - '0';
    }
    row++;
  }
  // Print matrix
  int max_scenic_score = 0;
  for (int i = 0; i < grid_size; i++) {
    for (int j = 0; j < grid_size; j++) {

      int scenic_score = 1;
      // Check directional + scenic scores
      for (int k = 0; k < 4; k++) {
        int vis_dir_trees = visible_trees(tree_matrix, i, j, grid_size, k);
        scenic_score *= vis_dir_trees;
        check_direction(tree_matrix, i, j, grid_size, k);
      }
      if (scenic_score > max_scenic_score) { max_scenic_score = scenic_score; }
#ifdef DEBUG
      printf("tree_matrix[%d][%d] scenic score %d\n", i, j, scenic_score);
#endif
    }
#ifdef DEBUG
    printf("\n");
#endif
  }
  printf("Total visible nodes is %d\n", total_visible);
  printf("Max scenic score is %d\n", max_scenic_score);
}
