/*
 * mux.c
 *
 * Copyright (C) 2020, Flight Circuits <adam@flightcircuits.com>
 */

#include <common.h>
#include <asm/arch/sys_proto.h>
#include <asm/arch/hardware.h>
#include <asm/arch/mux.h>
#include <asm/arch/gpio.h>
#include <asm-generic/gpio.h>
#include <asm/io.h>
#include <i2c.h>
#include "board.h"

//Set up the GPIOs for board detection
static struct module_pin_mux strap_pin_mux[] = {
	{OFFSET(gpmc_a0), (MODE(7) | PULLUDDIS | RXACTIVE)},	//STRAP_0
	{OFFSET(gpmc_a1), (MODE(7) | PULLUDDIS | RXACTIVE)},	//STRAP_1
	{OFFSET(gpmc_a2), (MODE(7) | PULLUDDIS | RXACTIVE)},	//STRAP_2
	{OFFSET(gpmc_a3), (MODE(7) | PULLUDDIS | RXACTIVE)},	//STRAP_3
	{-1},
};

//Set up the DEBUG UART
static struct module_pin_mux uart0_pin_mux[] = {
	{OFFSET(uart0_rxd), (MODE(0) | PULLUP_EN | RXACTIVE)},	//DEBUG_RX
	{OFFSET(uart0_txd), (MODE(0) | PULLUDEN)},		//DEBUG_TX
	{-1},
};

//Set up the BLE UART
static struct module_pin_mux uart1_pin_mux[] = {
	{OFFSET(uart1_rxd), (MODE(0) | PULLUP_EN | RXACTIVE)},	//HCI_RX
	{OFFSET(uart1_txd), (MODE(0) | PULLUDEN)},		//HCI_TX
	{OFFSET(uart1_ctsn), (MODE(0) | PULLUDDIS | RXACTIVE)},	//HCI_CTS
	{OFFSET(uart1_rtsn), (MODE(0) | PULLUDDIS)},		//HCI_RTS
	{-1},
};

//Set up the SD Card
static struct module_pin_mux mmc0_pin_mux[] = {
	{OFFSET(mmc0_dat3), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT3 */
	{OFFSET(mmc0_dat2), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT2 */
	{OFFSET(mmc0_dat1), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT1 */
	{OFFSET(mmc0_dat0), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_DAT0 */
	{OFFSET(mmc0_clk), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_CLK */
	{OFFSET(mmc0_cmd), (MODE(0) | RXACTIVE | PULLUP_EN)},	/* MMC0_CMD */
	{OFFSET(gpmc_a11), (MODE(5) | RXACTIVE | PULLUP_EN)},	/* MMC0_CD */
	{-1},
};


//Set up the eMMC
static struct module_pin_mux mmc1_pin_mux[] = {
	{OFFSET(gpmc_ad7), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D7
	{OFFSET(gpmc_ad6), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D6
	{OFFSET(gpmc_ad5), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D5
	{OFFSET(gpmc_ad4), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D4
	{OFFSET(gpmc_ad3), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D3
	{OFFSET(gpmc_ad2), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D2
	{OFFSET(gpmc_ad1), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D1
	{OFFSET(gpmc_ad0), (MODE(1) | RXACTIVE | PULLUP_EN)},	//eMMC_D0
	{OFFSET(gpmc_csn1), (MODE(2) | RXACTIVE | PULLUP_EN)},	//eMMC_CLK
	{OFFSET(gpmc_csn2), (MODE(2) | RXACTIVE | PULLUP_EN)},	//eMMC_CMD
	{OFFSET(gpmc_advn_ale), (MODE(7) | PULLUDDIS)}, 	//eMMC1_RSTn
	{-1},
};

//Set up RGMII
static struct module_pin_mux rgmii1_pin_mux[] = {
	{OFFSET(mii1_txen), MODE(2)},				//RGMII1_TCTL
	{OFFSET(mii1_rxdv), MODE(2) | RXACTIVE},		//RGMII1_RCTL
	{OFFSET(mii1_txd3), MODE(2)},				//RGMII1_TD3
	{OFFSET(mii1_txd2), MODE(2)},				//RGMII1_TD2
	{OFFSET(mii1_txd1), MODE(2)},				//RGMII1_TD1
	{OFFSET(mii1_txd0), MODE(2)},				//RGMII1_TD0
	{OFFSET(mii1_txclk), MODE(2)},				//RGMII1_TCLK
	{OFFSET(mii1_rxclk), MODE(2) | RXACTIVE},		//RGMII1_RCLK
	{OFFSET(mii1_rxd3), MODE(2) | RXACTIVE},		//RGMII1_RD3
	{OFFSET(mii1_rxd2), MODE(2) | RXACTIVE},		//RGMII1_RD2
	{OFFSET(mii1_rxd1), MODE(2) | RXACTIVE},		//RGMII1_RD1
	{OFFSET(mii1_rxd0), MODE(2) | RXACTIVE},		//RGMII1_RD0
	{OFFSET(mdio_data), MODE(0) | RXACTIVE | PULLUP_EN},	//MDIO
	{OFFSET(mdio_clk), MODE(0) | PULLUP_EN},		//MDCLK
	{-1},
};

void enable_strap_pin_mux(void){
	// while (true); // this is not being called
	configure_module_pin_mux(strap_pin_mux);
}

void enable_uart0_pin_mux(void){
	// while (true); // this is not being called
	configure_module_pin_mux(uart0_pin_mux);
}

int board_detect(void)
{
	// while (true); // this is not being called
	int board;
	enable_strap_pin_mux();
	board = ((GPIO_STRAP3 << 3) + (GPIO_STRAP2 << 2) + (GPIO_STRAP1 << 1) + GPIO_STRAP0);
	return board;
}

//int gpio_request(unsigned gpio, const char *label);
//int gpio_direction_output(unsigned gpio, int value);
//int gpio_set_value(unsigned gpio, int value);


void enable_board_pin_mux(void){
	// while (true); // this is being called

	//EPN11291 Mux
	configure_module_pin_mux(uart1_pin_mux);
	configure_module_pin_mux(mmc0_pin_mux);
	configure_module_pin_mux(mmc1_pin_mux);

	//set eMMC_RSTn high
	gpio_request(GPIO_eMMC_RSTn, "eMMC_RSTn");
	gpio_direction_output(GPIO_eMMC_RSTn, 0);
	gpio_set_value(GPIO_eMMC_RSTn, 1);

	// while (true); // we get here

	configure_module_pin_mux(rgmii1_pin_mux);

	// while (true); // we get here
}
