/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Avinash Tahakik <avinash.tahakik@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>
#include <spi.h>
#include <spi_flash.h>
#include <winbond-otp.h>

#include "sf_internal.h"

/* SPI FLASH opcodes */

#define SPINOR_OP_RD_SECURITY_REG	0x48 /* Read security register */
#define SECURITY_REG_SIZE		256 /* bytes per security register */

#define REG1_START_ADDRESS		0X1000
#define REG2_START_ADDRESS		0X2000
#define REG3_START_ADDRESS		0X3000

#define REG1_END_ADDRESS		0X10FF
#define REG2_END_ADDRESS		0X20FF
#define REG3_END_ADDRESS		0X30FF

static struct spi_flash *flash;

static int check_addr_validity(loff_t from, size_t len)
{
	if ((REG1_START_ADDRESS <= from && from + len <= REG1_END_ADDRESS)
	|| (REG2_START_ADDRESS <= from && from + len <= REG2_END_ADDRESS)
	|| (REG3_START_ADDRESS <= from && from + len <= REG3_END_ADDRESS))
		return 0;

	return -1;
}

int read_otp_data(loff_t from, size_t len, char *data)
{
	if (check_addr_validity(from, len))
		return -1;

	if (!flash)
		flash = spi_flash_probe(1, 0, CONFIG_SF_DEFAULT_SPEED,
					CONFIG_SF_DEFAULT_MODE);

	if (!flash) {
		printf("Failed to initialize SPI flash at 1:0\n");
		return -1;
	}

	flash->read_cmd = SPINOR_OP_RD_SECURITY_REG;
	return spi_flash_cmd_read_ops(flash, from, len, data);
}
