////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./board.h
// {{{
// Project:	10Gb Ethernet switch
//
// DO NOT EDIT THIS FILE!
// Computer Generated: This file is computer generated by AUTOFPGA. DO NOT EDIT.
// DO NOT EDIT THIS FILE!
//
// CmdLine:	autofpga -I .: -d -o . allclocks.txt global.txt wbdown.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt smiconsole.txt bkram.txt flash.txt sdspi.txt mem_bkram_only.txt mem_flash_bkram.txt mem_bootrom_bkram.txt mem_sdram_only.txt i2ccpu.txt fan.txt sirefclk.txt
//
// Creator:	Dan Gisselquist, Ph.D.
//		Gisselquist Technology, LLC
//
////////////////////////////////////////////////////////////////////////////////
// }}}
// Copyright (C) 2023, Gisselquist Technology, LLC
// {{{
// This file is part of the ETH10G project.
//
// The ETH10G project contains free software and gateware, licensed under the
// Apache License, Version 2.0 (the "License").  You may not use this project,
// or this file, except in compliance with the License.  You may obtain a copy
// of the License at
// }}}
//	http://www.apache.org/licenses/LICENSE-2.0
// {{{
// Unless required by applicable law or agreed to in writing, files
// distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
// WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
// License for the specific language governing permissions and limitations
// under the License.
//
////////////////////////////////////////////////////////////////////////////////
//
// }}}
#ifndef	BOARD_H
#define	BOARD_H

// And, so that we can know what is and isn't defined
// from within our main.v file, let's include:
#include <design.h>

////////////////////////////////////////////////////////////////////////////////
//
// ZipCPU defines and macros
// {{{
#include <design.h>

#define	_HAVE_ZIPSYS
#define	PIC	_zip->z_pic

#ifdef	INCLUDE_ZIPCPU
#ifdef INCLUDE_DMA_CONTROLLER
#define	_HAVE_ZIPSYS_DMA
#endif	// INCLUDE_DMA_CONTROLLER
#ifdef INCLUDE_ACCOUNTING_COUNTERS
#define	_HAVE_ZIPSYS_PERFORMANCE_COUNTERS
#endif	// INCLUDE_ACCOUNTING_COUNTERS
#endif // INCLUDE_ZIPCPU
// }}}


#define	SYSPIC(A)	(1<<(A))


#ifndef	FAN_H
#define	FAN_H
	////////////////////////////////////////////////////////////////////////
	//
	// I2C CPU data structures
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//
typedef struct  FAN_S        {
	unsigned	fan_fpgapwm, fan_syspwm, fan_tach;
	int		fan_temp;
	unsigned	temp_control, temp_override, temp_address,
			temp_clkcount;
} FAN;

#endif	// FAN_H
	// }}}


#ifndef	I2CCPU_H
#define	I2CCPU_H
	////////////////////////////////////////////////////////////////////////
	//
	// I2C CPU data structures
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//
typedef struct  I2CCPU_S        {
	unsigned	ic_control, ic_override, ic_address, ic_clkcount;
} I2CCPU;

#endif	// I2CCPU_H
	// }}}


#define	ALTPIC(A)	(1<<(A))


////////////////////////////////////////////////////////////////////////////////
//
// SD SPI constants
// {{{
////////////////////////////////////////////////////////////////////////////////
//
//

#define	SDSPI_SETAUX	0x0000ff
#define	SDSPI_READAUX	0x0000bf
#define	SDSPI_CMD		0x000040
#define	SDSPI_ACMD		(0x040+55) // CMD55
#define	SDSPI_FIFO_OP	0x000800	// Read only
#define	SDSPI_WRITEOP	0x000c00	// Write to the FIFO
#define	SDSPI_ALTFIFO	0x001000
#define	SDSPI_BUSY		0x004000
#define	SDSPI_ERROR		0x008000
#define	SDSPI_CLEARERR	0x008000
// #define	SDSPI_CRCERR	0x010000
// #define	SDSPI_ERRTOK	0x020000
#define	SDSPI_REMOVED	0x040000
#define	SDSPI_PRESENTN	0x080000
#define	SDSPI_RESET		0x100000	// Read only
#define	SDSPI_WATCHDOG	0x200000	// Read only
#define	SDSPI_GO_IDLE	((SDSPI_REMOVED|SDSPI_CLEARERR|SDSPI_CMD)+0)
#define	SDSPI_READ_SECTOR	((SDSPI_CMD|SDSPI_CLEARERR|SDSPI_FIFO_OP)+17)
#define	SDSPI_WRITE_SECTOR	((SDSPI_CMD|SDSPI_CLEARERR|SDSPI_WRITEOP)+24)

typedef	struct SDSPI_S {
	unsigned	sd_ctrl, sd_data, sd_fifo[2];
} SDSPI;
// }}}


typedef struct  CONSOLE_S {
	unsigned	u_setup;
	unsigned	u_fifo;
	unsigned	u_rx, u_tx;
} CONSOLE;

#define	_uart_txbusy	((_uart->u_fifo & 0x10000)==0)
#define	_uart_txidle	((_uart->u_tx   & 0x100)  ==0)


