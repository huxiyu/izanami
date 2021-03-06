/*
 * mempool.h
 *
 *  Created on: 2018年8月26日
 *      Author: caojx
 */

#ifndef MEMPOOL_H_
#define MEMPOOL_H_

#include "workercommon.h"

struct mempool {

	void *start;
	struct skiplist *freelist;
	struct skiplist *usedlist;
};

struct mempool *getmempool();
struct blockinfo *getblock(struct mempool *pool);
void returnblock(struct mempool *pool, struct blockinfo *info);

int getblocksize();
int getmetasize();
int getdatasize();

#endif /* MEMPOOL_H_ */
