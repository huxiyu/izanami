/*
 * iregion.h
 *
 *  Created on: 2018年9月11日
 *      Author: caojx
 */

#ifndef IREGION_H_
#define IREGION_H_

#include "config.h"
#include "icell.h"
#include "ifile.h"
#include "iregioninfo.h"
#include "memconsumer.h"
#include "skiplist.h"

struct iregion {

	struct skiplist *memstore;
	int memstorerefcnt;
	struct memconsumer *consumer;
	char dirname[IZANAMI_MAX_LEN];
	struct iregioninfo *info;
};

void inserticell(struct iregion *iregion, struct icell *icell);
void flushiregion(struct iregion *iregion, struct ifilemanager *filemanager);
int iregioncmp(void *arg1, void *arg2);
void loadiregion(struct iregion *iregion, struct iregioninfo *info);

struct iregionmanager {

	int iregioncnt;
	int maxiregion;
	struct iregion *iregions;
};

struct iregionmanager *initiregionmanager(struct iregioninfoset *set);
struct iregion *getiregion(struct iregionmanager *manager, char *table,
		struct icell *icell);
struct iregion *getiregionbyregioninfo(struct iregionmanager *manager, char *tablename, char *startkey, char *endkey);

#endif /* IREGION_H_ */
