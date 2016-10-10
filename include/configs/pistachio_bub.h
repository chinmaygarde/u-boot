/*
 * Copyright (C) 2015 Imagination Technologies
 * Author: Govindraj Raja <govindraj.raja@imgtec.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef _PISTACHIO_CONFIG_H
#define _PISTACHIO_CONFIG_H

#include <asm/addrspace.h>
#include <asm/pistachio.h>

/*
 * System configuration
 */

#define CONFIG_SKIP_LOWLEVEL_INIT
#define CONFIG_DISPLAY_CPUINFO

#define CONFIG_PISTACHIO
#define PISTACHIO_BOARD_NAME		CONFIG_SYS_CONFIG_NAME
#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_DISPLAY_BOARDINFO

#define CONFIG_OF_LIBFDT
/*
 * CPU Configuration
 */
#define CONFIG_SYS_MHZ			546
#define CONFIG_SYS_MIPS_TIMER_FREQ	(CONFIG_SYS_MHZ * 1000000)

#define CONFIG_PHYS_TO_BUS

/*
 *FIT Image
*/
#define CONFIG_FIT
#ifdef CONFIG_FIT
#define CONFIG_FIT_BEST_MATCH
#define CONFIG_FIT_SIGNATURE
#define CONFIG_FIT_VERBOSE
#define CONFIG_RSA
#define CONFIG_RSA_SOFTWARE_EXP
#define CONFIG_IMAGE_FORMAT_LEGACY
#define FITBOOT_VARIABLES	\
	"fitfile=fitImage\0"	\
	"fitconf="PISTACHIO_BOARD_NAME"_config@1\0"	\
	"bootm_verify=y\0"
#else
#define FITBOOT_VARIABLES ""
#endif

/*
 * Memory map
 */
#define CONFIG_SYS_GRAM_BASE		0x9A000000
#define CONFIG_SYS_GRAM_SIZE		0x00066CC0
#define CONFIG_SYS_SRAM_BASE		0x9B000000
#define CONFIG_SYS_SRAM_SIZE		0x00010000
#define CONFIG_SYS_SOC_REG_BASE		0x18100000
#define CONFIG_SYS_SOC_REG_SIZE		0x00440000

#define CONFIG_SYS_TEXT_BASE		0x00400000
#define CONFIG_UBOOT_EARLY_MEM		0x00400000

#define CONFIG_SYS_MONITOR_BASE		CONFIG_SYS_TEXT_BASE

#define CONFIG_MEMSIZE_IN_BYTES
#define CONFIG_SYS_SDRAM_BASE		0x00000000

#ifndef CONFIG_OF_CONTROL
#define CONFIG_SYS_MEM_SIZE		(128 * 1024 * 1024)
#endif

#define CONFIG_SYS_INIT_SP_OFFSET	0x400000

#define CONFIG_SYS_LOAD_ADDR		0x01000000
#define CONFIG_SYS_MEMTEST_START	0x00100000
#define CONFIG_SYS_MEMTEST_END		0x00800000

#define CONFIG_SYS_MALLOC_LEN		(4 * 1024 * 1024)
#define CONFIG_SYS_BOOTPARAMS_LEN	(128 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 * 1024 * 1024)

#define CONFIG_BOOTCOUNT_LIMIT

/*
 * enable scratchpad_read/write command
 * Note: scratchpad register 0 is in use for bootcount so should not be modified
 */
#define CONFIG_CMD_PISTACHIO_SCRATCHPAD
/*
 * factory reset cmd just sets a value in scratchpad reg, actual
 * reset will be done by Linux when it boots
 */
#define FACTORY_RESET_CMD "scratchpad_write 1 0x1234"

/*
 * Console configuration
 */
#ifdef CONFIG_SYS_PROMPT
#undef CONFIG_SYS_PROMPT
#endif
#define CONFIG_SYS_PROMPT		"pistachio # "

#define CONFIG_SYS_CBSIZE		256
#define CONFIG_SYS_PBSIZE		(CONFIG_SYS_CBSIZE + \
					 sizeof(CONFIG_SYS_PROMPT) + 16)
#define CONFIG_SYS_MAXARGS		16

#define CONFIG_SYS_HUSH_PARSER
#define CONFIG_AUTO_COMPLETE
#define CONFIG_CMDLINE_EDITING

