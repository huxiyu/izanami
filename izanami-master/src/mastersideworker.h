/*
 * mastersideworker.h
 *
 *  Created on: 2018年8月16日
 *      Author: caojx
 */

#ifndef MASTERSIDEWORKER_H_
#define MASTERSIDEWORKER_H_

#include "config.h"
#include "iregioninfo.h"

#include <arpa/inet.h>

struct mastersideworker {

	char ip[IZANAMI_MAX_IP_LEN];
	int workerfd;
	struct iregioninfoset *set;
};

struct mastersideworkermanager {

	int maxworkernum;
	int workernum;
	struct mastersideworker *workers;
};

int mastersideworkercmp(void *arg1, void *arg2);

typedef void (*configworkermanager)(struct mastersideworkermanager *manager);
struct mastersideworkermanager *initmastersideworkermanager(
		configworkermanager config);
struct mastersideworker *getmastersideworkerbyfd(
		struct mastersideworkermanager *manager, int fd);
void addmastersideworker(struct mastersideworkermanager *manager, int fd,
		char *ip);
void getregioninfos(struct mastersideworkermanager *manager, int fd);
#endif /* MASTERSIDEWORKER_H_ */
