#include "binaryheap.h"
#include <stdio.h>

// Implement a max priority queue

void swap(pq_t *q, int key1, int key2) {
  int temp = q->heap[key1];
  q->heap[key1] = q->heap[key2];
  q->heap[key2] = temp;
}

void sink(pq_t *q, int key) {
  // No children
  if (key * 2 < q->sz) {
    if (q->heap[key] < q->heap[key * 2] ||
        q->heap[key] < q->heap[(key * 2) + 1]) {
      // Choose the greater child key

      int gc_key = 0;
      if (q->heap[key * 2] > q->heap[(key * 2) + 1]) {
        gc_key = key * 2;
      } else {
        gc_key = (key * 2) + 1;
      }

      swap(q, key, gc_key);
      sink(q, gc_key);
    }
  }

  // Heap is consistent, return
}

void swim(pq_t *q, int key) {
  if (key > 1) {
    if (q->heap[key] > q->heap[key / 2]) {
      swap(q, key, key / 2);
      swim(q, key / 2);
    }
  }
}

void insert(pq_t *q, int val) {
  q->heap[q->i] = val;
  swim(q, q->i);

  q->i++;
}

int pop(pq_t *q) {
  swap(q, 1, q->i - 1);
  int d = q->heap[q->i - 1];
  q->heap[q->i - 1] = 0;
  q->i--;
  sink(q, 1);

  return d;
}

void print_q(pq_t *q) {
  printf("----\n");
  for (int i = 1; i < q->i; i++) {
    printf("%d\n", q->heap[i]);
  }
  printf("----\n");
}
