/*
 * am335x_epn11291.h
 *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __CONFIG_AM335X_EVM_H
#define __CONFIG_AM335X_EVM_H


#ifdef CONFIG_SPL_BUILD
#ifndef DEBUG
#define DEBUG
#endif
#endif

#include <configs/ti_am335x_common.h>
#include <linux/sizes.h>

//#ifdef CONFIG_OF_SEPARATE
//#undef CONFIG_OF_SEPARATE
//#endif

//#undef CONFIG_I2C
//#undef CONFIG_SYS_I2C
// #ifdef CONFIG_MMC
// #undef CONFIG_MMC
// #endif

//#define EPN11291_USE_ENET
//#define SPL_BOARD_INIT 1

#ifdef EPN11291_USE_ENET
// #ifndef CONFIG_SPL_ETH_DEVICE
// #define CONFIG_SPL_ETH_DEVICE "cpsw_emac0"
// #endif

#ifndef CONFIG_SPL_ETH_SUPPORT
#define CONFIG_SPL_ETH_SUPPORT
#endif

#ifndef CONFIG_SPL_NET_SUPPORT
#define CONFIG_SPL_NET_SUPPORT
#endif
#endif

#ifndef CONFIG_SPL_BUILD
# define CONFIG_TIMESTAMP
#endif

#define CONFIG_SYS_BOOTM_LEN		SZ_16M

#define CONFIG_MACH_TYPE		MACH_TYPE_AM335XEVM

/* Clock Defines */
#define V_OSCK				25000000  /* Clock output from T2 */
#define V_SCLK				(V_OSCK)

/* Custom script for NOR */
#define CONFIG_SYS_LDSCRIPT		"board/flightcircuits/am335x-epn11291/u-boot.lds"

/* Always 128 KiB env size */
//#define CONFIG_ENV_SIZE			SZ_128K

#define NANDARGS "\0"

#define BOOTENV_DEV_LEGACY_MMC(devtypeu, devtypel, instance) \
	"bootcmd_" #devtypel #instance "=" \
	"setenv devtype mmc; " \
	"setenv mmcdev " #instance"; "\
	"setenv bootpart " #instance":2 ; "\
	"run boot\0"

#define BOOTENV_DEV_NAME_LEGACY_MMC(devtypeu, devtypel, instance) \
	#devtypel #instance " "

#define BOOTENV_DEV_NAND(devtypeu, devtypel, instance) \
	"bootcmd_" #devtypel "=" \
	"run nandboot\0"

#define BOOTENV_DEV_NAME_NAND(devtypeu, devtypel, instance) \
	#devtypel #instance " "

#if CONFIG_IS_ENABLED(CMD_PXE)
# define BOOT_TARGET_PXE(func) func(PXE, pxe, na)
#else
# define BOOT_TARGET_PXE(func)
#endif

#if CONFIG_IS_ENABLED(CMD_DHCP)
# define BOOT_TARGET_DHCP(func) func(DHCP, dhcp, na)
#else
# define BOOT_TARGET_DHCP(func)
#endif

#define BOOT_TARGET_DEVICES(func) \
	func(MMC, mmc, 0) \
	func(LEGACY_MMC, legacy_mmc, 0) \
	func(MMC, mmc, 1) \
	func(LEGACY_MMC, legacy_mmc, 1) \
	BOOT_TARGET_PXE(func) \
	BOOT_TARGET_DHCP(func)

#include <config_distro_bootcmd.h>

// #define AM335XX_BOARD_FDTFILE
// 	"fdtfile=epn11291.dtb\0"

#ifndef CONFIG_SPL_BUILD
#include <environment/ti/dfu.h>
#include <environment/ti/mmc.h>

//XXXTODO
//#define CONFIG_BOOTFILE "5.8.0-rc4-bone4.zImage"

