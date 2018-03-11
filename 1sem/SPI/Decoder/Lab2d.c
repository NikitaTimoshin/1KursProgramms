#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

void symbol(int number, int size, char* alphabet) {

  FILE *out_file = fopen("out.txt", "a");

  fprintf(out_file, "%c", alphabet[number]);
    fclose(out_file);
}

int transfer(int buffer[], int buf) {

  int result = 0;
int i;
   for (i = buf-1; i >= 0; i--) {
    result = result + buffer[i] * pow(2,buf-1-i);
  }
  return result;
}

void new_alphabet(int number, int size, char* alphabet) {
  char buffer[size];
  int i;
  int j;
  buffer[0] = alphabet[number];
  for (i = 0, j = 1; i < size; i++) {
    if (i != number) {
      buffer[j] = alphabet[i];
      j++;
    }
  }
  for (i = 0; i < size; i++) {
    alphabet[i] = buffer[i];
  }
}

void f0() {

  char buffer[2];
  char alphabet[5];
  char *check;
  int i;
  int count = 0;
  FILE *in_file = fopen("in.txt", "r");

  for (i = 0; i < sizeof(alphabet); i++) {
    alphabet[i] = 97+i;
  }
  while (1) {
    check = fgets(buffer,2,in_file);
    if (check == NULL){
      break;
    }
    switch (buffer[0]) {
      case '\n':
      continue;
      case '0':
      count++;
      break;
      default:
      symbol(count,sizeof(alphabet),alphabet);
      new_alphabet(count,sizeof(alphabet),alphabet);
      count = 0;
      break;
    }
  }
  fclose(in_file);
}

void f1() {


  char retrieve_buffer[2];
  char alphabet[26];
  char *check;
  int buffer[100];
  int size;
  int number;
  int count = 0;
  int i;
  FILE *in_file = fopen("in.txt", "r");

  for (i = 0; i < sizeof(alphabet); i++) {
    alphabet[i] = 97+i;
  }
  while (1) {
    check = fgets(retrieve_buffer,2,in_file);
    if (check == NULL){
      break;
    }
    if (retrieve_buffer[0] == '\n') {
      continue;
    }
    if (count > -1) {
      switch (retrieve_buffer[0]) {
        case '0':
        count++;
        break;
        case '1':
        if (count == 0) {  // ?????????? ??? 0
          count = -1;
          size = -1;
          break;
        }
        count = -count;
        size = 0;
        break;
      }
    }
    if (count < 0) {
      buffer[size] = atoi(retrieve_buffer);
      count++;
      size++;
      if (count == 0) {
        if (size == 0) { // ?????????? ??? 0
          number = 0;
        } else{
          number = transfer(buffer, size);
        }
        printf("%i ",  number);
        symbol(number,sizeof(alphabet),alphabet);
        new_alphabet(number,sizeof(alphabet),alphabet);
      }
    }
  }
  fclose(in_file);
}

void f2() {

  char retrieve_buffer[2];
  char alphabet[5];
  char *check;
  int buffer[100];
  int size;
  int number;
  int count = 0;
  int exception = 0;
  int i;
  FILE *in_file = fopen("in.txt", "r");

  for (i = 0; i < sizeof(alphabet); i++) {
    alphabet[i] = 97+i;
  }
  while (1) {
    check = fgets(retrieve_buffer,2,in_file);
    if (check == NULL){
      break;
    }
    if (retrieve_buffer[0] == '\n') {
      continue;
    }
    if (count > -1) {
      switch (retrieve_buffer[0]) {
        case '0':
        count++;
        break;
        case '1':
        count = -count;
        size = 0;
        buffer[size] = atoi(retrieve_buffer);
        switch (count) {
          case 0:
          exception = -1; // ?????????? ??? ???? 1
          break;
          case -1:
          exception = -2; // ?????????? ??? ???? 01
          break;
        }
        if (exception == 0){
          for (i = 0; i < -count; i++) {
            fgets(retrieve_buffer,2,in_file);
            if ((i == 0) & (retrieve_buffer[0] == '0') & (-count == 2)) {
              exception = -3; // ?????????? ??? ???? 00100 ? 00101
            }
          }
        }
        break;
      }
    }
    if ((count < 0) | (exception == -1)) {
      switch (exception) {
        case 0:
        size++;
        buffer[size] = atoi(retrieve_buffer);
        count++;
        if (count == 0) {
          size++;
          number = transfer(buffer, size);
          symbol(number,sizeof(alphabet),alphabet);
          new_alphabet(number,sizeof(alphabet),alphabet);
        }
        break;
        case -1:
        size = 1;
        count = 0;
        exception = 0;
        buffer[0] = 0;
        number = transfer(buffer, size);
        symbol(number,sizeof(alphabet),alphabet);
        new_alphabet(number,sizeof(alphabet),alphabet);
        break;
        case -2:
        size = 1;
        count = 0;
        exception = 0;
        number = transfer(buffer, size);
        symbol(number,sizeof(alphabet),alphabet);
        new_alphabet(number,sizeof(alphabet),alphabet);
        break;
        case -3:
        buffer[1] = atoi(retrieve_buffer);
        size = 2;
        count = 0;
        exception = 0;
        number = transfer(buffer, size);
        symbol(number,sizeof(alphabet),alphabet);
        new_alphabet(number,sizeof(alphabet),alphabet);
        break;
      }
    }
  }
  fclose(in_file);
}

int main(int argc, char const *argv[]) {

  int type_code = atoi(argv[1]);
  type_code=1;

  switch (type_code) {
    case 0:
    f0();
    break;
    case 1:
    f1();
    break;
    case 2:
    f2();
    break;
  }

  return 0;
}
