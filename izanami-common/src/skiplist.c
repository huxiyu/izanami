/*
 * skiplist.c
 *
 *  Created on: 2018年8月26日
 *      Author: caojx
 */

#include "common.h"
#include "mempool.h"
#include "skiplist.h"

#include <stdlib.h>

void setsteaminode(struct steaminode *inode) {

	inode->element = NULL;
	inode->down = inode->upper = inode->post = inode->pre = NULL;
}

struct skiplist *initskiplist(elementcmp cmp) {

	struct skiplist *list = (struct skiplist *) malloc(sizeof(struct skiplist));
	list->count = 0;
	list->layer = 1;
	list->repeatable = FALSE;
	list->cmp = cmp;
	list->consumer = initmemconsumer();
	list->routenode = imalloc(list->consumer, sizeof(struct steaminode));
	setsteaminode(list->routenode);
	return list;
}

void setrepeatable(struct skiplist *list) {

	list->repeatable = TRUE;
}

struct leafinode *deletefromskiplist(struct skiplist *list, void *element) {

	return NULL;
}

struct leafinode *findfromskiplist(struct skiplist *list, void *element) {

	return NULL;
}

struct leafinode *insertintoskiplist(struct skiplist *list, void *element) {

	return NULL;
}
