#ifndef _JANUS_SCTP_H
#define _JANUS_SCTP_H
#ifdef HAVE_SCTP
#define INET 1
#define INET6 1

/* Uncomment the line below to enable SCTP debugging to files */
//~ #define DEBUG_SCTP

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <unistd.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <usrsctp.h>
#include <glib.h>

#include "mutex.h"


int janus_sctp_init(void);

void janus_sctp_deinit(void);


#define BUFFER_SIZE (1<<16)
#define NUMBER_OF_CHANNELS (100)
#define NUMBER_OF_STREAMS (16)

#define DATA_CHANNEL_PPID_CONTROL 50
#define DATA_CHANNEL_PPID_DOMSTRING 51
#define DATA_CHANNEL_PPID_BINARY_PARTIAL 52
#define DATA_CHANNEL_PPID_BINARY 53
#define DATA_CHANNEL_PPID_DOMSTRING_PARTIAL 54

#define DATA_CHANNEL_CLOSED 0
#define DATA_CHANNEL_CONNECTING 1
#define DATA_CHANNEL_OPEN 2
#define DATA_CHANNEL_CLOSING 3

#define DATA_CHANNEL_FLAGS_SEND_REQ 0x00000001
#define DATA_CHANNEL_FLAGS_SEND_RSP 0x00000002
#define DATA_CHANNEL_FLAGS_SEND_ACK 0x00000004

typedef struct janus_sctp_channel {
uint32_t id;
uint32_t pr_value;
uint16_t pr_policy;
uint16_t stream;
uint8_t unordered;
uint8_t state;
uint32_t flags;
} janus_sctp_channel;

typedef struct janus_sctp_association {
 void *dtls;
 uint64_t handle_id;
 struct janus_sctp_channel channels[NUMBER_OF_CHANNELS];
 struct janus_sctp_channel *stream_channel[NUMBER_OF_STREAMS];
 uint16_t stream_buffer[NUMBER_OF_STREAMS];
 uint32_t stream_buffer_counter;
 struct socket *sock;
 uint16_t local_port;
 uint16_t remote_port;
 GAsyncQueue *messages;
 GThread *thread;
#ifdef DEBUG_SCTP
 FILE *debug_dump;
#endif

 janus_mutex mutex;
} janus_sctp_association;

typedef struct janus_sctp_message {
gboolean incoming;
 char *buffer;
 size_t length;
} janus_sctp_message;

#define DATA_CHANNEL_OPEN_REQUEST 3 /* FIXME was 0, but should be 3 as per http://tools.ietf.org/html/draft-ietf-rtcweb-data-protocol-05 */
#define DATA_CHANNEL_OPEN_RESPONSE 1
#define DATA_CHANNEL_ACK 2

#define DATA_CHANNEL_RELIABLE 0x00
#define DATA_CHANNEL_RELIABLE_UNORDERED 0x80
#define DATA_CHANNEL_PARTIAL_RELIABLE_REXMIT 0x01
#define DATA_CHANNEL_PARTIAL_RELIABLE_REXMIT_UNORDERED 0x81
#define DATA_CHANNEL_PARTIAL_RELIABLE_TIMED 0x02
#define DATA_CHANNEL_PARTIAL_RELIABLE_TIMED_UNORDERED 0x82

/* http://tools.ietf.org/html/draft-ietf-rtcweb-data-protocol-05 */
typedef struct janus_datachannel_open_request {
 uint8_t msg_type;
 uint8_t channel_type;
 uint16_t priority;
 uint32_t reliability_params;
 uint16_t label_length;
 uint16_t protocol_length;
 char label[0];
 /* We ignore the Protocol field */
} janus_datachannel_open_request;

typedef struct janus_datachannel_open_response {
 uint8_t msg_type;
 uint8_t error;
 uint16_t flags;
 uint16_t reverse_stream;
} janus_datachannel_open_response;

typedef struct janus_datachannel_ack {
 uint8_t msg_type;
} janus_datachannel_ack;



janus_sctp_association *janus_sctp_association_create(void *dtls, uint64_t handle_id, uint16_t udp_port);

int janus_sctp_association_setup(janus_sctp_association *sctp);

void janus_sctp_association_destroy(janus_sctp_association *sctp);

void janus_sctp_data_from_dtls(janus_sctp_association *sctp, char *buf, int len);

void janus_sctp_send_data(janus_sctp_association *sctp, char *buf, int len);
#endif

#endif
