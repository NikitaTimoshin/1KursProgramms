#include "libra.h"
#include <stdio.h>

FILE *fp1;

int i = 0;
int l = 0;
int St = 0;
int Ch = 0;

void Proceses(char *b1, char *b2, int size, int *proc) {

  char buf1[size], buf2[size];

  if (Ch == 0) {
    if ((fp1 = fopen("start1.txt", "r")) == NULL)
      printf("Failed open file\n");
    Ch = 1;
  }

  while (1) {
    if ((*proc > 5) && (*proc < 55) && (St == 0)) {
      fscanf(fp1, "%c", &buf1[i]);
      printf("Process one...\n");
      if (feof(fp1)) {
        St = 1;
        fclose(fp1);
        break;
      }
      b1[i] = buf1[i];
      i = i + 1;
      break;
    }
    if ((*proc > 55) && (*proc < 105) && (St == 0)) {
      printf("Process two...\n");
      fscanf(fp1, "%c", &buf2[l]);
      if (feof(fp1)) {
        St = 1;
        fclose(fp1);
        break;
      }
      b2[l] = buf2[l];
      l = l + 1;
      break;
    }
    if ((*proc > -1) && (*proc < 6)) {
      printf("Process three...\n");
      St = 1;
      fclose(fp1);
      break;
    }
    if (St == 1)
      break;
    break;
  }
}
