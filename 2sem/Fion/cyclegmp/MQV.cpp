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
  mpz_t q, p, g, a, b, l, A, B, AA, BB, X, Y, XX, YY, x, y, d, dd, e, ee, Sa,
      Sb, tt, uu, t, u;
  mpz_inits(q, p, g, a, b, l, A, B, AA, BB, X, Y, XX, YY, x, y, d, dd, e, ee,
            Sa, Sb, tt, uu, t, u, 0);

  if ((fp = fopen("parametrs.txt", "r")) == NULL)
    printf("Failed open file\n");
  gmp_fscanf(fp, "%Zx %Zx %Zx", q, p, g);
  fclose(fp);
  gmp_printf("q = %Zx\n\np = %Zx\n\ng = %Zx\n\n", q, p, g);

  mpz_urandomm(a, state, q);
  mpz_urandomm(b, state, q);

  while (mpz_cmp(a, q) > -1) {
    mpz_sub_ui(a, a, 5);
  }
  while (mpz_cmp(b, q) > -1) {
    mpz_sub_ui(b, b, 10);
  }
  gmp_printf("a = %Zx\n\nb = %Zx\n\n", a, b);

  mpz_urandomm(x, state, q);
  mpz_urandomm(y, state, q);

  while (mpz_cmp(x, q) > -1) {
    mpz_sub_ui(x, x, 5);
  }
  while (mpz_cmp(y, q) > -1) {
    mpz_sub_ui(y, y, 10);
  }
  gmp_printf("x = %Zx\n\ny = %Zx\n\n", x, y);

  mpz_powm(A, g, a, p);
  mpz_powm(B, g, b, p);
  gmp_printf("A = %Zx\n\nB = %Zx\n\n", A, B);

  mpz_powm(X, g, x, p);
  mpz_powm(Y, g, y, p);
  gmp_printf("X = %Zx\n\nY = %Zx\n\n", X, Y);

  //Создание переменных d и e
  mpz_ui_pow_ui(l, 2, 128);
  mpz_powm_ui(d, X, 1, l);
  mpz_powm_ui(e, Y, 1, l);
  mpz_setbit(d, 128);
  mpz_setbit(e, 128);
  gmp_printf("d = %Zx\n\ne = %Zx\n\n", d, e);

  //Создание переменных Sa и Sb
  mpz_powm(BB, B, e, p);
  mpz_powm(AA, A, d, p);
  mpz_mul(YY, Y, BB);
  mpz_mul(XX, X, AA);
  mpz_mod(YY, YY, p);
  mpz_mod(XX, XX, p);
  gmp_printf("YB = %Zx\n\nXA = %Zx\n\n", YY, XX);

  mpz_set(t, x);
  mpz_set(u, y);
  mpz_addmul(t, d, a);
  mpz_addmul(u, e, b);
  mpz_mod(t, t, q);
  mpz_mod(u, u, q);
  gmp_printf("x+da = %Zx\n\ny+eb = %Zx\n\n", t, u);

  mpz_powm(Sa, YY, t, p);
  mpz_powm(Sb, XX, u, p);
  gmp_printf("Sa = %Zx\n\nSb = %Zx\n\n", Sa, Sb);

  return 0;
}
