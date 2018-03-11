#include <gmp.h>
#include <rdtsc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const int ModLen = 128;

int main() {
  FILE *file;
  char buf[ModLen];
  unsigned int t1, t2, t3, cps;
  cps = 0;
  t1 = 0;
  t2 = 0;
  t3 = 0;
  mpz_t q, p, g, t, b, f;
  mpz_inits(q, p, g, t, b, f, 0);
  mpz_set_ui(f, 2);
  sleep(1);
  srand(time(0));

  while (cps == 0) {
    for (int i = 0; i < ModLen; i++)
      buf[i] = rand();
    mpz_import(b, ModLen, 1, 1, 0, 0, buf);
    buf[0] &= 0x7f;
    buf[0] |= 0x40;
    mpz_import(q, ModLen, 1, 1, 0, 0, buf);
    // gmp_printf ("x = %Zx\n", x);
    printf("Popitka #%d", t1);
    printf("\n\n");
    mpz_nextprime(q, q);
    mpz_mul(p, q, b);
    mpz_add_ui(p, p, 1);
    cps = mpz_probab_prime_p(p, 50);
    t1++;
  }
  printf("\n\n");
  gmp_printf("q = %Zx\n", q);
  printf("\n\n");
  gmp_printf("p = %Zx\n", p);
  printf("\n\n");
  gmp_printf("b = %Zx\n", b);
  printf("\n\n");
  printf("cps=%d", cps);
  printf("\n");

  while (mpz_cmp_ui(t, 1) != 0) {
    if (mpz_cmp_ui(t, 1) != 0) {
      mpz_set_ui(g, 0);
    }
    while (mpz_cmp_ui(g, 1) != 1) {
      mpz_powm(g, f, b, p);
      printf("G poisk Popitka #%d", t2);
      printf("\n\n");
      if (mpz_cmp_ui(g, 1) != 1) {
        mpz_add_ui(f, f, 1);
      }
      t2++;
    }
    printf("T poisk Popitka #%d", t3);
    printf("\n\n");
    mpz_powm(t, g, q, p);
    t3++;
  }
  gmp_printf("TestG = %Zx\n", t);
  gmp_printf("g = %Zx\n", g);
  gmp_printf("f = %Zx\n", f);

  if ((file = fopen("parametrs.txt", "w")) == NULL)
    printf("Файл невозможно открыть или создать\n");
  else {
    gmp_fprintf(file, "q = %Zx p = %Zx g = %Zx", q, p, g);
  }
  fclose(file);

  return 0;
}