/*
 * Serial driver
 */
#define CONFIG_BAUDRATE			115200

#ifdef CONFIG_SYS_NS16550_REG_SIZE
#undef CONFIG_SYS_NS16550_REG_SIZE
#define CONFIG_SYS_NS16550_REG_SIZE	-4
#endif

#define CONFIG_DW_SERIAL
#define CONFIG_SYS_NS16550
#define CONFIG_SYS_NS16550_SERIAL
#define CONFIG_SYS_NS16550_CLK		(115200 * 16)

#ifndef DM_SERIAL
#define CONFIG_SYS_NS16550_COM1	(PISTACHIO_UART0)
#define CONFIG_SYS_NS16550_COM2	(PISTACHIO_UART1)
#define CONFIG_CONS_INDEX		2
#endif

/*
 * Ethernet configuration
 */
/* to use Pistachio specific configuration */
#define CONFIG_PISTACHIO_DW_MAC

#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL
#define CONFIG_MII
#define CONFIG_AUTONEG_TIMEOUT		(150 * CONFIG_SYS_HZ)
#define CONFIG_ETH_DESIGNWARE

#define	CONFIG_SYS_RX_ETH_BUFFER	16

/*
 * USB configuration
 */
#define CONFIG_USB_DWC2_REG_ADDR	(PISTACHIO_USB)
#define CONFIG_USB_DWC2

/* Default option is NAND_BOOT */
#define NAND_BOOT

/* SPL */
#define CONFIG_SPL_BOARD_INIT
#define CONFIG_SPL_FRAMEWORK
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_SPL_SPI_FLASH_SUPPORT
#define CONFIG_SPL_SPI_LOAD
#define CONFIG_IGNORE_BOOT_FLAG
#define CONFIG_DRAM_DDR2

/* Memory layout for SPL */
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_TEXT_BASE		CONFIG_SYS_GRAM_BASE
#define CONFIG_SPL_MAX_SIZE		0x00040000
#define CONFIG_SYS_SPI_U_BOOT_OFFS 	0x00080000

/* Place BSS at the beginning of SRAM */
#define CONFIG_SPL_BSS_MAX_SIZE        0x00000400
#define CONFIG_SPL_BSS_START_ADDR      CONFIG_SYS_SRAM_BASE

/* Place dynamic allocation area before BSS */
#define CONFIG_SYS_SPL_MALLOC_SIZE 	0X00020000
#define CONFIG_SYS_SPL_MALLOC_START 	((CONFIG_SYS_GRAM_BASE) + \
					(CONFIG_SPL_MAX_SIZE))

#define CONFIG_SPL_LDSCRIPT		"arch/mips/cpu/u-boot.lds"

#ifdef NAND_BOOT
/* SPFI */
#define CONFIG_IMGTEC_SPFI
#define CONFIG_SPI_FLASH
/* NOR support */
#define CONFIG_CMD_SF
#define CONFIG_SYS_SPI1_CS0_GPIO	0
#define CONFIG_SYS_SPI1_CS1_GPIO	58
#define CONFIG_SPI_FLASH_WINBOND
#define CONFIG_SPI_FLASH_USE_4K_SECTORS
/* NOR partitions */
#ifndef CONFIG_SPL_BUILD
#define CONFIG_SPI_FLASH_MTD
#endif
/* NAND support */
#define CONFIG_MTD_SPI_NAND
#define CONFIG_MTD_SPI_NAND_DEVICES
#define CONFIG_SPI_NAND_GD5F
#define CONFIG_SYS_NAND_SELF_INIT
#define CONFIG_SYS_MAX_NAND_DEVICE	1
#define CONFIG_SF_DEFAULT_BUS		1
#define CONFIG_SYS_NAND_CS		1
#define CONFIG_SYS_NAND_USE_FLASH_BBT
#define CONFIG_CMD_NAND
/* NAND pattitions */
#define CONFIG_LZO
#define CONFIG_RBTREE
#define CONFIG_CMD_MTDPARTS
#define CONFIG_MTD_DEVICE
#define CONFIG_MTD_PARTITIONS
#define CONFIG_CMD_UBI
#define CONFIG_CMD_UBIFS
#define MTDIDS_DEFAULT                  "nand0=spi-nand,nor0=spi-nor"
#define MTDPARTS_DEFAULT		"mtdparts=spi-nand:256M(firmware0),256M(firmware1);"\
					"spi-nor:1536k(uboot),8k(data-ro),8k(uEnv),496k(data-rw)"
