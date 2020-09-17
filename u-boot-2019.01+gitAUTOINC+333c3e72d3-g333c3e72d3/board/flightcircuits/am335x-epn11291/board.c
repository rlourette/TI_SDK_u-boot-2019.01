// SPDX-License-Identifier: GPL-2.0+
/*
 * board.c
 *
 * Board functions for Flight Circuits TI AM335X based boards
 *
 * Copyright (C) 2011, Texas Instruments, Incorporated - http://www.ti.com/
 * Copyright (C) 2020, Flight Circuits, Inc - http://flightcircuits.com
 */

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <spl.h>
#include <serial.h>
#include <asm/arch/cpu.h>
#include <asm/arch/hardware.h>
#include <asm/arch/omap.h>
#include <asm/arch/ddr_defs.h>
#include <asm/arch/clock.h>
#include <asm/arch/clk_synthesizer.h>
#include <asm/arch/gpio.h>
#include <asm/arch/mmc_host_def.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/mem.h>
#include <asm/io.h>
#include <asm/emif.h>
#include <asm/gpio.h>
#include <asm/omap_common.h>
#include <asm/omap_sec_common.h>
#include <asm/omap_mmc.h>
#include <i2c.h>
#include <miiphy.h>
#include <cpsw.h>
#include <power/tps65217.h>
#include <power/tps65910.h>
#include <environment.h>
#include <watchdog.h>
#include <environment.h>
#include "board.h"

DECLARE_GLOBAL_DATA_PTR;

static struct ctrl_dev *cdev = (struct ctrl_dev *)CTRL_DEVICE_BASE;

#define GPIO0_RISINGDETECT	(AM33XX_GPIO0_BASE + OMAP_GPIO_RISINGDETECT)
#define GPIO1_RISINGDETECT	(AM33XX_GPIO1_BASE + OMAP_GPIO_RISINGDETECT)

#define GPIO0_IRQSTATUS1	(AM33XX_GPIO0_BASE + OMAP_GPIO_IRQSTATUS1)
#define GPIO1_IRQSTATUS1	(AM33XX_GPIO1_BASE + OMAP_GPIO_IRQSTATUS1)

#define GPIO0_IRQSTATUSRAW	(AM33XX_GPIO0_BASE + 0x024)
#define GPIO1_IRQSTATUSRAW	(AM33XX_GPIO1_BASE + 0x024)

#ifndef CONFIG_DM_SERIAL
struct serial_device *default_serial_console(void)
{
	return &eserial1_device;
}
#endif

#ifndef CONFIG_SKIP_LOWLEVEL_INIT
static const struct ddr_data ddr3_epn11291_data = {
	.datardsratio0 = MT41K256M16HA125E_RD_DQS,
	.datawdsratio0 = MT41K256M16HA125E_WR_DQS,
	.datafwsratio0 = MT41K256M16HA125E_PHY_FIFO_WE,
	.datawrsratio0 = MT41K256M16HA125E_PHY_WR_DATA,
};

static const struct cmd_control ddr3_epn11291_cmd_ctrl_data = {
	.cmd0csratio = MT41K256M16HA125E_RATIO,
	.cmd0iclkout = MT41K256M16HA125E_INVERT_CLKOUT,

	.cmd1csratio = MT41K256M16HA125E_RATIO,
	.cmd1iclkout = MT41K256M16HA125E_INVERT_CLKOUT,

	.cmd2csratio = MT41K256M16HA125E_RATIO,
	.cmd2iclkout = MT41K256M16HA125E_INVERT_CLKOUT,
};

static struct emif_regs ddr3_epn11291_emif_reg_data = {
	.sdram_config = MT41K256M16HA125E_EMIF_SDCFG,
	.ref_ctrl = MT41K256M16HA125E_EMIF_SDREF,
	.sdram_tim1 = MT41K256M16HA125E_EMIF_TIM1,
	.sdram_tim2 = MT41K256M16HA125E_EMIF_TIM2,
	.sdram_tim3 = MT41K256M16HA125E_EMIF_TIM3,
	.ocp_config = EMIF_OCP_CONFIG_EPN11291,
	.zq_config = MT41K256M16HA125E_ZQ_CFG,
	.emif_ddr_phy_ctlr_1 = MT41K256M16HA125E_EMIF_READ_LATENCY,
};

