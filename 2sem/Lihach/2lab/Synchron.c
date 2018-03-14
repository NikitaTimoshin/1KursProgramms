#include <stdio.h>
#include <stdlib.h>

int *Conv, *Stat;
int n, i, z, x, m;

void Conveer() {
  for (i = 0; i < n; i++) {
    if ((Conv[i] == 1) && (Stat[i] != 0))
      Stat[i]--;

    if (Stat[i] == 0) {
      Conv[i] = 0;
      Conv[i + 1] = 1;
    }
    if ((Conv[n - 1] == 0) && (Stat[n - 1] == 0)) {
      x++;
    }
    if ((Conv[i] == 0) && (Stat[i] == 0)) {
      Conv[i] = 1;
      Stat[i] = 7;
    }

    printf("Conv [%d] = %d  Stat [%d] = %d\n\n", i, Conv[i], i, Stat[i]);
  }
}

int main() {

  printf("Введите размер конвеера - ");
  scanf("%d", &n);
  printf("Введите количество символов - ");
  scanf("%d", &m);
  Conv = (int *)malloc(n * sizeof(int));
  Stat = (int *)malloc(n * sizeof(int));

  for (i = 0; i < n; i++) {
    Conv[i] = 0;
    Stat[i] = 7;
    Conv[0] = 1;
  }
  z = 0;
  x = 0;

  while (x < m) {

    Conveer();
    z++;
    printf("z = %d\nx = %d\n", z, x);
    printf("-----------------------------------------------------\n");
  }
z=z+(n-1);
  printf("Conv = %d  Stat = %d", Conv[n - 1], Stat[n - 1]);
  printf("Количество тактов = %d\n", z);
  return 0;
}
