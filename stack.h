#pragma once

typedef struct lln {
  char data;
  struct lln *next;
} lln_t;

void enq(lln_t **h, char d);
void push(lln_t **h, char d);
char pop(lln_t **h);
char dequeue(lln_t **h);
void p_s(lln_t **h);
