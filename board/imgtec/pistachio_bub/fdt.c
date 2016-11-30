/*
 * Copyright (C) 2016 Imagination Technologies
 * Author: Francois Berder <francois.berder@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <common.h>

#if defined(CONFIG_OF_LIBFDT) && defined(CONFIG_OF_BOARD_SETUP)

#include <winbond-otp.h>
#include "otp.h"

DECLARE_GLOBAL_DATA_PTR;

static void fixup_wifi_mac(void *blob, int node)
{
	u_char wifi_sta_mac_addr[MAC_ADDR_LEN], wifi_ap_mac_addr[MAC_ADDR_LEN];

	memset(wifi_sta_mac_addr, 0, sizeof(wifi_sta_mac_addr));
	memset(wifi_ap_mac_addr, 0, sizeof(wifi_ap_mac_addr));

	if (read_otp_version(VERSION_REG0_OFFSET) >= 1) {
		/* Read MAC addresses from OTP */
		if (read_otp_data(WIFI_STA_MAC_ADDRESS_OFFSET, MAC_ADDR_LEN,
				  (char *)wifi_sta_mac_addr)
		||  read_otp_data(WIFI_AP_MAC_ADDRESS_OFFSET, MAC_ADDR_LEN,
				  (char *)wifi_ap_mac_addr)) {
			printf("WARNING: Could not read Wifi MAC addresses from OTP\n");
			return;
		}
	}

	/* Set Wifi STA and AP MAC address in device tree */
	if (is_valid_ethaddr(wifi_sta_mac_addr))
		fdt_setprop(blob, node, "mac-address0", wifi_sta_mac_addr,
			    MAC_ADDR_LEN);
	else
		printf("WARNING: Invalid Wifi sta MAC address.\n");

	if (is_valid_ethaddr(wifi_ap_mac_addr))
		fdt_setprop(blob, node, "mac-address1", wifi_ap_mac_addr,
			    MAC_ADDR_LEN);
	else
		printf("WARNING: Invalid Wifi ap MAC address.\n");
}

static void fixup_wifi_calibration(void *blob, int node)
{
	int len;
	char dcxo;
	char *rf_params_prop;
	int version_reg1 = read_otp_version(VERSION_REG1_OFFSET);

	if (version_reg1 >= 1) {
		/* Read calibration data from OTP */
		if (read_otp_data(DCXO_OFFSET, sizeof(dcxo), &dcxo)) {
			printf("WARNING: Could not read dcxo from OTP\n");
			return;
		}
	}

	/* Overwrite first byte of rf-params property with DXCO */
	rf_params_prop = fdt_getprop_w(blob, node, "rf-params", &len);
	if (!rf_params_prop) {
		printf("WARNING: Could not find rf-params property.\n");
		return;
	}

	if (version_reg1 >= 1)
		rf_params_prop[0] = dcxo;

	fdt_setprop(blob, node, "rf-params", rf_params_prop, len);
}

int ft_board_setup(void *blob, bd_t *bd)
{
	int node = fdt_path_offset(blob, "wifi0");
	if (node < 0) {
		printf("WARNING: can't find wifi0 alias\n");
		return -1;
	}

	fixup_wifi_mac(blob, node);
	fixup_wifi_calibration(blob, node);

	return 0;
}
#endif
