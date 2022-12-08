#pragma once

typedef struct lln {
  void *data;
  struct lln *next;
} lln_t;

void enq(lln_t **h, void *d);
void push(lln_t **h, void *d);
void *pop(lln_t **h);
void *dequeue(lln_t **h);
void p_s(lln_t **h);
