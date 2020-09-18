/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * board.h
 *
 * Flight Circuits AM335x boards information header
 *
 * Copyright (C) 2020, Flight Circuits, LLC <www.flightcircuits.com>
 * Copyright (C) 2020, Flight Circuits <adam@flightcircuits.com>
 */

#ifndef _BOARD_H_
#define _BOARD_H_

//DEFINE GPIOs
#define GPIO_TO_PIN(bank, gpio)		(32 * (bank) + (gpio))
#define GPIO_STRAP0		GPIO_TO_PIN(1, 16)
#define GPIO_STRAP1		GPIO_TO_PIN(1, 17)
#define GPIO_STRAP2		GPIO_TO_PIN(1, 18)
#define GPIO_STRAP3		GPIO_TO_PIN(1, 19)
#define GPIO_eMMC_RSTn		GPIO_TO_PIN(2, 2)

//DEFINE BOARDS
#define BOARD_EPN11291 0

#define EMIF_OCP_CONFIG_EPN11291       0x00141414

void enable_strap_pin_mux(void);
void enable_uart0_pin_mux(void);
void enable_board_pin_mux(void);
int board_detect(void);

#endif
