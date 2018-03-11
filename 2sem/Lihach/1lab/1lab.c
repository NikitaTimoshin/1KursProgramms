#include "libra.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  int proc;
  char b1[100], b2[100];
  srand(time(0));

  while ((St1 == 0) || (St2 == 0)) {
    proc = (rand() % 106);
    Proceses(b1, b2, sizeof(b1), &proc);
  }
  printf("Symbols 1file = %s\n", b1);
  printf("Symbols 2file = %s\n", b2);
  return 0;
}
