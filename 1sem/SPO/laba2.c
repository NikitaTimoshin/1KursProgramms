#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <inttypes.h>
#include <stdint.h>
#include <inttypes.h>

uint64_t get_time(){
uint32_t low, high;
__asm__ __volatile__("rdtsc\n" : "=a" (low), "=d" (high) );
return ((uint64_t)high << 32) | low;
}

int main(int argc, char const*argv[])
{
//задаем переменные
	    int M = atoi(argv[1]);
	    int N = atoi(argv[2]);
        int P = atoi(argv[3]);

//выделяем память
	    int **A = (int **)malloc(M * sizeof(int *));
        for (int i = 0; i < M; i++) {
        	A[i] = (int *)malloc(N * sizeof(int));
        }
        int **B = (int **)malloc(N * sizeof(int *));
        for (int i = 0; i < N; i++) {
        	B[i] = (int *)malloc(P * sizeof(int));
    	}
        int **C = (int **)malloc(M * sizeof(int *));
        for (int i = 0; i < M; i++) {
        	C[i] = (int *)malloc(P * sizeof(int));
        }
        //заполнение матриц
        for (int i = 0; i < M; i++){
    	    for (int j = 0; j < N; j++){
    	        A[i][j] = rand() % 10 + 1;
    	    }
    	}
        for (int i = 0; i < N; i++){
        	for (int j = 0; j < P; j++){
            		B[i][j] = rand() % 10 + 1;
        	}
        }

        uint64_t t = get_time();
                int result = 0;
        for (int i = 0; i < M; i++) {
        	for (int j = 0; j < P; j++) {
                C[i][j]=0;
        		for (int k = 0; k < M; k++)
                		C[i][j] += A[i][k] * B[k][j];
            		}
        }
        uint64_t t1 = get_time();
        printf("%"PRId64"\n", (t1-t));
  return 0;
}
