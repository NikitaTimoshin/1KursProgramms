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
        int **C = (int **)malloc(M * sizeof(int *));
        for (int i = 0; i < M; i++) {
        	C[i] = (int *)malloc(P * sizeof(int));
        }

//заполнение матриц
        
    if (argc == 5) {
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
    }
    else {
    //Чтение матриц из файла
    FILE *r_file = fopen("matrix.txt","r");
    char buffer[2];
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        fgets(buffer,2,r_file);
        if (buffer[0] == '\0') {
          fgets(buffer,2,r_file);
          printf("%s\n", buffer);
        }
        A[i][j] = atoi(buffer);
      }
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < P; j++) {
        fgets(buffer,2,r_file);
        if (buffer[0] == '\0') {
          fgets(buffer,2,r_file);
        }
        B[i][j] = atoi(buffer);
      }
    }
    fclose(r_file);
}

//перемножение матриц
        int result = 0;
        for (int j = 0; j < P; j++) {
        	for (int i = 0; i < M; i++) {
        		for (int k = 0; k < N; k++) {
                		result = result + A[i][k] * B[k][j];
            		}
            		C[i][j] = result;
            		result = 0;
        	}
        }
 
//вывод матриц   

        printf("\nПроизведение двух матриц ");
        for (int i = 0; i < M; i++) {
        	printf("\n");
        	for (int j = 0; j < P; j++) {
            		if (j != 0) {
                		printf(" ");
                	}
                	printf("%i", C[i][j]);
        	}
    	}
        printf("\n");
        for (int i = 0; i < M; i++){
        	free(A[i]);
        	free(C[i]);
    	}

    	for (int i = 0; i < N; i++){
        	free(B[i]);
        }

    		free(A);
    		free(B);
    		free(C);

	return 0;
}
