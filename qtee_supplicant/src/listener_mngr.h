// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
// SPDX-License-Identifier: BSD-3-Clause-Clear

#ifndef __LISTENER_MNGR_H
#define __LISTENER_MNGR_H

#include <stdint.h>
#include <stdio.h>

#define MSGV printf
#define MSGD printf
#define MSGE printf

typedef int (*listener_init)(void);
typedef void (*listener_deinit)(void);

/**
 * @brief Listener service.
 *
 * Represents a listener service to be initialized and started by the QTEE
 * supplicant. Each listener service offers a specific REE service to QTEE,
 * e.g. time service.
 */
struct listener_svc {
	char *service_name; /**< Name of the listener service. */
	int is_registered; /**< Listener registration status. */
	char *file_name; /**< File name of the listener service. */
	void *lib_handle; /**< LibHandle for the listener. */
	char *init; /**< Listener initialization callback. */
	char *deinit; /**< Listener deinitialization callback. */
};

/**
 * @brief Start listener services.
 *
 * Starts listener services which wait for a listener request from QTEE.
 */
int start_listener_services(void);

#endif // __LISTENER_MNGR_H
