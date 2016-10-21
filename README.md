# Using u-boot on Creator (Ci40) Marduk platform

## Toolchain setup
If you are using the toolchain produced by OpenWrt you must setup the environment as explained
[here](https://wiki.openwrt.org/doc/devel/crosscompile).

For the MIPS official toolchain see
[here](https://community.imgtec.com/developers/mips/tools/codescape-mips-sdk/download-codescape-mips-sdk-essentials/).

## Configure and build it
	$ make CROSS_COMPILE=<toolchain-prefix> pistachio_marduk_defconfig
	$ make CROSS_COMPILE=<toolchain-prefix>

This will generate u-boot-pistachio-nor.img

## Flash it onto your Ci40
See our [docs](https://docs.creatordev.io/ci40/guides/openwrt-platform/#flashing-u-boot-binary).