#endif

/* I2C */
#define CONFIG_IMGTEC_I2C
#define CONFIG_DM_I2C
#define CONFIG_CMD_I2C

/* TPM I2C interface */
#define CONFIG_TPM
#define CONFIG_DM_TPM
#define CONFIG_TPM_TIS_I2C_BUS_NUMBER		0
#define CONFIG_TPM_TIS_I2C_SLAVE_ADDRESS	0x20
#define CONFIG_TPM_TIS_I2C
#define CONFIG_CMD_TPM

/* MMC - Sdhost */
#define CONFIG_MMC
#define CONFIG_GENERIC_MMC
#define CONFIG_DWMMC
#define CONFIG_BOUNCE_BUFFER

#define HAVE_BLOCK_DEVICE
#define CONFIG_PARTITION_UUIDS
#define CONFIG_CMD_FAT
#define CONFIG_CMD_EXT3
#define CONFIG_CMD_EXT4
#define CONFIG_DOS_PARTITION
#define CONFIG_ISO_PARTITION
#define CONFIG_FS_EXT4
#define CONFIG_FS_FAT

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ENV_IS_IN_SPI_FLASH
#define CONFIG_ENV_SECT_SIZE		0x01000		/* 4KB */
#define CONFIG_ENV_SIZE			0x02000		/* 8KB */
#define CONFIG_ENV_OFFSET		0x182000	/* env starts here */
#define CONFIG_ENV_SPI_BUS		1
#define CONFIG_ENV_SPI_CS		0

#define USB_BOOTCOMMAND							\
	"sf probe 1:0;"                                                 \
	"mtdparts default;"                                             \
	"setenv bootargs $console $earlycon $usbroot $bootextra $mtdparts;" 	\
	"setenv verify n;"						\
	"usb start;"							\
	"ext4load usb $usbdev $fdtaddr $bootdir$fdtfile;"		\
	"ext4load usb $usbdev $loadaddr $bootdir$bootfile;"		\
	"bootm $loadaddr - $fdtaddr;"

#define ETH_BOOTCOMMAND							\
	"setenv verify n;"						\
	"dhcp $loadaddr $bootfile; dhcp $fdtaddr $fdtfile;"		\
	"bootm $loadaddr - $fdtaddr;"

#define MMC_BOOTCOMMAND							\
	"sf probe 1:0;"                                                 \
	"mtdparts default;"                                             \
	"setenv bootargs $console $earlycon $mmcroot $bootextra $mtdparts;" 	\
	"setenv verify n;"						\
	"mmcinfo; mmc dev $mmcdev;"					\
	"ext4load mmc $mmcdev $fdtaddr $bootdir$fdtfile;"		\
	"ext4load mmc $mmcdev $loadaddr $bootdir$bootfile;"		\
	"bootm $loadaddr - $fdtaddr;"

#define NAND_BOOT_INIT							\
	"sf probe 1:0;"								\
	"mtdparts default;"							\
	"setenv nandroot ubi.mtd=firmware${boot_partition} root=ubi0:rootfs rootfstype=ubifs;"	\
	"setenv bootargs $console $earlycon $nandroot $bootextra $mtdparts panic=2;"	\
	"setenv verify $bootm_verify;"						\
	"ubi part firmware${boot_partition};"					\
	"ubifsmount ubi:rootfs || reset;"

#define NAND_UIMAGE_BOOT							\
	"setenv ubifs_bootm_cmd \"ubifsload $loadaddr $bootdir$bootfile && "	\
	"ubifsload $fdtaddr $bootdir$fdtfile && "				\
	"bootm $loadaddr - $fdtaddr\";"

#define NAND_FITIMAGE_BOOT							\
	"setenv ubifs_bootm_cmd \"ubifsload $loadaddr $bootdir$fitfile && "	\
	"bootm $loadaddr#$fitconf\";"

