#include <stdlib.h>
#include <stdio.h>

void truncation (int result_rank, int result_transfer[], int result_truncation[]){
int i;
int y;
  for (i = 32 - result_rank, y = 0; i < 31; i++, y++) {
    result_truncation[y] = result_transfer[i];
  }
}

void transfer (int number, int transfer[]){

  int buffer = 1073741824;
	int i;
  for (i = 0; i < 31; i++) {
    if ((buffer & number) == 0) {
      transfer[i] = 0;
    }else{
      transfer[i] = 1;
    }
    buffer = buffer >> 1;
  }
}

int number(char code, int size, char* alphabet) {

  int result;
int i;
  for (i = 0; i < size; i++) {
    if (code == alphabet[i]) {
      result = i;
      break;
    }
  }
  return result;
}

int rank (int result_transfer[]){

  int count = 0;
int i;
  for (i = 0; i < 31; i++) {
    if (result_transfer[i] == 1) {
      count = 31 - i;
      break;
    }
  }
  return count;
}

void new_alphabet(char code, int size, char* alphabet) {

  char buffer[26];
int i;
int j;
int z;
  for (i = 0, j = 1; i < size; i++) {
    if (alphabet[i] != code) {
      buffer[j] = alphabet[i];
      j++;
    }
  }
  buffer[0] = code;

  for (z = 0; z < size; z++) {
  alphabet[z] = buffer[z];
  }
}

void f0 (int number){
int i;
  FILE *out_file = fopen("out.txt", "a");

  if (number == 0) {
    fprintf(out_file, "%s", "1");
  } else {
    for (i = 0; i < number; i++) {
      fprintf(out_file, "%s", "0");
    }
    fprintf(out_file, "%s", "1");
  }
    fclose(out_file);
}

void f1 (int result_rank, int result_truncation[]) {
int i;
int y;
  FILE *out_file = fopen("out.txt", "a");

  f0(result_rank);
  for (i = result_rank + 1, y = 0; i < 2 * result_rank; i++, y++) {
    fprintf(out_file, "%i", result_truncation[y]);
  }
  fclose(out_file);
}

void f2(int result_rank_old, int result_truncation_old[]){

  FILE *out_file = fopen("out.txt", "a");

  int number;
  int result_transfer[31];
  int result_rank;
  int result_truncation[31];
  int buffer[10000];
int i;
  number = result_rank_old;
  transfer(number, result_transfer);
  result_rank = rank(result_transfer);
  truncation(result_rank,result_transfer,result_truncation);
  f1(result_rank, result_truncation);
  for (i = 0; i < result_rank_old - 1; i++) {
    fprintf(out_file, "%i", result_truncation_old[i]);
  }
  fclose(out_file);
}

int main(int argc, char const *argv[]) {

  int number_for_lab1;
  int result_rank;
  int result_transfer[31];
  int result_truncation[31];
  int type_code = atoi(argv[1]);
  char file_read_buffer[2];
  char alphabet[26];
  char *check;
  int i;
  FILE *in_file = fopen("in.txt", "r");

  for (i = 0; i < sizeof(alphabet); i++) {
    alphabet[i] = 97+i;
  }
  /*for (int l = 0; l < sizeof(alphabet); l++) {
    printf(" %c ", alphabet[l]);
  }*/
 while (1) {
    check = fgets(file_read_buffer,2,in_file);
    if (check == NULL){
      break;
    }
    if (file_read_buffer[0] == '\n') {
      continue;
    }
    // sizeof(alphabet)
    number_for_lab1 = number(file_read_buffer[0],sizeof(alphabet),alphabet);
    new_alphabet(file_read_buffer[0],26,alphabet);
    transfer(number_for_lab1, result_transfer);
    result_rank = rank(result_transfer);
    truncation(result_rank, result_transfer, result_truncation);
    switch (type_code) {
      case 0:
      f0(number_for_lab1);
      break;
      case 1:
      f1(result_rank, result_truncation);
      break;
      case 2:
      f2(result_rank, result_truncation);
    }
  }
  fclose(in_file);
  return 0;
}
