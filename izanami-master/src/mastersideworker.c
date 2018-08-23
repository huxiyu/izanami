/*
 * mastersideworker.c
 *
 *  Created on: 2018年8月16日
 *      Author: caojx
 */

#include "mastersideworker.h"

#include <stdlib.h>
#include <string.h>

int mastersideworkercmp(void *arg1, void *arg2) {

	struct mastersideworker *instance1 = (struct mastersideworker *) arg1;
	struct mastersideworker *instance2 = (struct mastersideworker *) arg2;

	int ret = instance1->workerfd - instance2->workerfd;

	return ret;
}

struct mastersideworkermanager *initmastersideworkermanager(
		configworkermanager config) {

	struct mastersideworkermanager *manager =
			(struct mastersideworkermanager *) malloc(
					sizeof(struct mastersideworkermanager));
	config(manager);
	return manager;
}

struct mastersideworker *getmastersideworkerbyfd(
		struct mastersideworkermanager *manager, int fd) {

	struct mastersideworker *ret = NULL;
	int tmp = 0;
	while (tmp < manager->workernum) {
		struct mastersideworker *worker = manager->workers + tmp;
		if (worker->workerfd == fd) {
			ret = worker;
			break;
		}
		tmp++;
	}
	return ret;
}

void addmastersideworker(struct mastersideworkermanager *manager,
		 int fd) {

	struct mastersideworker *worker = manager->workers + manager->workernum;
	manager->workernum++;
	worker->workerfd = fd;
}

