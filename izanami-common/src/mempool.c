/*
 * mempool.c
 *
 *  Created on: 2018年8月26日
 *      Author: caojx
 */

#include "config.h"
#include "common.h"
#include "mempool.h"
#include "skiplist.h"
#include "workercommon.h"

#include <stdlib.h>

static struct mempool *pool = NULL;

int blockinfocmp(void *arg1, void *arg2) {

	struct blockinfo *info1 = (struct blockinfo *) arg1;
	struct blockinfo *info2 = (struct blockinfo *) arg2;
	return info1->ptr - info2->ptr;
}

struct mempool *getmempool() {

	if (pool == NULL) {
		dictionary *dict = getdict();
		long poolsize = iniparser_getlongint(dict, IZANAMI_MEMPOOL_MAXSIZE,
				1204 * 1024 * 1024);
		int blocksize = iniparser_getint(dict, IZANAMI_MEMPOOL_BLOCKSIZE,
				1024 * 1024);

		pool = (struct mempool *) malloc(sizeof(struct mempool));
		pool->start = malloc(sizeof(poolsize));
		pool->freelist = initskiplist(blockinfocmp);
		pool->usedlist = initskiplist(blockinfocmp);

		int count = poolsize / blocksize;
		int i = 0;
		for (; i < count; i++) {
			insertintoskiplist(pool->freelist, pool->start + i * blocksize);
		}

	}

	return pool;
}

struct leafinode *getfirst(struct skiplist *list) {

	struct leafinode *inode = NULL;

	struct steaminode *head = list->routenode;
	while (head->down != NULL) {
		head = head->down;
	}

	inode = (struct leafinode *) head->post;

	return inode;
}

void insertinodeintoskiplist(struct skiplist *list, struct leafinode *inode) {

	struct leafinode *prenode = findfromskiplist(list, inode->element);
	inode->post = prenode->post;
	inode->pre = prenode;
	prenode->post->pre = inode;
	prenode->post = inode;
}

struct blockinfo *getblock(struct mempool *pool) {

	struct leafinode *inode = getfirst(pool->freelist);
	deletefromskiplist(pool->freelist, inode->element);
	insertinodeintoskiplist(pool->usedlist, inode);
	return (struct blockinfo *) inode->element;
}

void returnblock(struct mempool *pool, struct blockinfo *info) {

	struct leafinode *inode = deletefromskiplist(pool->usedlist, info);
	insertinodeintoskiplist(pool->freelist, inode);
}

void setconsumerhead(struct consumerhead *head) {
	head->dataused = 0;
	head->next = NULL;
}

struct memconsumer *initmemconsumer() {

	struct memconsumer *consumer = (struct memconsumer *) malloc(
			sizeof(struct memconsumer));
	consumer->firstblock = consumer->currentblock = getblock(getmempool());

	struct consumerhead *head = consumer->firstblock;
	setconsumerhead(head);
	return consumer;
}

void *imalloc(struct memconsumer *consumer, int size) {

	struct consumerhead *head = consumer->currentblock;
	dictionary *dict = getdict();
	int datasize = iniparser_getint(dict, IZANAMI_MEMPOOL_BLOCKDATASIZE,
			1024 * 1000);
	int metasize = iniparser_getint(dict, IZANAMI_MEMPOOL_METASIZE, 1024 * 24);

	if (head->dataused + size < datasize) {
		head->dataused += size;
	} else {

		struct blockinfo *info = getblock(getmempool());
		head->next = info;
		head = info;
		setconsumerhead(head);
		head->dataused += size;
	}

	return head + metasize + head->dataused;
}

