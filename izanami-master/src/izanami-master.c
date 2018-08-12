/*
 * izanami-master.c
 *
 *  Created on: 2018年8月11日
 *      Author: caojx
 */

#include "common.h"
#include "config.h"
#include "dictionary.h"
#include "executor.h"
#include "iniparser.h"
#include "izanami-master.h"
#include "masterexecutor.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void waitmasterfinish(struct master *_master) {

	printf("waiting master to finish\n");
	pthread_join(_master->networkserver->serverthread, NULL);
}

void configmaster(struct networkserver *server) {

	dictionary *dict = getdict();
	server->port = iniparser_getint(dict, IZANAMI_MASTER_PORT, 7000);
	server->eth = iniparser_getstring(dict, IZANAMI_MASTER_ETH, "0.0.0.0");
	server->maxconn = iniparser_getint(dict, IZANAMI_MASTER_MAXCONN, 1024);
	server->executor = (struct executor*) initmasterexecutor();
}

struct master * initmaster() {

	struct master * ret = (struct master *) malloc(sizeof(struct master));
	ret->networkserver = initnetworkserver(configmaster);
	struct masterexecutor * executor =
			(struct masterexecutor *) (ret->networkserver->executor);
	executor->server = ret;

	return ret;
}