/* #define CONFIG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	DEFAULT_MMC_TI_ARGS \
	DEFAULT_FIT_TI_ARGS \
	"bootpart=1:2\0" \
	"bootdir=/boot\0" \
	"bootfile=vmlinuz-4.19.94-ti-r36\0" \
	"fdtfile=epn11291.dtb\0" \
	"fdt_addr=0x8E000000\0"			\
	"console=ttyS0,115200n8\0" \
	"partitions=" \
		"uuid_disk=${uuid_gpt_disk};" \
		"name=bootloader,start=384K,size=1792K," \
			"uuid=${uuid_gpt_bootloader};" \
		"name=rootfs,start=2688K,size=-,uuid=${uuid_gpt_rootfs}\0" \
	"optargs=\0" \
	"boot_os=bootz ${loadaddr} - ${fdt_addr};\0" \
	"ramroot=/dev/ram0 rw\0" \
	"ramrootfstype=ext2\0" \
	"ramargs=setenv bootargs console=${console} earlyprintk " \
		"${optargs} " \
		"root=${ramroot} " \
		"rootfstype=${ramrootfstype}\0" \
	"loadramdisk=load mmc ${mmcdev} ${rdaddr} ramdisk.gz\0" \
	"pb_eeprom_hdr=" \
		"mw 82001000 ee3355aa; " \
		"mw 82001004 35333341; " \
		"mw 82001008 4c474250\0" \
	"serverip=192.168.1.123\0" \
	"ipaddr=192.168.1.136\0" \
	"router=192.168.1.1\0" \
	"if_netconsole=ping $serverip\0" \
	"start_netconsole=" \
		"setenv ncip $serverip; " \
		"setenv bootdelay 10; " \
		"setenv stdin serial,nc; " \
		"setenv stdout serial,nc; " \
		"setenv stderr serial,nc; " \
		"version\0" \
	"preboot=run if_netconsole start_netconsole\0"\
	"ramboot=echo Booting from ramdisk ...; " \
		"run ramargs; " \
		"bootz ${loadaddr} ${rdaddr} ${fdt_addr}\0" \
	"findfdt= setenv fdtfile epn11291.dtb;" \
	"init_console= setenv console ttyS0,115200n8; " \
	"rwlboot=echo Loading elf image ...; " \
		"bootp ${loadaddr} '${serverip}':${bootfile}; " \
		"echo booting elf image ...; "\
		"bootelf ${loadaddr}\0" \
	NETARGS \
	BOOTENV
#endif
 */
// Adapted from EEWIKI_UNAME_BOOT

// Adapted from EEWIKI_NFS
#define EPNWIKI_NFS \
	"server_ip=192.168.1.100\0" \
	"gw_ip=192.168.1.1\0" \
	"netmask=255.255.255.0\0" \
	"hostname=\0" \
	"device=eth0\0" \
	"autoconf=off\0" \
	"root_dir=/home/userid/targetNFS\0" \
	"tftp_dir=\0" \
	"nfs_options=,vers=3\0" \
	"nfsrootfstype=ext4 rootwait fixrtc\0" \
	"nfsargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"${cape_uboot} " \
		"root=/dev/nfs rw " \
		"rootfstype=${nfsrootfstype} " \
		"nfsroot=${nfsroot} " \
		"ip=${ip} " \
		"${cmdline}\0" \
	"nfsboot=echo Booting from ${server_ip} ...; " \
		"setenv nfsroot ${server_ip}:${root_dir}${nfs_options}; " \
		"setenv ip ${client_ip}:${server_ip}:${gw_ip}:${netmask}:${hostname}:${device}:${autoconf}; " \
		"setenv autoload no; " \
		"setenv serverip ${server_ip}; " \
		"setenv ipaddr ${client_ip}; " \
		"tftp ${loadaddr} ${tftp_dir}${bootfile}; " \
		"tftp ${fdtaddr} ${tftp_dir}dtbs/${fdtfile}; " \
		"run nfsargs; " \
		"bootz ${loadaddr} - ${fdtaddr}\0" \
	"nfsboot_uname_r=echo Booting from ${server_ip} ...; " \
		"setenv nfsroot ${server_ip}:${root_dir}${nfs_options}; " \
		"setenv ip ${client_ip}:${server_ip}:${gw_ip}:${netmask}:${hostname}:${device}:${autoconf}; " \
		"setenv autoload no; " \
		"setenv serverip ${server_ip}; " \
		"setenv ipaddr ${client_ip}; " \
		"tftp ${loadaddr} ${tftp_dir}vmlinuz-${uname_r}; " \
		"tftp ${fdtaddr} ${tftp_dir}dtbs/${uname_r}/${fdtfile}; " \
		"run nfsargs; " \
		"bootz ${loadaddr} - ${fdtaddr}\0" \

