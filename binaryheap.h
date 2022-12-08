#pragma once

typedef struct pq {
  int *heap;
  int sz;
  int i;
} pq_t;

void swap(pq_t *q, int key1, int key2);
void sink(pq_t *q, int key);
void insert(pq_t *q, int val);
int pop(pq_t *q);
void print_q(pq_t *q);
