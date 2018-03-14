#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <gmp.h>
#include <unistd.h>
#include <rdtsc.h>

const int ModLen = 128;

int main()
  {
    FILE *f;
    char buf [ModLen];
    unsigned int t1, t2, cps;
    cps=0;
    t1=0;
    mpz_t q, p, g, t;
    mpz_inits (q, p, g, t, 0);
    mpz_set_ui (g,2);
    sleep(1);
    srand (time(0));

    while(cps==0)
  {
        for (int i = 0; i < ModLen; i++) buf[i] = rand();
    buf[0] &= 0x7f;
    buf[0] |= 0x40;
    mpz_import (q, ModLen, 1, 1, 0, 0, buf);
    //gmp_printf ("x = %Zx\n", x);
    printf("Popitka #%d",t1);
    printf ("\n\n");
    mpz_nextprime(q,q);
    mpz_mul_ui (p,q,2);
    mpz_add_ui (p,p,1);
    cps=mpz_probab_prime_p (p,50);
    t1++;
  }
  printf ("\n\n");
  gmp_printf ("q = %Zx\n", q);
  printf ("\n\n");
  gmp_printf ("p = %Zx\n", p);
  printf ("\n\n");
  printf("cps=%d",cps);
  printf ("\n");
    while(mpz_cmp_ui(t,1)==0)
  {
    mpz_powm(t,g,q,p);
    printf ("Popitka #%d",t2);
    if (mpz_cmp_ui(t,1)==0) { mpz_add_ui (g,g,1); }
    t2++;
  }
  gmp_printf ("TestG = %Zx\n", t);
  gmp_printf ("g = %Zx\n", g);

  if ((f = fopen("parametrs.txt","w")) == NULL)
     printf("Файл невозможно открыть или создать\n");
  else
  {
    gmp_fprintf (f,"%Zx %Zx %Zx",q,p,g);
  }
  fclose(f);

  return 0;
}
