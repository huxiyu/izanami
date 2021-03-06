/*
 * networkserver.h
 *
 *  Created on: 2018年8月11日
 *      Author: caojx
 */

#ifndef SRC_NETWORKSERVER_H_
#define SRC_NETWORKSERVER_H_

#include "common.h"
#include "executor.h"

#include <netinet/in.h>
#include <sys/epoll.h>

typedef void (*onconnect)(struct networkserver *server,
		struct epoll_event *event, struct sockaddr_in *addr);

struct networkserver {

	int port;
	const char *eth;
	int maxconn;
	int serversock;
	struct sockaddr_in server_addr;
	onconnect connfun;

	int epollfd;
	struct epoll_event server, *requests;
	struct executor *executor;
	pthread_t serverthread;
};

//确定端口、最大连接数、executor
typedef void (*networkserverconfig)(struct networkserver *server);
struct networkserver *initnetworkserver(networkserverconfig config);

#endif /* SRC_NETWORKSERVER_H_ */
