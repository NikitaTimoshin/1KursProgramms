#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char const*argv[])
{
//рандом задае
        srand(time(NULL));

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

//заполнение матриц
        FILE *w_file = fopen("matrix.txt","w");
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
            // Запись созданных рандомных матриц в файл
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                fprintf(w_file, "%i", A[i][j]);
            }
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < P; j++) {
                fprintf(w_file, "%i", B[i][j]);
            }
        }
        fclose(w_file);
        for (int i = 0; i < M; i++){
        	free(A[i]);
    	}

    	for (int i = 0; i < N; i++){
        	free(B[i]);
        }

    		free(A);
    		free(B);
	return 0;
}