// Adapted from EEWIKI_BOOT
#define EPNWIKI_BOOT \
	"boot=${devtype} dev ${mmcdev}; " \
		"if ${devtype} rescan; then " \
			"echo gpio set 54;" \
			"setenv bootpart ${mmcdev}:1; " \
			"if test -e ${devtype} ${bootpart} /etc/fstab; then " \
				"setenv mmcpart 1;" \
			"fi; " \
			"echo Checking for: /uEnv.txt ...;" \
			"if test -e ${devtype} ${bootpart} /uEnv.txt; then " \
				"if run loadbootenv; then " \
					"echo gpio set 55;" \
					"echo Loaded environment from /uEnv.txt;" \
					"run importbootenv;" \
				"fi;" \
				"echo Checking if uenvcmd is set ...;" \
				"if test -n ${uenvcmd}; then " \
					"echo gpio set 56; " \
					"echo Running uenvcmd ...;" \
					"run uenvcmd;" \
				"fi;" \
				"echo Checking if client_ip is set ...;" \
				"if test -n ${client_ip}; then " \
					"if test -n ${dtb}; then " \
						"setenv fdtfile ${dtb};" \
						"echo using ${fdtfile} ...;" \
					"fi;" \
					"echo gpio set 56; " \
					"if test -n ${uname_r}; then " \
						"echo Running nfsboot_uname_r ...;" \
						"run nfsboot_uname_r;" \
					"fi;" \
					"echo Running nfsboot ...;" \
					"run nfsboot;" \
				"fi;" \
			"fi; " \
			"echo Checking for: /${script} ...;" \
			"if test -e ${devtype} ${bootpart} /${script}; then " \
				"echo gpio set 55;" \
				"setenv scriptfile ${script};" \
				"run loadbootscript;" \
				"echo Loaded script from ${scriptfile};" \
				"echo gpio set 56; " \
				"run bootscript;" \
			"fi; " \
			"echo Checking for: /boot/${script} ...;" \
			"if test -e ${devtype} ${bootpart} /boot/${script}; then " \
				"echo gpio set 55;" \
				"setenv scriptfile /boot/${script};" \
				"run loadbootscript;" \
				"echo Loaded script from ${scriptfile};" \
				"echo gpio set 56; " \
				"run bootscript;" \
			"fi; " \
			"echo Checking for: /boot/uEnv.txt ...;" \
			"for i in 1 2 3 4 5 6 7 ; do " \
				"setenv mmcpart ${i};" \
				"setenv bootpart ${mmcdev}:${mmcpart};" \
				"if test -e ${devtype} ${bootpart} /boot/uEnv.txt; then " \
					"echo gpio set 55;" \
					"load ${devtype} ${bootpart} ${loadaddr} /boot/uEnv.txt;" \
					"env import -t ${loadaddr} ${filesize};" \
					"echo Loaded environment from /boot/uEnv.txt;" \
					"echo testing DTB(${dtb});" \
					"if test -n ${dtb}; then " \
						"echo debug: [dtb=${dtb}] ... ;" \
						"setenv fdtfile ${dtb};" \
						"echo Using: dtb=${fdtfile} ...;" \
					"fi;" \
					"echo Checking if uname_r is set in /boot/uEnv.txt...;" \
					"if test -n ${uname_r}; then " \
						"echo gpio set 56; " \
						"setenv oldroot /dev/mmcblk${mmcdev}p${mmcpart};" \
						"echo Running uname_boot ...;" \
						"run uname_boot;" \
					"fi;" \
				"fi;" \
			"done;" \
		"fi;\0" \

