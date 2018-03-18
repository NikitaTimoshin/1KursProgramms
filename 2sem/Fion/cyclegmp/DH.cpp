#include <gmp.h>
#include <rdtsc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

FILE *fp;

int main() {

  gmp_randstate_t state;
  gmp_randinit_mt(state);
  gmp_randseed_ui(state, time(0));
  mpz_t q, p, g, x, y, X, Y, xx, yy;
  mpz_inits(q, p, g, x, y, X, Y, xx, yy, 0);
  if ((fp = fopen("parametrs.txt", "r")) == NULL)
    printf("Failed open file\n");
  gmp_fscanf(fp, "%Zx %Zx %Zx", q, p, g);
  fclose(fp);
  gmp_printf("q = %Zx\n\np = %Zx\n\ng = %Zx\n\n", q, p, g);
  // mpz_set(x, q);
  // mpz_set(y, q);
  mpz_urandomm(x, state, q);
  mpz_urandomm(y, state, q);
  while (mpz_cmp(x, q) > -1) {
    mpz_sub_ui(x, x, 5);
  }
  while (mpz_cmp(y, q) > -1) {
    mpz_sub_ui(y, y, 10);
  }
  mpz_powm(X, g, x, q);
  mpz_powm(Y, g, y, q);
  mpz_powm(xx, Y, x, q);
  mpz_powm(yy, X, y, q);
  gmp_printf("x = %Zx\n\n", x);
  gmp_printf("y = %Zx\n\n", y);
  gmp_printf("X = %Zx\n\n", X);
  gmp_printf("Y = %Zx\n\n", Y);
  gmp_printf("Xx = %Zx\n\n", xx);
  gmp_printf("Yy = %Zx\n\n", yy);
  return 0;
}
