#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void enq(lln_t **h, char d) {
  // Questionable implementation
  lln_t *n_h = malloc(sizeof(lln_t));
  n_h->data = d;
  if (*h != NULL) {
    n_h->next = (*h)->next;
    (*h)->next = n_h;
  } else {
    n_h->next = n_h;
  }

  *h = n_h;
}

void push(lln_t **h, char d) {
  lln_t *n_h = malloc(sizeof(lln_t));
  n_h->data = d;
  if ((*h) == NULL) {
    n_h->next = n_h;
    *h = n_h;
  } else {
    n_h->next = (*h)->next;
    (*h)->next = n_h;
  }
}

char pop(lln_t **h) {
  if ((*h) == (*h)->next) {
    char d = (*h)->data;
    *h = NULL;
    return d;
  }
  lln_t *o_h = (*h)->next;
  char d = o_h->data;
  (*h)->next = o_h->next;

  free(o_h);
  return d;
}

void p_s(lln_t **h) {
  if ((*h) != NULL) {
    lln_t *i = (*h)->next;
    do {
      printf("%c -> ", i->data);
      int a = i == *h;
      i = i->next;
      if (i == *h && !a) { printf("%c -> ", i->data); }
    } while (i != *h);
  }
  printf("\n");
}