// Adapted from EEWIKI_UNAME
#define EPNWIKI_UNAME_BOOT \
	"uname_boot="\
		"setenv bootdir /boot; " \
		"setenv bootfile vmlinuz-${uname_r}; " \
		"if test -e ${devtype} ${bootpart} ${bootdir}/${bootfile}; then " \
			"echo loading ${bootdir}/${bootfile} ...; "\
			"run loadimage;" \
			"echo setenv fdtdir /boot/dtbs/${uname_r} ...; "\
			"setenv fdtdir /boot/dtbs/${uname_r}; " \
			"echo debug: [enable_uboot_overlays=${enable_uboot_overlays}] ... ;" \
			"if test -n ${enable_uboot_overlays}; then " \
				"echo debug: [enable_uboot_cape_universal=${enable_uboot_cape_universal}] ... ;" \
				"if test -n ${enable_uboot_cape_universal}; then " \
					"echo debug: [uboot_base_dtb_univ=${uboot_base_dtb_univ}] ... ;" \
					"if test -n ${uboot_base_dtb_univ}; then " \
						"echo uboot_overlays: [uboot_base_dtb=${uboot_base_dtb_univ}] ... ;" \
						"if test -e ${devtype} ${bootpart} ${fdtdir}/${uboot_base_dtb_univ}; then " \
							"setenv fdtfile ${uboot_base_dtb_univ};" \
							"echo uboot_overlays: Switching too: dtb=${fdtfile} ...;" \
							"setenv cape_uboot bone_capemgr.uboot_capemgr_enabled=1; " \
						"else " \
							"echo debug: unable to find [${uboot_base_dtb_univ}] using [${uboot_base_dtb}] instead ... ;" \
							"echo debug: [uboot_base_dtb_univ=${uboot_base_dtb}] ... ;" \
							"if test -n ${uboot_base_dtb}; then " \
								"echo uboot_overlays: [uboot_base_dtb=${uboot_base_dtb}] ... ;" \
								"if test -e ${devtype} ${bootpart} ${fdtdir}/${uboot_base_dtb}; then " \
									"setenv fdtfile ${uboot_base_dtb};" \
									"echo uboot_overlays: Switching too: dtb=${fdtfile} ...;" \
								"fi;" \
							"fi;" \
						"fi;" \
					"fi;" \
				"else " \
					"echo debug: [uboot_base_dtb_univ=${uboot_base_dtb}] ... ;" \
					"if test -n ${uboot_base_dtb}; then " \
						"echo uboot_overlays: [uboot_base_dtb=${uboot_base_dtb}] ... ;" \
						"if test -e ${devtype} ${bootpart} ${fdtdir}/${uboot_base_dtb}; then " \
							"setenv fdtfile ${uboot_base_dtb};" \
							"echo uboot_overlays: Switching too: dtb=${fdtfile} ...;" \
						"fi;" \
					"fi;" \
				"fi;" \
			"fi;" \
			"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
				"echo run loadfdt ...;" \
				"run loadfdt;" \
			"else " \
				"setenv fdtdir /usr/lib/linux-image-${uname_r}; " \
				"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
					"run loadfdt;" \
				"else " \
					"setenv fdtdir /lib/firmware/${uname_r}/device-tree; " \
					"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
						"run loadfdt;" \
					"else " \
						"setenv fdtdir /boot/dtb-${uname_r}; " \
						"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
							"run loadfdt;" \
						"else " \
							"setenv fdtdir /boot/dtbs; " \
							"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
								"run loadfdt;" \
							"else " \
								"setenv fdtdir /boot/dtb; " \
								"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
									"run loadfdt;" \
								"else " \
									"setenv fdtdir /boot; " \
									"if test -e ${devtype} ${bootpart} ${fdtdir}/${fdtfile}; then " \
										"run loadfdt;" \
									"else " \
										"if test -e ${devtype} ${bootpart} ${fdtfile}; then " \
											"run loadfdt;" \
										"else " \
											"echo; echo unable to find [dtb=${fdtfile}] did you name it correctly? ...; " \
											"run failumsboot;" \
										"fi;" \
									"fi;" \
								"fi;" \
							"fi;" \
						"fi;" \
					"fi;" \
				"fi;" \
			"fi; " \
			"if test -n ${enable_uboot_overlays}; then " \
				"setenv fdt_buffer 0x60000;" \
				"if test -n ${uboot_fdt_buffer}; then " \
					"setenv fdt_buffer ${uboot_fdt_buffer};" \
				"fi;" \
				"echo uboot_overlays: [fdt_buffer=${fdt_buffer}] ... ;" \
				"if test -n ${uboot_silicon}; then " \
					"setenv uboot_overlay ${uboot_silicon}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_model}; then " \
					"setenv uboot_overlay ${uboot_model}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${disable_uboot_overlay_adc}; then " \
					"echo uboot_overlays: uboot loading of [BB-ADC-00A0.dtbo] disabled by /boot/uEnv.txt [disable_uboot_overlay_adc=1]...;" \
				"else " \
					"setenv uboot_overlay BB-ADC-00A0.dtbo; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr0}; then " \
					"if test -n ${disable_uboot_overlay_addr0}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_overlay_addr0}] disabled by /boot/uEnv.txt [disable_uboot_overlay_addr0=1]...;" \
					"else " \
						"setenv uboot_overlay ${uboot_overlay_addr0}; " \
						"run virtualloadoverlay;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr1}; then " \
					"if test -n ${disable_uboot_overlay_addr1}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_overlay_addr1}] disabled by /boot/uEnv.txt [disable_uboot_overlay_addr1=1]...;" \
					"else " \
						"setenv uboot_overlay ${uboot_overlay_addr1}; " \
						"run virtualloadoverlay;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr2}; then " \
					"if test -n ${disable_uboot_overlay_addr2}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_overlay_addr2}] disabled by /boot/uEnv.txt [disable_uboot_overlay_addr2=1]...;" \
					"else " \
						"setenv uboot_overlay ${uboot_overlay_addr2}; " \
						"run virtualloadoverlay;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr3}; then " \
					"if test -n ${disable_uboot_overlay_addr3}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_overlay_addr3}] disabled by /boot/uEnv.txt [disable_uboot_overlay_addr3=1]...;" \
					"else " \
						"setenv uboot_overlay ${uboot_overlay_addr3}; " \
						"run virtualloadoverlay;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr4}; then " \
					"setenv uboot_overlay ${uboot_overlay_addr4}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr5}; then " \
					"setenv uboot_overlay ${uboot_overlay_addr5}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr6}; then " \
					"setenv uboot_overlay ${uboot_overlay_addr6}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_overlay_addr7}; then " \
					"setenv uboot_overlay ${uboot_overlay_addr7}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_emmc}; then " \
					"if test -n ${disable_uboot_overlay_emmc}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_emmc}] disabled by /boot/uEnv.txt [disable_uboot_overlay_emmc=1]...;" \
					"else " \
						"setenv uboot_overlay ${uboot_emmc}; " \
						"run virtualloadoverlay;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_video}; then " \
					"if test -n ${disable_uboot_overlay_video}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_video}] disabled by /boot/uEnv.txt [disable_uboot_overlay_video=1]...;" \
					"else " \
						"if test -n ${disable_uboot_overlay_audio}; then " \
							"echo uboot_overlays: uboot loading of [${uboot_video}] disabled by /boot/uEnv.txt [disable_uboot_overlay_audio=1]...;" \
							"setenv uboot_overlay ${uboot_video_naudio}; " \
							"run virtualloadoverlay;" \
						"else " \
							"setenv uboot_overlay ${uboot_video}; " \
							"run virtualloadoverlay;" \
						"fi;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_wireless}; then " \
					"if test -n ${disable_uboot_overlay_wireless}; then " \
						"echo uboot_overlays: uboot loading of [${uboot_wireless}] disabled by /boot/uEnv.txt [disable_uboot_overlay_wireless=1]...;" \
					"else " \
						"setenv uboot_overlay ${uboot_wireless}; " \
						"run virtualloadoverlay;" \
					"fi;" \
				"fi;" \
				"if test -n ${uboot_overlay_pru}; then " \
					"setenv uboot_overlay ${uboot_overlay_pru}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_overlay_pru_add}; then " \
					"setenv uboot_overlay ${uboot_overlay_pru_add}; " \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${dtb_overlay}; then " \
					"setenv uboot_overlay ${dtb_overlay}; " \
					"echo uboot_overlays: [dtb_overlay=${uboot_overlay}] ... ;" \
					"run virtualloadoverlay;" \
				"fi;" \
				"if test -n ${uboot_detected_capes}; then " \
					"echo uboot_overlays: [uboot_detected_capes=${uboot_detected_capes_addr0}${uboot_detected_capes_addr1}${uboot_detected_capes_addr2}${uboot_detected_capes_addr3}] ... ;" \
					"setenv uboot_detected_capes uboot_detected_capes=${uboot_detected_capes_addr0}${uboot_detected_capes_addr1}${uboot_detected_capes_addr2}${uboot_detected_capes_addr3}; " \
				"fi;" \
			"else " \
				"echo uboot_overlays: add [enable_uboot_overlays=1] to /boot/uEnv.txt to enable...;" \
			"fi;" \
			"setenv rdfile initrd.img-${uname_r}; " \
			"if test -e ${devtype} ${bootpart} ${bootdir}/${rdfile}; then " \
				"echo loading ${bootdir}/${rdfile} ...; "\
				"run loadrd;" \
				"if test -n ${netinstall_enable}; then " \
					"run args_netinstall; run message;" \
					"echo debug: [${bootargs}] ... ;" \
					"echo debug: [bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}] ... ;" \
					"bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}; " \
				"fi;" \
				"if test -n ${uenv_root}; then " \
					"run args_uenv_root;" \
					"echo debug: [${bootargs}] ... ;" \
					"echo debug: [bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}] ... ;" \
					"bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}; " \
				"fi;" \
				"if test -n ${uuid}; then " \
					"run args_mmc_uuid;" \
					"echo debug: [${bootargs}] ... ;" \
					"echo debug: [bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}] ... ;" \
					"bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}; " \
				"fi;" \
				"run args_mmc_old;" \
				"echo debug: [${bootargs}] ... ;" \
				"echo debug: [bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}] ... ;" \
				"bootz ${loadaddr} ${rdaddr}:${rdsize} ${fdtaddr}; " \
			"else " \
				"if test -n ${uenv_root}; then " \
					"run args_uenv_root;" \
					"echo debug: [${bootargs}] ... ;" \
					"echo debug: [bootz ${loadaddr} - ${fdtaddr}] ... ;" \
					"bootz ${loadaddr} - ${fdtaddr}; " \
				"fi;" \
				"run args_mmc_old;" \
				"echo debug: [${bootargs}] ... ;" \
				"echo debug: [bootz ${loadaddr} - ${fdtaddr}] ... ;" \
				"bootz ${loadaddr} - ${fdtaddr}; " \
			"fi;" \
		"fi;\0" \