#define NAND_BOOTCOMMAND							\
	NAND_BOOT_INIT							\
	"if ubifsls $bootdir$fitfile; then "					\
		NAND_FITIMAGE_BOOT						\
	"else "									\
		NAND_UIMAGE_BOOT						\
	"fi;"									\
	"run ubifs_bootm_cmd || reset;"

#ifdef CONFIG_BOOTCOUNT_LIMIT

#define CONFIG_SYS_BOOTCOUNT_ADDR	0x18102120

#define ALT_BOOTCOMMAND							\
	"setexpr boot_partition ${boot_partition} + 1 && " \
	"setexpr boot_partition ${boot_partition} % 2 && " \
	"echo Boot failure detected, switching to firmware${boot_partition} && "	\
	"saveenv && "	\
	NAND_BOOTCOMMAND

#define BOOTCOUNT_VARIABLES			\
	"bootlimit=5\0"				\
	"altbootcmd="ALT_BOOTCOMMAND"\0"

#else

#define BOOTCOUNT_VARIABLES ""

#endif

#define NET_BOOTCOMMAND										\
	"sf probe 1:0;"                                                 \
	"mtdparts default;"                                             \
	"setenv bootargs $console $earlycon $netroot nfsroot=$serverip:$rootpath $bootextra $mtdparts;"	\
	ETH_BOOTCOMMAND

#define BOOT_EXTRA "rootwait ro lpj=723968"

#ifndef NAND_BOOT
#define CONFIG_BOOTCOMMAND	USB_BOOTCOMMAND
#else
#define CONFIG_BOOTCOMMAND	NAND_BOOTCOMMAND
#endif

#define CONFIG_EXTRA_ENV_SETTINGS 					\
	"console=console=ttyS1,115200n8\0" 				\
	"earlycon=earlycon=uart8250,mmio32,0x18101500,115200\0" 	\
	"bootextra="BOOT_EXTRA"\0"					\
	"rootpath=/srv/fs\0"						\
	"usbroot=root=/dev/sda1\0"					\
	"mmcroot=root=/dev/mmcblk0p1\0"					\
	"boot_partition=0\0"						\
	"netroot=root=/dev/nfs rootfstype=nfs ip=dhcp\0"		\
	"fdtaddr=0x0D000000\0"						\
	"fdtfile="PISTACHIO_BOARD_NAME".dtb\0"				\
	"bootfile=uImage\0"						\
	FITBOOT_VARIABLES						\
	"loadaddr=0x0E000000\0"						\
	"bootdir=/\0"							\
	"usbdev=0\0"							\
	"usbpart=0\0"							\
	"mmcdev=0\0"							\
	"usbboot="USB_BOOTCOMMAND"\0"					\
	"mmcboot="MMC_BOOTCOMMAND"\0"					\
	"ethboot="ETH_BOOTCOMMAND"\0"					\
	"netboot="NET_BOOTCOMMAND"\0"					\
	"nandboot="NAND_BOOTCOMMAND"\0"			\
	BOOTCOUNT_VARIABLES						\
	"factory_reset="FACTORY_RESET_CMD"\0"				\
	"\0"

#define CONFIG_BOOTDELAY    2

/*
* Hash Accelerator
*/

#define CONFIG_DEV_IMGTEC_HASH
#define HASH_BASE_ADDRESS		0x18149600
#define HASH_WRITE_PORT			0x18101100

#undef CONFIG_CMD_FPGA
#undef CONFIG_CMD_LOADB
#undef CONFIG_CMD_LOADS
#undef CONFIG_CMD_NFS
#undef CONFIG_CMD_IMLS
#undef CONFIG_CMD_XIMG

#define CONFIG_CMD_ELF

#define CONFIG_CMD_DNS
#define CONFIG_BOOTP_DNS
#define CONFIG_BOOTP_DNS2
#define CONFIG_BOOTP_GATEWAY
#define CONFIG_BOOTP_HOSTNAME
#define CONFIG_BOOTP_SUBNETMASK
#define CONFIG_BOOTP_SEND_HOSTNAME

#define CONFIG_CMD_NFS
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_PING
#define CONFIG_CMD_HASH

#define CONFIG_CMD_MMC

#define CONFIG_SYS_LONGHELP		/* verbose help, undef to save memory */

#endif /* _PISTACHIO_CONFIG_H */
