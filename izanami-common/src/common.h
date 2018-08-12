/*
 * common.h
 *
 *  Created on: 2018年8月11日
 *      Author: caojx
 */

#ifndef SRC_COMMON_H_
#define SRC_COMMON_H_

#include "dictionary.h"

#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct networkserver;
struct executor;
struct server;

dictionary *getdict();

#endif /* SRC_COMMON_H_ */