#define CONFIG_EXTRA_ENV_SETTINGS \
	DEFAULT_LINUX_BOOT_ENV \
	DEFAULT_MMC_TI_ARGS \
	DEFAULT_FIT_TI_ARGS \
	"bootpart=0:2\0" \
	"bootdir=/boot\0" \
	"bootfile=zImage\0" \
	"fdtfile=undefined\0" \
	"console=ttyO0,115200n8\0" \
	"optargs=earlyprintk\0" \
	"fdt_addr_r=0x88000000\0" \
	"fdtaddr=0x88000000\0" \
	"loadfdt=echo loading ${fdtdir}/${fdtfile} ...; " \
		"load ${devtype} ${bootpart} ${fdtaddr} ${fdtdir}/${fdtfile}\0" \
	"partitions=" \
		"uuid_disk=${uuid_gpt_disk};" \
		"name=bootloader,start=384K,size=1792K," \
			"uuid=${uuid_gpt_bootloader};" \
		"name=rootfs,start=2688K,size=-,uuid=${uuid_gpt_rootfs}\0" \
	"ramroot=/dev/ram0 rw\0" \
	"ramrootfstype=ext2\0" \
	"ramargs=setenv bootargs console=${console} " \
		"${optargs} " \
		"root=${ramroot} " \
		"rootfstype=${ramrootfstype}\0" \
	"loadrd=load mmc ${bootpart} ${rdaddr} " \
		"${bootdir}/${rdfile}; setenv rdsize ${filesize}\0" \
	"loadramdisk=load mmc ${mmcdev} ${rdaddr} ramdisk.gz\0" \
	"serverip=192.168.1.123\0" \
	"ipaddr=192.168.1.136\0" \
	"router=192.168.1.1\0" \
	"if_netconsole=ping $serverip\0" \
	"start_netconsole=" \
		"setenv ncip $serverip; " \
		"setenv bootdelay 10; " \
		"setenv stdin serial,nc; " \
		"setenv stdout serial,nc; " \
		"setenv stderr serial,nc; " \
		"version\0" \
	"preboot=run if_netconsole start_netconsole\0"\
	"ramboot=echo Booting from ramdisk ...; " \
		"run ramargs; " \
		"bootz ${loadaddr} ${rdaddr} ${fdt_addr}\0" \
	"findfdt="\
		"if test $board_name = EPN11291; then " \
			"setenv fdtfile epn11291.dtb; fi; " \
		"if test $board_name = A335BONE; then " \
			"setenv fdtfile am335x-bone.dtb; fi; " \
		"if test $board_name = A335BNLT; then " \
			"setenv fdtfile am335x-boneblack.dtb; fi; " \
		"if test $board_name = A335PBGL; then " \
			"setenv fdtfile am335x-pocketbeagle.dtb; fi; " \
		"if test $board_name = BBBW; then " \
			"setenv fdtfile am335x-boneblack-wireless.dtb; fi; " \
		"if test $board_name = BBG1; then " \
			"setenv fdtfile am335x-bonegreen.dtb; fi; " \
		"if test $board_name = BBGW; then " \
			"setenv fdtfile am335x-bonegreen-wireless.dtb; fi; " \
		"if test $board_name = BBBL; then " \
			"setenv fdtfile am335x-boneblue.dtb; fi; " \
		"if test $board_name = BBEN; then " \
			"setenv fdtfile am335x-sancloud-bbe.dtb; fi; " \
		"if test $board_name = A33515BB; then " \
			"setenv fdtfile am335x-evm.dtb; fi; " \
		"if test $board_name = A335X_SK; then " \
			"setenv fdtfile am335x-evmsk.dtb; fi; " \
		"if test $board_name = A335_ICE; then " \
			"setenv fdtfile am335x-icev2.dtb; fi; " \
		"if test $fdtfile = undefined; then " \
			"echo WARNING: Could not determine device tree to use; fi; \0" \
	"init_console= setenv console ${console}\0" \
	"loadoverlay= echo uboot_overlays: loading ${actual_uboot_overlay} ...; " \
		"load ${devtype} ${bootpart} ${rdaddr} ${actual_uboot_overlay}; " \
		"echo uboot_overlays: fdt addr ${fdtaddr}; " \
		"fdt addr ${fdtaddr}; " \
		"fdt resize ${fdt_buffer}; " \
		"fdt apply ${rdaddr}; " \
		"fdt resize ${fdt_buffer}\0" \
	"virtualloadoverlay=" \
		"if test -e ${devtype} ${bootpart} ${fdtdir}/overlays/${uboot_overlay}; then " \
			 "setenv actual_uboot_overlay ${fdtdir}/overlays/${uboot_overlay}; " \
			 "run loadoverlay; " \
		"else " \
			"if test -e ${devtype} ${bootpart} /lib/firmware/${uboot_overlay}; then " \
				"setenv actual_uboot_overlay /lib/firmware/${uboot_overlay}; " \
				"run loadoverlay; " \
			"else " \
				"if test -e ${devtype} ${bootpart} ${uboot_overlay}; then " \
					"setenv actual_uboot_overlay ${uboot_overlay}; " \
					"run loadoverlay; " \
				"else " \
					"echo uboot_overlays: unable to find [${devtype} ${bootpart} ${uboot_overlay}]...; " \
				"fi; " \
			"fi; " \
		"fi;\0" \
	"args_mmc_old=setenv bootargs console=${console} ${optargs} ${cape_uboot} root=${oldroot} " \
		"ro rootfstype=${mmcrootfstype} ${uboot_detected_capes} ${cmdline}\0" \
	EPNWIKI_NFS \
	EPNWIKI_BOOT \
	EPNWIKI_UNAME_BOOT \
	NETARGS \
	BOOTENV
