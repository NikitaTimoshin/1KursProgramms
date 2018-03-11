#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  char a[20];
  gets(a);
  printf("%s\n", a);
sleep(100);
  return 0;
}
