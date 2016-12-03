/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Francois Berder <francois.berder@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _OTP_H
#define _OTP_H

#define MAC_ADDR_LEN 6

#ifdef CONFIG_WINBOND_OTP

#include <linux/types.h>

#define VERSION_REG0_OFFSET		0x1002
#define VERSION_REG1_OFFSET		0x2002
#define WIFI_STA_MAC_ADDRESS_OFFSET	0x1003
#define WIFI_AP_MAC_ADDRESS_OFFSET	0x1009
#define ETH_MAC_ADDRESS_OFFSET		0x1015
#define DCXO_OFFSET			0x2003

int read_otp_version(loff_t offset);

#endif

#endif
