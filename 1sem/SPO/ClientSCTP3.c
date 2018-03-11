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

int main(int argc, char **argv)
{
    int cfd, i;
    struct sockaddr_in saddr;
    struct sctp_sndrcvinfo;
    struct sctp_event_subscribe events;
    struct sctp_initmsg initmsg;
    char buffer[MAX_BUFFER+1];

  /*  if(argc!=2) {
        printf("Использьзуемый: %s ip адрес\n", argv[0]);
    return -1;
  } */

    cfd = socket( AF_INET, SOCK_STREAM, IPPROTO_SCTP );

/* Для каждого сокета не более трех потоков */
    memset( &initmsg, 0, sizeof(initmsg) );
    initmsg.sinit_num_ostreams = 2;
    initmsg.sinit_max_instreams = 2;
    initmsg.sinit_max_attempts = 1;
    setsockopt( cfd, IPPROTO_SCTP, SCTP_INITMSG,
            &initmsg, sizeof(initmsg) );

    bzero( (void *)&saddr, sizeof(saddr) );
    saddr.sin_family = AF_INET;
    inet_pton(AF_INET, argv[1], &saddr.sin_addr);
    saddr.sin_port = htons(atoi(argv[2]));

    connect( cfd, (struct sockaddr *)&saddr, sizeof(saddr) );

    memset( (void *)&events, 0, sizeof(events) );
    events.sctp_data_io_event = 1;
    setsockopt(cfd, SOL_SCTP, SCTP_EVENTS,(const void *)&events, sizeof(events) );

    for(;;)
    {
    printf("Введите сообщение\n");
    fgets(buffer,MAX_BUFFER,stdin);
    for(i=0; i< 2; i++)
    {
    sctp_sendmsg(cfd, (void *)buffer, (size_t)strlen(buffer),
    NULL, 0, 0, 0, i, 0, 0 );
    printf("Отправка сообщения: %s\n", buffer);
    }
    close(cfd);
    break;
    }
    return 0;
}
