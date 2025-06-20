// Copyright (c) Qualcomm Technologies, Inc. and/or its subsidiaries.
// SPDX-License-Identifier: BSD-3-Clause-Clear

#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "fs_msg.h"
#include "cmn.h"
#include "helper.h"
#include "fs.h"

int smci_dispatch(void *buf, size_t buf_len);

int smci_dispatch(void *buf, size_t buf_len)
{
	int ret = -1;
	tz_fs_msg_cmd_type fs_cmd_id;

	MSGD("FSDispatch starts!\n");

	/* Buffer size is 4K aligned and should always be big enough to
	 * accomodate the largest of fs structs */
	if (buf_len < TZ_MAX_BUF_LEN) {
		MSGE("[%s:%d] Invalid buffer len.\n", __func__, __LINE__);
		return -1; // This should be reported as a transport error
	}

	fs_cmd_id = *((tz_fs_msg_cmd_type *)buf);
	MSGD("fs_cmd_id = 0x%x\n", fs_cmd_id);

	/* Make sure that partition is mounted before proceeding */
	if (!is_persist_partition_mounted()) {
		MSGE("persist partition is not mounted, dispatch failed!\n.");
		file_partition_error(fs_cmd_id, buf);
		return 0;
	}

	/* Read command id */
	switch (fs_cmd_id) {
	case TZ_FS_MSG_CMD_FILE_OPEN:
		MSGD("file_open starts!\n");
		ret = file_open(buf, buf_len, buf, buf_len);
		MSGD("file_open finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_OPENAT:
		MSGD("file_openat starts!\n");
		ret = file_openat(buf, buf_len, buf, buf_len);
		MSGD("file_openat finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_UNLINKAT:
		MSGD("file_unlinkat starts!\n");
		ret = file_unlinkat(buf, buf_len, buf, buf_len);
		MSGD("file_unlinkatis finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_FCNTL:
		MSGD("file_fcntl starts!\n");
		ret = file_fcntl(buf, buf_len, buf, buf_len);
		MSGD("file_fcntl finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_CREAT:
		MSGD("file_create starts!\n");
		ret = file_creat(buf, buf_len, buf, buf_len);
		MSGD("file_create finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_READ:
		MSGD("file_read starts!\n");
		ret = file_read(buf, buf_len, buf, buf_len);
		MSGD("file_read finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_WRITE:
		MSGD("file_write starts!\n");
		ret = file_write(buf, buf_len, buf, buf_len);
		MSGD("file_write finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_CLOSE:
		MSGD("file_close starts!\n");
		ret = file_close(buf, buf_len, buf, buf_len);
		MSGD("file_close finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_LSEEK:
		MSGD("file_lseek starts!\n");
		ret = file_lseek(buf, buf_len, buf, buf_len);
		MSGD("file_lseek finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_LINK:
		MSGD("file_link starts!\n");
		ret = file_link(buf, buf_len, buf, buf_len);
		MSGD("file_link finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_UNLINK:
		MSGD("file_unlink starts\n");
		ret = file_unlink(buf, buf_len, buf, buf_len);
		MSGD("file_unlink finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_RMDIR:
		MSGD("file_rmdir starts!\n");
		ret = file_rmdir(buf, buf_len, buf, buf_len);
		MSGD("file_rmdir finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_FSTAT:
		MSGD("file_fstat starts!\n");
		ret = file_fstat(buf, buf_len, buf, buf_len);
		MSGD("file_fstat finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_LSTAT:
		MSGD("file_lstat starts!\n");
		ret = file_lstat(buf, buf_len, buf, buf_len);
		MSGD("file_lstat finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_MKDIR:
		MSGD("file_mkdir starts!\n");
		ret = file_mkdir(buf, buf_len, buf, buf_len);
		MSGD("file_mkdir finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_TESTDIR:
		MSGD("file_testdir starts!\n");
		ret = file_testdir(buf, buf_len, buf, buf_len);
		MSGD("file_testdir finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_TELLDIR:
		MSGD("file_telldir starts!\n");
		ret = file_telldir(buf, buf_len, buf, buf_len);
		MSGD("file_telldir finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_REMOVE:
		MSGD("file_remove starts!\n");
		ret = file_remove(buf, buf_len, buf, buf_len);
		MSGD("file_remove finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_CHOWN_CHMOD:
		MSGD("file_dir_chown_chmod starts!\n");
		ret = file_dir_chown_chmod(buf, buf_len, buf,
					   buf_len);
		MSGD("file_dir_chown_chmod finished!\n");
		break;
	case TZ_FS_MSG_CMD_FILE_END:
		MSGD("file_services Dispatch end request!\n");
		ret = file_end(buf, buf_len, buf, buf_len);
		break;
	case TZ_FS_MSG_CMD_FILE_SYNC:
		MSGD("file_sync starts!\n");
		ret = file_sync(buf, buf_len, buf, buf_len);
		MSGD("file_sync finished!\n");
		break;

	case TZ_FS_MSG_CMD_FILE_RENAME:
		MSGD("file_rename starts!\n");
		ret = file_rename(buf, buf_len, buf, buf_len);
		MSGD("file_rename finished!\n");
		break;

	case TZ_FS_MSG_CMD_FILE_PAR_FR_SIZE:
		MSGD("file_get_partition_free_size get partition free size\n");
		ret = file_get_partition_free_size(buf, buf_len, buf,
					     buf_len);
		MSGD("file_get_partition_free_size finished!\n");
		break;

	case TZ_FS_MSG_CMD_DIR_OPEN:
		MSGD("dir_open starts!\n");
		ret = dir_open(buf, buf_len, buf, buf_len);
		MSGD("dir_open finished!\n");
		break;

	case TZ_FS_MSG_CMD_DIR_READ:
		MSGD("dir_read starts!\n");
		ret = dir_read(buf, buf_len, buf, buf_len);
		MSGD("dir_read finished!\n");
		break;

	case TZ_FS_MSG_CMD_DIR_CLOSE:
		MSGD("dir_close starts!\n");
		ret = dir_close(buf, buf_len, buf, buf_len);
		MSGD("dir_close finished!\n");
		break;

	case TZ_FS_MSG_CMD_FILE_GET_ERRNO:
		MSGD("file_get_errno starts!\n");
		ret = file_get_errno(buf, buf_len);
		MSGD("file_get_errno finished\n");
		break;
	default:
		MSGD("file command 0x%x is not found!, returning ERROR!\n",
		     fs_cmd_id);
		ret = file_error(buf, buf_len);
		break;
	}

	MSGD("FSDispatch ends! %d\n", ret);
	return ret;
}