#endif

/* NS16550 Configuration */
#define CONFIG_SYS_NS16550_COM1		0x44e09000	/* Base EVM has UART0 */

/* SPL */
#ifndef CONFIG_NOR_BOOT
/* Bootcount using the RTC block */
#define CONFIG_SYS_BOOTCOUNT_BE
//CONFIG_SYS_NS16550_COM1
/* USB gadget RNDIS */
#endif


/*
 * Disable MMC DM for SPL build and can be re-enabled after adding
 * DM support in SPL
 */
#ifdef CONFIG_SPL_BUILD
#undef CONFIG_DM_MMC
#undef CONFIG_TIMER
#endif

#if defined(CONFIG_SPL_BUILD) && defined(CONFIG_SPL_USB_ETHER)
/* Remove other SPL modes. */
/* disable host part of MUSB in SPL */
/* disable EFI partitions and partition UUID support */
#endif

/*
 * Default to using SPI for environment, etc.
 * 0x000000 - 0x020000 : SPL (128KiB)
 * 0x020000 - 0x0A0000 : U-Boot (512KiB)
 * 0x0A0000 - 0x0BFFFF : First copy of U-Boot Environment (128KiB)
 * 0x0C0000 - 0x0DFFFF : Second copy of U-Boot Environment (128KiB)
 * 0x0E0000 - 0x442000 : Linux Kernel
 * 0x442000 - 0x800000 : Userland
 */
#if defined(CONFIG_EMMC_BOOT)
#define CONFIG_SYS_MMC_ENV_DEV		1
#define CONFIG_SYS_MMC_ENV_PART		0
#define CONFIG_ENV_OFFSET		0x260000
#define CONFIG_ENV_OFFSET_REDUND	(CONFIG_ENV_OFFSET + CONFIG_ENV_SIZE)
#define CONFIG_SYS_REDUNDAND_ENVIRONMENT
#define CONFIG_SYS_MMC_MAX_DEVICE	2
#endif

#ifdef CONFIG_DRIVER_TI_CPSW
#define CONFIG_CLOCK_SYNTHESIZER
#define CLK_SYNTHESIZER_I2C_ADDR 0x65
#endif

#endif	/* ! __CONFIG_AM335X_EVM_H */
