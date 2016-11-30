/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Francois Berder <francois.berder@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <winbond-otp.h>
#include "otp.h"

int read_otp_version(loff_t offset)
{
	u_char version;

	if (read_otp_data(offset, sizeof(version), (char *)&version)) {
		printf("WARNING: Could not read register version from OTP.\n");
		return -1;
	}

	return version;
}
