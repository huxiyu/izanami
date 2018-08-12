/*
 * networkserver.c
 *
 *  Created on: 2018年8月11日
 *      Author: caojx
 */

#include "networkserver.h"

#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>

void * startnetworkserver(void *arg) {

	struct networkserver *server = arg;

	while (TRUE) {
		int nfds = epoll_wait(server->epollfd, server->requests,
				server->maxconn, -1);

		if (nfds == -1) {
			printf("epoll wait 出错");
		}

		int i = 0;
		for (; i < nfds; i++) {

			struct epoll_event request = server->requests[i];

			if (!(request.events && EPOLLIN)) {
				continue;
			}

			if (request.data.fd == server->serversock) {

				struct sockaddr_in in_addr;
				socklen_t in_len;
				int infd;

				infd = accept(server->serversock, (struct sockaddr *) &in_addr,
						&in_len);
				struct epoll_event ev;
				ev.data.fd = infd;
				ev.events = EPOLLIN;
				epoll_ctl(server->epollfd, EPOLL_CTL_ADD, infd, &ev);
			} else {

				server->executor->execute(server->executor, request.data.fd);
			}

		}
	}
}

struct networkserver *initnetworkserver(networkserverconfig config) {

	struct networkserver *server = (struct networkserver *) malloc(
			sizeof(struct networkserver));

	if (server == NULL) {
		printf("初始化networkserver失败");
		exit(EXIT_FAILURE);
	}

	config(server);
	server->epollfd = epoll_create(server->maxconn + 1);
	server->requests = (struct epoll_event *) malloc(
			sizeof(struct epoll_event) * (server->maxconn + 1));

	server->serversock = socket(AF_INET, SOCK_STREAM, 0);
	bind(server->serversock, (struct sockaddr *) &(server->server_addr),
			sizeof(struct sockaddr_in));
	listen(server->serversock, server->maxconn);

	server->server.data.fd = server->serversock;
	server->server.events = EPOLLIN;
	epoll_ctl(server->epollfd, EPOLL_CTL_ADD, server->serversock,
			&(server->server));
	//开启epoll监控线程
	pthread_create(&(server->serverthread), NULL, startnetworkserver, server);
	return server;
}