void am33xx_spl_board_init(void)
{
	// puts("[debug] am33xx_spl_board_init(): entry\n");

	// while(true); // we don't get here
}

#ifdef CONFIG_SPL_OS_BOOT
int spl_start_uboot(void)
{
#ifdef CONFIG_SPL_SERIAL_SUPPORT
	/* break into full u-boot on 'c' */
	if (serial_tstc() && serial_getc() == 'c')
		return 1;
#endif

#ifdef CONFIG_SPL_ENV_SUPPORT
	env_init();
	env_load();
	if (env_get_yesno("boot_os") != 1)
		return 1;
#endif

	return 0;
}
#endif


const struct dpll_params *get_dpll_ddr_params(void)
{
	// this is compiled in for SPL foo1
	// while (true); // This is getting called
	int ind = get_sys_clk_index();

	// while (true); // this is getting called

	return &dpll_ddr3_400MHz[ind];

}

const struct dpll_params *get_dpll_mpu_params(void)
{
	// this is complied in for SPL foo2
	// while (true); // This is getting called

	int ind = get_sys_clk_index();
	int freq = am335x_get_efuse_mpu_max_freq(cdev);
	// while (true); // this is getting called

	switch (freq) {
	case MPUPLL_M_1000:
		return &dpll_mpu_opp[ind][5];
	case MPUPLL_M_800:
		return &dpll_mpu_opp[ind][4];
	case MPUPLL_M_720:
		return &dpll_mpu_opp[ind][3];
	case MPUPLL_M_600:
		return &dpll_mpu_opp[ind][2];
	case MPUPLL_M_500:
		return &dpll_mpu_opp100;
	case MPUPLL_M_300:
		return &dpll_mpu_opp[ind][0];
	}
	// while (true); // this is not getting called

	return &dpll_mpu_opp[ind][0];
}




void gpi2c_init(void)
{
	/* When needed to be invoked prior to BSS initialization */
	static bool first_time = true;

	if (first_time) {
		enable_i2c0_pin_mux();
#ifndef CONFIG_DM_I2C
		i2c_init(CONFIG_SYS_OMAP24_I2C_SPEED,
			 CONFIG_SYS_OMAP24_I2C_SLAVE);
#endif
		first_time = false;
	}
}

void set_uart_mux_conf(void)
{
	// this is compiled in for SPL foobar
	// while (true); // This is getting called
	// puts("[debug] set_uart_mux_conf(void) entry.\n");

	enable_uart0_pin_mux();

	//enable_uart0_pin_mux(); // XXXTODO added back rwl
}

void set_mux_conf_regs(void)
{
	enable_board_pin_mux();
}

const struct ctrl_ioregs ioregs_epn11291 = {
	.cm0ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.cm1ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.cm2ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.dt0ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
	.dt1ioctl		= MT41K256M16HA125E_IOCTRL_VALUE,
};

void sdram_init(void)
{
	// puts("[debug] sdram_init()\n");
	// this is complied in for SPL foo
	extern void console_init_f(void);
	// console_init_f();


	// while (true); // this is getting called

	config_ddr(400, &ioregs_epn11291,
			   &ddr3_epn11291_data,
			   &ddr3_epn11291_cmd_ctrl_data,
			   &ddr3_epn11291_emif_reg_data, 0);

	// while (true); // this is getting called
}
#endif

#if defined(CONFIG_OF_BOARD_SETUP) && defined(CONFIG_OF_CONTROL) && \
	defined(CONFIG_DM_ETH) && defined(CONFIG_DRIVER_TI_CPSW)

#define MAX_CPSW_SLAVES	2

