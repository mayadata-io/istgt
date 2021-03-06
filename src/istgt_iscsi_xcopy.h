/*
 * Copyright © 2017-2019 The OpenEBS Authors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at

 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ISTGT_ISCSI_XCOPY_H
#define	ISTGT_ISCSI_XCOPY_H

#include <stdint.h>
#include <pthread.h>
#include "istgt.h"
#include "istgt_iscsi_param.h"
#include "istgt_iscsi.h"
#include "istgt_scsi.h"
#include "istgt_lu.h"

#define	SNLID	1 /* Support no list id Refer 6.22 / 6.4.3.2 of spc4r36s */
#define	MAX_CSCD_DESCRIPTOR_COUNT	2
#define	MAX_SEGMENT_DESCRIPTOR_COUNT	1
#define	MAX_DESCRIPTOR_LIST_LENGTH	800
/* No limit on the amount of data written by a single segment */
#define	MAX_SEGMENT_LENGTH	0
/* Set to zero since 04h descriptor code not supported */
#define	MAX_INLINE_DATA_LENGTH	0
#define	HELD_DATA_LIMIT	1
#define	MAX_STREAM_DEVICE_TRANSFER_SIZE	0
#define	TOTAL_CONCURRENT_COPIES	MAX_CONCURRENT_COPIES	/* Since snlid=1 */
#define	MAX_CONCURRENT_COPIES	5
#define	DATA_SEGMENT_GRANULARITY	512
#define	INLINE_DATA_GRANULARITY	512
#define	HELD_DATA_GRANULARITY	512
#define	IMPLEMENTED_DESCRIPTOR_LIST_LENGTH	2
#define	SEGMENT_DESCRIPTOR_B2B	0X2	/* 2d */
#define	SEGMENT_DESCRIPTOR_B2B_OFFSET	0xA	/* 10d */
#define	CSCD_IDENTIFICATION_DESCRIPTOR	0xE4	/* 228d */
#define	CSCD_DESCRIPTOR_LENGTH		32	/* 32 bytes */
#define	LIST_ID_USAGE	3	/* 11b */
/* Actual parameter data for copy starts from 16th byte */
#define	PARAMETER_HEADER_DATA	16
#define	NAA_IDENTIFIER	0x03
#define	PDT_DIRECT_ACCESS_BLK_DEV 0x00
#define	PDT_SIMPLIFIED_DIRECT_ACCESS_DEV	0x0E

typedef struct istgt_xcopy_tgt_t {
	ISTGT_LU_DISK *spec;
	uint32_t block_len;
	uint64_t lba;
	uint64_t offset;
	int pad;
} ISTGT_XCOPY_TGT;

int istgt_lu_disk_receive_copy_results(CONN_Ptr conn, ISTGT_LU_CMD_Ptr lu_cmd);
int istgt_lu_disk_xcopy(ISTGT_LU_DISK *spec,
    CONN_Ptr conn, ISTGT_LU_CMD_Ptr lu_cmd);
int istgt_lu_disk_process_xcopy(ISTGT_LU_DISK *spec,
    CONN_Ptr conn, ISTGT_LU_CMD_Ptr lu_cmd, uint8_t *data_buf, int dlen);
int istgt_lu_disk_lbxcopy(ISTGT_XCOPY_TGT *src_tgt, ISTGT_XCOPY_TGT *dst_tgt,
    CONN_Ptr conn, ISTGT_LU_CMD_Ptr lu_cmd, int dc, int cat,
    uint64_t num_blks_byts, uint8_t sd_opcode);


#endif /* ISTGT_ISCSI_XCOPY_H */
