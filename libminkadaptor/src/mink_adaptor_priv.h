// Copyright (c) 2025, Qualcomm Innovation Center, Inc. All rights reserved.
// SPDX-License-Identifier: BSD-3-Clause

#ifndef _MINK_ADAPTOR_PRIV_H_
#define _MINK_ADAPTOR_PRIV_H_

#include <qcomtee_object_types.h>
#include "object.h"

#define container_of(ptr, type, member) \
	((type *)((void *)(ptr) - __builtin_offsetof(type, member)))

#define DEFAULT_CBOBJ_THREAD_CNT 4

#define MAX_OBJ_ARG_COUNT                                               \
	(ObjectCounts_maxBI + ObjectCounts_maxBO + ObjectCounts_maxOI + \
	 ObjectCounts_maxOO)

#define FOR_ARGS(ndxvar, counts, section)                         \
	for (size_t ndxvar = ObjectCounts_index##section(counts); \
	     ndxvar < (ObjectCounts_index##section(counts) +      \
		       ObjectCounts_num##section(counts));        \
	     ++ndxvar)

struct qcomtee_callback_obj {
	struct qcomtee_object object;
	/* To satify the IDL interface, each BO argument passed to a
	 * to a MINK Callback Object must be initialized with a valid
	 * pointer. Allocated pointers are stored here to be free'd later.
	 */
	void *allocated_bo[ObjectCounts_maxBO];
	Object mink_obj;
};

#define CALLBACKOBJ(o) container_of((o), struct qcomtee_callback_obj, object)

#endif // _MINK_ADAPTOR_PRIV_H_
