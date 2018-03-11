
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

FILE *file;

void func(int *x, int *y, int size, char *Txt) {

  char buf[size];

  while (1) {
    printf("x = %d\n", *x);
    fscanf(file, "%c", &buf[*x]);

    if (feof(file)) {
      *y = 20;
      fclose(file);
      break;
    }

    Txt[*x] = buf[*x];
    *x = *x + 1;
    *y = *y + 1;
    break;
  }
}

int main() {
  int x = 0;
  int y = 0;
  //char Txt[100];

while (x<20)
{
printf("x = %d\n", x);
  while (y<20)
  {
    printf("y = %d\n", y);
    y++;
  }
  x++;
}


/*
  if ((file = fopen("test.txt", "r")) == NULL)
    printf("Файл невозможно открыть или создать\n");

  while (1) {
    func(&x, &y, sizeof(Txt), Txt);


    printf("y = %d\n", y);
    printf("Txt = %s\n", Txt);
    // sleep(1);
    if (y == 20)
      break;
  }
  printf("Txt = %s\n", Txt);
*/

  return 0;
}
