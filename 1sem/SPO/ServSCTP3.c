#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <netinet/sctp.h>
#include <memory.h>
#include <stdarg.h>
#include <stdarg.h>
#include <syslog.h>

#define MAX_BUFFER  1024

void die(char *s)
{
      perror(s);
      exit(1);
}

int main()
{
    int sfd, cfd, i, flags;
    struct sctp_sndrcvinfo sndrcvinfo;
    struct sockaddr_in saddr;
    struct sctp_initmsg initmsg;
    //char buff[INET_ADDRSTRLEN];
    char buffer[MAX_BUFFER+1];

    sfd = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );

    bzero( (void *)&saddr, sizeof(saddr) );
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = 0;

    bind(sfd, (struct sockaddr *)&saddr, sizeof(saddr) );

    int addrLenght = sizeof(saddr);
    if (getsockname(sfd, (struct sockaddr *) &saddr, (socklen_t *) &addrLenght)) {
    perror("Вызов getsockname неудачен\n");
    }
    printf("SERVER: номер порта сервера %i\n\n", ntohs(saddr.sin_port));

/* Не более трех потоков для каждого сокета */
    memset( &initmsg, 0, sizeof(initmsg) );
    initmsg.sinit_num_ostreams = 2;
    initmsg.sinit_max_instreams = 2;
    initmsg.sinit_max_attempts = 1;
    setsockopt( sfd, IPPROTO_SCTP, SCTP_INITMSG, &initmsg, sizeof(initmsg) );

    listen(sfd, 5);

    printf("Сервер запущен\n");

    cfd = accept(sfd, 0, 0);
    if (cfd == -1)
    die("accept()");
    else
    printf("Клиент уже здесь\n");
    for (i = 0; i < 2; i++){
    int z;
    if((z = sctp_recvmsg(cfd, (void *)buffer, sizeof(buffer), 0, 0, &sndrcvinfo, &flags )) == -1)
    printf("%s\n", "Ошибка");
    else{
      printf("Полученное сообщение с потока: %s\n",buffer);
      memset(buffer, 0, sizeof(buffer));
    }

  }
  close(cfd);
return 0;
}
