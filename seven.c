
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "binaryheap.h"
#include "stack.h"

// 14 for part 2, 4 for part 1
#define SEQ_STRING 14

typedef struct fsnode {
  bool is_file;
  char *name;

  size_t file_size;

  lln_t *files;
  lln_t *dirs;

  struct fsnode *parent;
} fsnode_t;

size_t total_dir_sizes_under_threshhold(fsnode_t *root);
size_t threshhold_total = 0;
size_t total_dirs = 1;
pq_t dir_size_heap;

int main(int argc, char **argv) {
  FILE *inp = NULL;

  printf("Reading file %s\n", argv[1]);
  inp = fopen(argv[1], "r+");

  char *line = NULL;
  size_t line_read_len = 0;

  fsnode_t root = {
      .is_file = false,
      .name = NULL,
      .file_size = 0,
      .files = NULL,
      .dirs = NULL,
      .parent = NULL,
  };

  fsnode_t *current_dir = &root;

  while (getline(&line, &line_read_len, inp) != -1) {
    line[strlen(line) - 1] = "\0";
    // printf("Line was %s\n", line);

    if (strstr(line, "$")) {
      if (strstr(line, "cd")) {
        if (strstr(line, "..")) {
          // Go to parent directory
          current_dir = current_dir->parent;
        } else if (!strstr(line, "/")) {
          // Go to a child directory
          // Initialize with that length because "$ cd " is 4 characters
          char child_dir_name[strlen(line) - 4];
          sscanf(line, "$ cd %s", child_dir_name);

          // Could I implement some kind of binary tree for this for efficiency?

          lln_t *i = current_dir->dirs;
          do {
            if (strcmp(((fsnode_t *)i->data)->name, child_dir_name) == 0) {
              current_dir = (fsnode_t *)i->data;
              break;
            }
            i = i->next;
          } while (i != current_dir->dirs);
        }
      }
    }
    // Otherwise, we are in a directory listing.
    else {
      // Hopefully this is big enough?? Obviously we can get the exact amount
      // but w/e
      char *child_name = malloc(100);
      // Is a directory
      if (strstr(line, "dir")) {
        fsnode_t *child_dir = malloc(sizeof(fsnode_t));

        sscanf(line, "dir %s", child_name);
        child_dir->parent = current_dir;
        child_dir->name = child_name;
        total_dirs++;

        enq(&current_dir->dirs, (void *)child_dir);
      }
      // Is a file
      else {
        fsnode_t *child_file = malloc(sizeof(fsnode_t));
        sscanf(line, "%lu %s", &child_file->file_size, child_name);
        child_file->name = child_name;
        child_file->parent = current_dir;

        enq(&current_dir->files, (void *)child_file);
      }
    }
  }

  // FS tree is constructed. Now we can get the sizes of every dir

  dir_size_heap.heap = malloc((total_dirs + 1) * sizeof(int));
  dir_size_heap.sz = total_dirs;
  dir_size_heap.i = 1;

  size_t total_root_size = total_dir_sizes_under_threshhold(&root);
  size_t required_space = 30000000 - (70000000 - total_root_size);

  printf("Total value is %lu\n", threshhold_total);
  printf("Total root size is %lu\n", total_root_size);
  printf("Total required space is %lu\n", required_space);
  printf("Total dirs %lu\n", total_dirs);

  while (true) {
    int i_dir_size = -pq_pop(&dir_size_heap);
    // printf("i_dir_size is %d\n", i_dir_size);
    if (i_dir_size >= required_space) {
      printf("Delete directory with size %d\n", i_dir_size);
      break;
    }
  }
}

size_t total_dir_sizes_under_threshhold(fsnode_t *root) {

  size_t total_file_sum = 0;
  lln_t *i;
  // Only if the files are not NULL
  if (root->files) {
    // Loop through files
    i = root->files;
    do {
      size_t current_file_size = ((fsnode_t *)i->data)->file_size;
      /*printf("Directory %s adding %lu from file %s\n", root->name,
             current_file_size, ((fsnode_t *)i->data)->name);*/
      total_file_sum += current_file_size;
      i = i->next;
    } while (i != root->files);
  }

  // Only if the dirs are not NULL
  if (root->dirs) {
    i = root->dirs;
    do {
      total_file_sum += total_dir_sizes_under_threshhold(((fsnode_t *)i->data));
      i = i->next;
    } while (i != root->dirs);
  }

  if (total_file_sum <= 100000) { threshhold_total += total_file_sum; }
  insert(&dir_size_heap, -total_file_sum);

  return total_file_sum;
}
