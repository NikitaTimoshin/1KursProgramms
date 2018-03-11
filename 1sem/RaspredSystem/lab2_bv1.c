#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

int exit_function = 0;

void sighandler (int signo){
  exit_function = 1;
}

void printf_a() {
  alarm (3);
  signal(SIGALRM, sighandler);
  while (1) {
    printf("%c", 'A');
    if (exit_function) {
      exit_function = 0;
      break;
    }
  }
}

void printf_b() {
  alarm (3);
  signal(SIGALRM, sighandler);
  while (1) {
    printf("%c", 'B');
    if (exit_function) {
      exit_function = 0;
      break;
    }
  }
}

int main(int argc, char const *argv[]) {
  while (1) {
  printf_a();
  printf_b();
}
return 0;
}
