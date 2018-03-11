#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main(int argc, char const *argv[])
{
int i=0;
int j=0;
int k=0;
   srand (time(NULL));
   //Создание потока для записи результата в файл
   FILE *out_file = fopen("output.txt", "a");
  // Создание первой рандомной матрицы
  int **array = (int **) malloc(atoi(argv[1]) * sizeof(int *));
  for (i = 0; i < atoi(argv[1]); i++){
    array[i] = (int *) malloc(atoi(argv[2]) * sizeof(int));
  }
  for (i = 0; i < atoi(argv[1]); i++) {
    array[i][j] = rand() % 10;
    }
  }

//Создание второй рандомной матрицы
  int **array2 = (int **) malloc(atoi(argv[2]) * sizeof(int *));
  for (i = 0; i < atoi(argv[2]); i++){
    array2[i] = (int *) malloc(atoi(argv[3]) * sizeof(int));
  }
  //Создание третьей матрицы для записи результата перемножения двух матриц
   int **array3 = (int **) malloc(atoi(argv[1]) * sizeof(int *));
   for (i = 0; i < atoi(argv[1]); i++){
     array3[i] = (int *) malloc(atoi(argv[3]) * sizeof(int));
     //Перемножение двух первых матриц
      int result = 0;
      for (j = 0; j < atoi(argv[3]); j++) {
        for (i = 0; i < atoi(argv[1]); i++) {
          for (k = 0; k < atoi(argv[2]); k++) {
            result = result + array[i][k] * array2[k][j];
          }
          array3[i][j] = result;
        }
       }

       //Вывод результата работы

       printf("\nПроизведение двух матриц размерносью %i на %i", atoi(argv[1]), atoi$
       for (i = 0; i < atoi(argv[1]); i++) {
         printf("\n");
         for (j = 0; j < atoi(argv[3]); j++) {
           if (j != 0){
               printf(" ");
             }
             printf("%i", array3[i][j]);
           }
         }

         return 0;
       }
