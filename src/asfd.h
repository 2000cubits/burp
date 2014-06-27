#ifndef _ASFD_H
#define _ASFD_H

#include "ssl.h"

// Return values for simple_loop().
enum asl_ret
{
	ASL_END_ERROR=-1,
	ASL_CONTINUE=0,
	ASL_END_OK=1,
	ASL_END_OK_RETURN_1=2
};

struct asfd
{
	int fd;
	SSL *ssl;
	struct async *as;
	char *desc;

	int network_timeout;
	int max_network_timeout;

	float ratelimit;
	time_t rlstart;
	int rlsleeptime;
	unsigned long long rlbytes;

	struct iobuf *rbuf;

	int doread;
	char *readbuf;
	size_t readbuflen;
	int read_blocked_on_write;

	int dowrite;
	char *writebuf;
	size_t writebuflen;
	int write_blocked_on_read;

	struct asfd *next;

	// Stuff for the champ chooser server.
	struct incoming *in;
	struct blist *blist;
	int blkcnt;
	uint64_t wrap_up;
	uint8_t want_to_remove;
	// For the champ chooser server main socket.
	uint8_t listening_for_new_clients;
	uint8_t new_client;

	// Function pointers.
	int (*init)(struct asfd *, const char *,
		struct async *, int, SSL *, struct conf *);
	int (*parse_readbuf)(struct asfd *);
	int (*append_all_to_write_buffer)(struct asfd *, struct iobuf *);
	int (*set_bulk_packets)(struct asfd *);
	int (*do_read)(struct asfd *);
	int (*do_read_ssl)(struct asfd *);
	int (*do_write)(struct asfd *);
	int (*do_write_ssl)(struct asfd *);
	int (*read)(struct asfd *);
	int (*read_expect)(struct asfd *, char, const char *);
	int (*simple_loop)(struct asfd *, struct conf *, void *,
		const char *, enum asl_ret callback(struct asfd *,
			struct conf *, void *));
	int (*write)(struct asfd *, struct iobuf *);
	int (*write_str)(struct asfd *, char, const char *);
	int (*write_strn)(struct asfd *, char, const char *, size_t);
};

extern struct asfd *asfd_alloc(void);
extern void asfd_close(struct asfd *asfd); // Maybe should be in the struct.
extern void asfd_free(struct asfd **asfd);

#endif