//
// GPIO input wires
//
#define	GPIO_SOFT_RESET		0x000010000
#define	GPIO_PI_RESET		0x000020000
#define	GPIO_SYSCLK_LOCKED	0x000040000
#define	GPIO_SI_INT		0x000080000
//
// GPIO output wires
//
#define	GPIO_SET(WIRE)	(((WIRE)<<16)|(WIRE))
#define	GPIO_CLR(WIRE)	 ((WIRE)<<16)
//
#define	GPIO_TP0		0x000000001
#define	GPIO_TP1		0x000000002
#define	GPIO_TP2		0x000000004
#define	GPIO_TP3		0x000000008
#define	GPIO_SIRESET		0x000000010
//
#define	GPIO_TP0_SET	GPIO_SET(GPIO_TP0)
#define	GPIO_TP0_CLR	GPIO_CLR(GPIO_TP0)
#define	GPIO_TP1_SET	GPIO_SET(GPIO_TP1)
#define	GPIO_TP1_CLR	GPIO_CLR(GPIO_TP1)
#define	GPIO_TP2_SET	GPIO_SET(GPIO_TP2)
#define	GPIO_TP2_CLR	GPIO_CLR(GPIO_TP2)
#define	GPIO_TP3_SET	GPIO_SET(GPIO_TP3)
#define	GPIO_TP3_CLR	GPIO_CLR(GPIO_TP3)
#define	GPIO_SIRESET_SET	GPIO_SET(GPIO_SIRESET)
#define	GPIO_SIRESET_CLR	GPIO_CLR(GPIO_SIRESET)


#define	SPIO_BTNC	0x01000
#define	SPIO_BTND	0x00800
#define	SPIO_BTNL	0x00400
#define	SPIO_BTNR	0x00200
#define	SPIO_BTNU	0x00100


#ifdef	BKRAM_ACCESS
#define	_BOARD_HAS_BKRAM
extern char	_bkram[0x00040000];
#endif	// BKRAM_ACCESS
#ifdef	FAN_ACCESS
#define	_BOARD_HAS_FAN
static volatile FAN *const _fan=((FAN *)0x00800040);
#endif	// FAN_ACCESS
#ifdef	I2CCPU_ACCESS
#define	_BOARD_HAS_I2CCPU
static volatile I2CCPU *const _i2c=((I2CCPU *)0x00800010);
#endif	// I2CCPU_ACCESS
#ifdef	FLASH_ACCESS
#define	_BOARD_HAS_FLASH
extern int _flash[1];
#endif	// FLASH_ACCESS
#ifdef	SDSPI_ACCESS
#define	_BOARD_HAS_SDSPI
static volatile SDSPI *const _sdcard = ((SDSPI *)0x00800020);
#endif	// SDSPI_ACCESS
#define	_BOARD_HAS_BUILDTIME
static volatile unsigned *const _buildtime = ((unsigned *)0x00800060);
#ifdef	BUSCONSOLE_ACCESS
#define	_BOARD_HAS_BUSCONSOLE
static volatile CONSOLE *const _uart = ((CONSOLE *)0x00800030);
#endif	// BUSCONSOLE_ACCESS
#ifdef	VERSION_ACCESS
#define	_BOARD_HAS_VERSION
static volatile unsigned *const _version = ((unsigned *)0x00800070);
#endif	// VERSION_ACCESS
#ifdef	FLASHCFG_ACCESS
#define	_BOARD_HAS_FLASHCFG
static volatile unsigned * const _flashcfg = ((unsigned *)(0x00800000));
#endif	// FLASHCFG_ACCESS
#ifdef	GPIO_ACCESS
#define	_BOARD_HAS_GPIO
static volatile unsigned *const _gpio = ((unsigned *)0x00800064);
#endif	// GPIO_ACCESS
#ifdef	SPIO_ACCESS
#define	_BOARD_HAS_SPIO
static volatile unsigned *const _spio = ((unsigned *)0x0080006c);
#endif	// SPIO_ACCESS
//
// Interrupt assignments (2 PICs)
//
// PIC: syspic
#define	SYSPIC_DMAC	SYSPIC(0)
#define	SYSPIC_JIFFIES	SYSPIC(1)
#define	SYSPIC_TMC	SYSPIC(2)
#define	SYSPIC_TMB	SYSPIC(3)
#define	SYSPIC_TMA	SYSPIC(4)
#define	SYSPIC_ALT	SYSPIC(5)
#define	SYSPIC_SDCARD	SYSPIC(6)
#define	SYSPIC_UARTRXF	SYSPIC(7)
#define	SYSPIC_UARTTXF	SYSPIC(8)
#define	SYSPIC_SPIO	SYSPIC(9)
// PIC: altpic
#define	ALTPIC_UIC	ALTPIC(0)
#define	ALTPIC_UOC	ALTPIC(1)
#define	ALTPIC_UPC	ALTPIC(2)
#define	ALTPIC_UTC	ALTPIC(3)
#define	ALTPIC_MIC	ALTPIC(4)
#define	ALTPIC_MOC	ALTPIC(5)
#define	ALTPIC_MPC	ALTPIC(6)
#define	ALTPIC_MTC	ALTPIC(7)
#define	ALTPIC_UARTTX	ALTPIC(8)
#define	ALTPIC_UARTRX	ALTPIC(9)
#define	ALTPIC_GPIO	ALTPIC(10)
#endif	// BOARD_H