#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, char const *argv[]) {

  int i, maxI, msgLength, maxCountSock, sockMain, sockClient, sockCheck, sockReady, client[FD_SETSIZE];
  fd_set rset, allset;
  char msgClient[81];
  struct sockaddr_in servAddr;


  if ((sockMain = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Сервер не может открыть главный socket.\n");
    exit(1);
  }
  servAddr.sin_family = AF_INET;
  servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servAddr.sin_port = 0;
  if (bind(sockMain, (struct sockaddr *) &servAddr, sizeof(servAddr))) {
    perror("Связывание сервера неудачно\n");
    exit(1);
  }
  int lenght = sizeof(servAddr);
  if (getsockname(sockMain, (struct sockaddr *) &servAddr, (socklen_t *) &lenght)) {
    perror("Вызов getsockname неудачен.\n");
    exit(1);
  }
  printf("СЕРВЕР: Номер порта сервера %i\n\n", ntohs(servAddr.sin_port));
  listen(sockMain, 5);
  maxCountSock = sockMain;
  maxI = -1;
  for (int i = 0; i < FD_SETSIZE; i++) {
    client[i] = -1;
  }
  FD_ZERO(&allset);
  FD_SET(sockMain, &allset);
  while (1) {
    rset = allset;
    sockReady = select(maxCountSock + 1, &rset, NULL, NULL, NULL);
    if (FD_ISSET(sockMain, &rset)) {
      printf("Пришел новый запрос на соединение.\n");
      sockClient = accept(sockMain, 0, 0);
      for (i = 0; i < FD_SETSIZE; i++) {
      if (client[i] < 0) {
        client[i] = sockClient;
        printf("Дискриптор нового сокета %i\n", client[i]);
        break;
      }
    }
    FD_SET(sockClient, &allset);
    if (sockClient > maxCountSock) {
      maxCountSock = sockClient;
    }
    if (i > maxI) {
      maxI = i;
    }
    if (--sockReady <= 0) {
      continue;
    }
  }
  for (int i = 0; i <= maxI; i++) {
    if ((sockCheck = client[i]) < 0) {
      continue;
    }
    if (FD_ISSET(sockCheck, &rset)) {
      if((msgLength = recv(sockCheck, msgClient, 81, 0)) <= 0){
        printf("SERVER: Клиент закончил передачу.\n");
        close(sockCheck);
        FD_CLR(sockCheck, &allset);
        client[i] = -1;
      }else{
        printf("SERVER: сообщение от клиента %s\n", msgClient);
        memset(msgClient, 0, sizeof(msgClient));
      }
      if (--sockReady <= 0) {
        break;
        }
      }
    }
  }
  return 0;
}
