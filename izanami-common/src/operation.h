/*
 * operation.h
 *
 *  Created on: 2018年8月15日
 *      Author: caojx
 */

#ifndef OPERATION_H_
#define OPERATION_H_

enum operation {

	/**
	 * worker2master
	 */
	report,

	/**
	 * master2worker
	 */
	assign,

	/**
	 * client2master
	 */
	route, create,

	/**
	 * client2worker
	 */
	put, scan
};

#endif /* OPERATION_H_ */
