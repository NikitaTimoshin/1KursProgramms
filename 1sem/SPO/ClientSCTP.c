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

#define SERV_PORT  5134
#define MAXNAME    1024
#define LISTENQ 1024
#define MAX_BUFFER  1024
#define SA struct sockaddr
#define	MAXLINE	4096
#define	BUFFSIZE	8192
#define	SCTP_MAXLINE	800

int daemon_proc;
int SERV_MAX_SCTP_STRM=10;

void
sctpstr_cli_echoall(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen)
{
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char sendline[SCTP_MAXLINE], recvline[SCTP_MAXLINE];
	socklen_t len;
	int rd_sz,i,strsz;
	int msg_flags;

	bzero(sendline,sizeof(sendline));
	bzero(&sri,sizeof(sri));
	while (fgets(sendline, SCTP_MAXLINE - 9, fp) != NULL) {
		strsz = strlen(sendline);
		if(sendline[strsz-1] == '\n') {
			sendline[strsz-1] = '\0';
			strsz--;
		}
		for(i=0;i<SERV_MAX_SCTP_STRM;i++) {
			snprintf(sendline + strsz, sizeof(sendline) - strsz,
				".msg.%d", i);
			sctp_sendmsg(sock_fd, sendline, sizeof(sendline),
				     to, tolen,
				     0, 0,
				     i,
				     0, 0);
		}
		for(i=0;i<SERV_MAX_SCTP_STRM;i++) {
			len = sizeof(peeraddr);
			rd_sz = sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
				     (SA *)&peeraddr, &len,
				     &sri,&msg_flags);
			printf("From str:%d seq:%d (assoc:0x%x):",
				sri.sinfo_stream,sri.sinfo_ssn,
				(u_int)sri.sinfo_assoc_id);
			printf("%.*s\n",rd_sz,recvline);
		}
	}
}

void
sctpstr_cli(FILE *fp, int sock_fd, struct sockaddr *to, socklen_t tolen)
{
	struct sockaddr_in peeraddr;
	struct sctp_sndrcvinfo sri;
	char sendline[MAXLINE], recvline[MAXLINE];
	socklen_t len;
	int out_sz,rd_sz;
	int msg_flags;

	bzero(&sri,sizeof(sri));
	while (fgets(sendline, MAXLINE, fp) != NULL) {
		if(sendline[0] != '[') {
			printf("Error, line must be of the form '[streamnum]text'\n");
			continue;
		}
		sri.sinfo_stream = strtol(&sendline[1],NULL,0);
		out_sz = strlen(sendline);
		sctp_sendmsg(sock_fd, sendline, out_sz,
			     to, tolen,
			     0, 0,
			     sri.sinfo_stream,
			     0, 0);

		len = sizeof(peeraddr);
		rd_sz = sctp_recvmsg(sock_fd, recvline, sizeof(recvline),
			     (SA *)&peeraddr, &len,
			     &sri,&msg_flags);
		printf("From str:%d seq:%d (assoc:0x%x):",
		       sri.sinfo_stream,sri.sinfo_ssn,
		       (u_int)sri.sinfo_assoc_id);
		printf("%.*s",rd_sz,recvline);
	}
}

static void
err_doit(int errnoflag, int level, const char *fmt, va_list ap)
{
int errno_save, n;
char buf[MAXLINE + 1];
errno_save = errno; /* значение может понадобиться вызвавшему
                   процессу */
#ifdef HAVE_VSNPRINTF
vsnprintf(buf, MAXLINE, fmt, ap); /* защищенный вариант */
#else
vsprintf(buf, fmt, ap); /* незащищенный вариант */
#endif
n = strlen(buf);
if (errnoflag)
 snprintf(buf + n, MAXLINE - n, ": %s", strerror(errno_save));
strcat(buf, "n");
if (daemon_proc) {
//syslog(level, buf);
} else {
 fflush(stdout); /* если stdout и stderr совпадают */
 fputs(buf, stderr);
 fflush(stderr);
}
return;
}

void err_quit(const char *fmt, ...)
{
va_list ap;
va_start(ap, fmt);
err_doit(0, LOG_ERR, fmt, ap);
va_end(ap);
exit(1);
}

int
main(int argc, char **argv)
{
	int sock_fd;
	struct sockaddr_in servaddr;
	struct sctp_event_subscribe evnts;
	int echo_to_all=0;

	if(argc < 2)
		err_quit("Missing host argument - use '%s host [echo]'\n",
		       argv[0]);
	if(argc > 2) {
		printf("Echoing messages to all streams\n");
		echo_to_all = 1;
	}
        sock_fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

	bzero(&evnts, sizeof(evnts));
	evnts.sctp_data_io_event = 1;
	setsockopt(sock_fd,IPPROTO_SCTP, SCTP_EVENTS,
		   &evnts, sizeof(evnts));
	if(echo_to_all == 0)
		sctpstr_cli(stdin,sock_fd,(SA *)&servaddr,sizeof(servaddr));
	else
		sctpstr_cli_echoall(stdin,sock_fd,(SA *)&servaddr,sizeof(servaddr));
	close(sock_fd);
	return(0);
}
