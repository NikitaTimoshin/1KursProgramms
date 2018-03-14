#include <gmp.h>
#include <rdtsc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

const int ModLenq = 32;
const int ModLenb = 96;

int main() {
  FILE *file;
  char bufq[ModLenq];
  char bufb[ModLenb];
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
    for (int i = 0; i < ModLenq; i++)
      bufq[i] = rand();
    for (int i = 0; i < ModLenb; i++)
      bufb[i] = rand();
    bufq[0] &= 0x80;
    bufb[0] |= 0x80;
    mpz_import(b, ModLenb, 1, 1, 0, 0, bufb);
    mpz_import(q, ModLenq, 1, 1, 0, 0, bufq);
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
  gmp_printf("b = %Zx\n", b);
  printf("\n\n");
  gmp_printf("p = %Zx\n", p);
  printf("\n\n");
  printf("cps=%d", cps);
  printf("\n");

  while (mpz_cmp_ui(t, 1) != 0) {
    if (mpz_cmp_ui(t, 1) != 0) {
      mpz_set_ui(g, 0);
    }
    while (mpz_cmp_ui(g, 1) != 1) {
      mpz_powm(g, f, b, p);
      printf("f poisk Popitka #%d", t2);
      printf("\n\n");
      if (mpz_cmp_ui(g, 1) != 1) {
        mpz_add_ui(f, f, 1);
      }
      t2++;
    }
    printf("g poisk Popitka #%d", t3);
    printf("\n\n");
    mpz_powm(t, g, q, p);
    t3++;
  }
  gmp_printf("f = %Zx\n\n", f);
  gmp_printf("g = %Zx\n", g);


  if ((file = fopen("parametrs.txt", "w")) == NULL)
    printf("Файл невозможно открыть или создать\n");
  else {
    gmp_fprintf(file, "%Zx %Zx %Zx", q, p, g);
  }
  fclose(file);

  return 0;
}