/* At the moment, we do not want to stop booting for any failures here */
int ft_board_setup(void *fdt, bd_t *bd)
{
	// while (true); // this is not getting called
	return 0;
}

#endif

/*
 * Basic board specific setup.  Pinmux has been handled already.
 */
int board_init(void)
{
	// this is being compiled in foobar
	// while (true); This is not being called when the failure occurs

	// puts("[debug] board_init(void) entry.\n");

	u32 sys_reboot;

	sys_reboot = readl(PRM_RSTST);
	if (sys_reboot & (1 << 9))
		puts("Reset Source: IcePick reset has occurred.\n");

	if (sys_reboot & (1 << 5))
		puts("Reset Source: Global external warm reset has occurred.\n");

	if (sys_reboot & (1 << 4))
		puts("Reset Source: watchdog reset has occurred.\n");

	if (sys_reboot & (1 << 1))
		puts("Reset Source: Global warm SW reset has occurred.\n");

	if (sys_reboot & (1 << 0))
		puts("Reset Source: Power-on reset has occurred.\n");


	gd->bd->bi_boot_params = CONFIG_SYS_SDRAM_BASE + 0x100;


	return 0;
}

#ifdef CONFIG_BOARD_LATE_INIT
int board_late_init(void)
{
#if !defined(CONFIG_SPL_BUILD)
	uint8_t mac_addr[6];
	uint32_t mac_hi, mac_lo;
#endif

	puts("[debug] board_late_init(): entry\n");

#ifdef CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG
	char *name = NULL;


	puts("Board: CTC EPN11291\n");
	name = "EPN11291";


	env_set("board_name", name);

	/*
	 * Default FIT boot on HS devices. Non FIT images are not allowed
	 * on HS devices.
	 */
	if (get_device_type() == HS_DEVICE)
		env_set("boot_fit", "1");

#endif

#if !defined(CONFIG_SPL_BUILD)
	/* try reading mac address from efuse */
	mac_lo = readl(&cdev->macid0l);
	mac_hi = readl(&cdev->macid0h);
	mac_addr[0] = mac_hi & 0xFF;
	mac_addr[1] = (mac_hi & 0xFF00) >> 8;
	mac_addr[2] = (mac_hi & 0xFF0000) >> 16;
	mac_addr[3] = (mac_hi & 0xFF000000) >> 24;
	mac_addr[4] = mac_lo & 0xFF;
	mac_addr[5] = (mac_lo & 0xFF00) >> 8;

	if (!env_get("ethaddr")) {
		printf("<ethaddr> not set. Validating first E-fuse MAC\n");

		if (is_valid_ethaddr(mac_addr))
			eth_env_set_enetaddr("ethaddr", mac_addr);
	}

	mac_lo = readl(&cdev->macid1l);
	mac_hi = readl(&cdev->macid1h);
	mac_addr[0] = mac_hi & 0xFF;
	mac_addr[1] = (mac_hi & 0xFF00) >> 8;
	mac_addr[2] = (mac_hi & 0xFF0000) >> 16;
	mac_addr[3] = (mac_hi & 0xFF000000) >> 24;
	mac_addr[4] = mac_lo & 0xFF;
	mac_addr[5] = (mac_lo & 0xFF00) >> 8;

	if (!env_get("eth1addr")) {
		if (is_valid_ethaddr(mac_addr))
			eth_env_set_enetaddr("eth1addr", mac_addr);
	}

	printf("MAC: %x:%x:%x:%x:%x:%x\n",mac_addr[0],mac_addr[1],mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
#endif

	if (!env_get("serial#")) {
		char *board_serial = env_get("board_serial");
		char *ethaddr = env_get("ethaddr");

		if (!board_serial || !strncmp(board_serial, "unknown", 7))
			env_set("serial#", ethaddr);
		else
			env_set("serial#", board_serial);
	}

	return 0;
}
#endif

/* CPSW platdata */
#if (defined(CONFIG_DRIVER_TI_CPSW) && !defined(CONFIG_SPL_BUILD)) || \
	(defined(CONFIG_SPL_ETH_SUPPORT) && defined(CONFIG_SPL_BUILD))
struct cpsw_slave_data cpsw_slaves[] = {
	{
	.slave_reg_ofs  = CPSW_SLAVE0_OFFSET,
	.sliver_reg_ofs = CPSW_SLIVER0_OFFSET,
	.phy_addr       = 0,
	}
};

struct cpsw_platform_data am335_eth_data = {
	.mdio_base		= 0x4a101000,
	.cpsw_base		= CPSW_BASE,
	//.mac_id
	.gmii_sel		= 0x44e10650,
	.mdio_div		= CPSW_MDIO_DIV,
	.channels		= 8,
	.cpdma_reg_ofs	= CPSW_CPDMA_OFFSET,
	.slaves			= 2,
	.ale_reg_ofs	= CPSW_ALE_OFFSET,
	.ale_entries	= 1024,
	.host_port_reg_ofs	= CPSW_HOST_PORT_OFFSET,
	//.hw_stats_reg_ofs
	.bd_ram_ofs		= CPSW_BD_OFFSET,
	//.bd_ram_ofs		= 0x2000,
	.mac_control	= 0x20,
	.slave_data		= cpsw_slaves,
	// void	(*control)(int enabled); // control - pointer to function takes int returns void
	// .host_port_num		= 0,
	.active_slave	= 0,
	// .rmii_clock_external;
	.version		= CPSW_CTRL_VERSION_2,
	.phy_sel_compat	= "ti,am3352-cpsw-phy-sel",
	.syscon_addr	= 0x44e10630,
	.macid_sel_compat= "cpsw,am33xx",
};
#ifdef CONFIG_DM_ETH
struct eth_pdata cpsw_pdata = {
	.iobase = 0x4a100000,
	.phy_interface = 0,
	.priv_pdata = &am335_eth_data,
};

U_BOOT_DEVICE(am335x_eth) = {
	.name = "eth_cpsw",
	.platdata = &cpsw_pdata,
};
#endif
#endif

#ifdef CONFIG_SPL_LOAD_FIT
int board_fit_config_name_match(const char *name)
{
	//FIME: we currently dont use this, yet...
	if (!strcmp(name, "epn11291"))
		return 0;
	else
		return -1;
}
#endif

#ifdef CONFIG_TI_SECURE_DEVICE
void board_fit_image_post_process(void **p_image, size_t *p_size)
{
	secure_boot_verify_image(p_image, p_size);
}
#endif

#if !CONFIG_IS_ENABLED(OF_CONTROL)
static const struct omap_hsmmc_plat am335x_mmc0_platdata = {
	.base_addr = (struct hsmmc *)OMAP_HSMMC1_BASE,
	.cfg.host_caps = MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_4BIT,
	.cfg.f_min = 400000,
	.cfg.f_max = 52000000,
	.cfg.voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195,
	.cfg.b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT,
};

U_BOOT_DEVICE(am335x_mmc0) = {
	.name = "omap_hsmmc",
	.platdata = &am335x_mmc0_platdata,
};

static const struct omap_hsmmc_plat am335x_mmc1_platdata = {
	.base_addr = (struct hsmmc *)OMAP_HSMMC2_BASE,
	.cfg.host_caps = MMC_MODE_HS_52MHz | MMC_MODE_HS | MMC_MODE_8BIT,
	.cfg.f_min = 400000,
	.cfg.f_max = 52000000,
	.cfg.voltages = MMC_VDD_32_33 | MMC_VDD_33_34 | MMC_VDD_165_195,
	.cfg.b_max = CONFIG_SYS_MMC_MAX_BLK_COUNT,
};

U_BOOT_DEVICE(am335x_mmc1) = {
	.name = "omap_hsmmc",
	.platdata = &am335x_mmc1_platdata,
};
#endif
