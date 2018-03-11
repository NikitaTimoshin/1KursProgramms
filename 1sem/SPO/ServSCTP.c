/*sctp/sctpserv01.c
#include "unp.h"*/

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
#define SERV_PORT  5134
#define MAXNAME    1024
#define LISTENQ 1024
#define MAX_BUFFER  1024
#define SA struct sockaddr

sctp_assoc_t
sctp_address_to_associd(int sock_fd, struct sockaddr *sa, socklen_t salen)
{
	struct sctp_paddrparams sp;
	int siz;

	siz = sizeof(struct sctp_paddrparams);
	bzero(&sp,siz);
	memcpy(&sp.spp_address,sa,salen);
	sctp_opt_info(sock_fd,0,
		   SCTP_PEER_ADDR_PARAMS, &sp, &siz);
	return(sp.spp_assoc_id);
}

int
sctp_get_no_strms(int sock_fd,struct sockaddr *to, socklen_t tolen)
{
	int retsz;
	struct sctp_status status;
	retsz = sizeof(status);
	bzero(&status,sizeof(status));

	status.sstat_assoc_id = sctp_address_to_associd(sock_fd,to,tolen);
	getsockopt(sock_fd,IPPROTO_SCTP, SCTP_STATUS,
		   &status, &retsz);
	return(status.sstat_outstrms);
}

int main(int argc, char **argv)
{

int sock_fd, msg_flags;
char readbuf[1000];
struct sockaddr_in servaddr, cliaddr;
struct sctp_sndrcvinfo sri;
struct sctp_event_subscribe evnts;
int stream_increment=1;

socklen_t len;
size_t rd_sz;

if (argc == 2)
stream_increment = atoi(argv[1]);

sock_fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
servaddr.sin_port = htons(SERV_PORT);
bind(sock_fd, (SA*) &servaddr, sizeof(servaddr));
bzero(&evnts, sizeof(evnts));
evnts.sctp_data_io_event = 1;
setsockopt(sock_fd, IPPROTO_SCTP, SCTP_EVENTS, &evnts, sizeof(evnts));
listen(sock_fd, LISTENQ);

for (;;)
{

len = sizeof(struct sockaddr_in);
rd_sz = sctp_recvmsg(sock_fd, readbuf, sizeof(readbuf),
(SA*)&cliaddr, &len, &sri, &msg_flags);

if (stream_increment)
{
sri.sinfo_stream++;
if (sri.sinfo_stream >= sctp_get_no_strms(sock_fd, (SA*)&cliaddr, len))
sri.sinfo_stream = 0;
}
sctp_sendmsg(sock_fd, readbuf, rd_sz, (SA*)&cliaddr, len, sri.sinfo_ppid, sri.sinfo_flags, sri.sinfo_stream, 0, 0);
}
}
