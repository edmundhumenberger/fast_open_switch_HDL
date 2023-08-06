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
// CmdLine:	autofpga -I .: -d -o . allclocks.txt siclk.txt sirefclk.txt global.txt wbdown.txt icape.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt bkram.txt sdio.txt emmc.txt netrouter.txt cpunet.txt hdmi.txt cec.txt edid.txt emmcscope.txt netscope.txt i2cscope.txt mem_bkram_only.txt mem_flash_bkram.txt i2ccpu.txt fan.txt netclk.txt sirefclkcounter.txt
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


#include <stdint.h>


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


	////////////////////////////////////////////////////////////////////////
	//
	// I2C CPU data structures
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//
#ifndef	I2CCPU_H
#define	I2CCPU_H

#define	I2CC_WAITING	0x00800000	// True if waiting for synch signal
#define	I2CC_HALT	0x00400000	// Halt request
#define	I2CC_ABORT	0x00200000	// Abort
#define	I2CC_ERROR	0x00100000
#define	I2CC_HARDHALT	0x00080000
#define	I2CC_SCL	0x00000200
#define	I2CC_SDA	0x00000100
#define I2CC_STOPPED	I2CC_HARDHALT
#define I2CC_FAULT	(I2CC_ERROR | I2CC_ABORT)
#define I2CC_CLEAR	(I2CC_FAULT | I2CC_HALT)

// For the manual port
#define	I2CC_MANSCL	0x00008000
#define	I2CC_MANSDA	0x00004000
#define	I2CC_MANUAL	0x00000800
#define	I2CC_TVALID	0x00000200
#define	I2CC_TLAST	0x00000100

typedef	struct	I2CCPU_S {
	volatile unsigned	ic_control,
				ic_override,
				ic_address,
				ic_clkcount;
} I2CCPU;

#endif	// I2CCPU_H
	// }}}


#ifndef	I2CDMA_H
#define	I2CDMA_H
	////////////////////////////////////////////////////////////////////////
	//
	// I2C DMA data structures
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//


typedef struct  I2CDMA_S        {
	unsigned	id_control, id_current, id_base, id_memlen;
} I2CDMA;

#endif	// I2CDMA_H
	// }}}


#define	SPIO_BTNC	0x01000
#define	SPIO_BTND	0x00800
#define	SPIO_BTNL	0x00400
#define	SPIO_BTNR	0x00200
#define	SPIO_BTNU	0x00100


////////////////////////////////////////////////////////////////////////////////
//
// SDIO SD Card constants
// {{{
////////////////////////////////////////////////////////////////////////////////
//
//

// These will be defined in sdiodrv.h for the SDIO controller
struct SDIO_S;
// }}}


//
// GPIO input wires
//
#define	GPIO_SOFT_RESET		0x000010000
#define	GPIO_PI_RESET		0x000020000
#define	GPIO_SYSCLK_LOCKED	0x000040000
#define	GPIO_SI_INT		0x000080000
#define	GPIO_HDMITXD		0x000100000
#define	GPIO_PIXCLK_LOCKED	0x000200000
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
#define	GPIO_HDMIRXD		0x000000020
#define	GPIO_TRACE		0x000000040	// SIM ONLY
#define	GPIO_ERROR		0x000000080	// SIM ONLY
//
#define	GPIO_TP0_SET		GPIO_SET(GPIO_TP0)
#define	GPIO_TP0_CLR		GPIO_CLR(GPIO_TP0)
#define	GPIO_TP1_SET		GPIO_SET(GPIO_TP1)
#define	GPIO_TP1_CLR		GPIO_CLR(GPIO_TP1)
#define	GPIO_TP2_SET		GPIO_SET(GPIO_TP2)
#define	GPIO_TP2_CLR		GPIO_CLR(GPIO_TP2)
#define	GPIO_TP3_SET		GPIO_SET(GPIO_TP3)
#define	GPIO_TP3_CLR		GPIO_CLR(GPIO_TP3)
#define	GPIO_SIRESET_SET	GPIO_SET(GPIO_SIRESET)
#define	GPIO_SIRESET_CLR	GPIO_CLR(GPIO_SIRESET)
#define	GPIO_HDMIRXD_SET	GPIO_SET(GPIO_HDMIRXD)
#define	GPIO_HDMIRXD_CLR	GPIO_CLR(GPIO_HDMIRXD)
#define	GPIO_TRACE_SET		GPIO_SET(GPIO_TRACE)
#define	GPIO_TRACE_CLR		GPIO_CLR(GPIO_TRACE)
#define	GPIO_ERROR_SET		GPIO_SET(GPIO_ERROR)
#define	GPIO_ERROR_CLR		GPIO_CLR(GPIO_ERROR)
#define	SET_TRACE		(*_gpio) = GPIO_TRACE_SET
#define	CLR_TRACE		(*_gpio) = GPIO_TRACE_CLR


// Offsets for the ICAPE2 interface
#define	CFG_CRC		0
#define	CFG_FAR		1
#define	CFG_FDRI	2
#define	CFG_FDRO	3
#define	CFG_CMD		4
#define	CFG_CTL0	5
#define	CFG_MASK	6
#define	CFG_STAT	7
#define	CFG_LOUT	8
#define	CFG_COR0	9
#define	CFG_MFWR	10
#define	CFG_CBC		11
#define	CFG_IDCODE	12
#define	CFG_AXSS	13
#define	CFG_COR1	14
#define	CFG_WBSTAR	16
#define	CFG_TIMER	17
#define	CFG_BOOTSTS	22
#define	CFG_CTL1	24
#define	CFG_BSPI	31


#ifndef	WBSCOPE_H
#define	WBSCOPE_H

#define	WBSCOPE_NO_RESET	0x80000000u
#define	WBSCOPE_STOPPED		0x40000000u
#define	WBSCOPE_TRIGGERED	0x20000000u
#define	WBSCOPE_PRIMED		0x10000000u
#define	WBSCOPE_TRIGGER		(WBSCOPE_NO_RESET|0x08000000u)
#define	WBSCOPE_MANUAL		(WBSCOPE_TRIGGER)
#define	WBSCOPE_DISABLE		0x04000000u

typedef	struct	WBSCOPE_S {
	volatile unsigned s_ctrl, s_data;
} WBSCOPE;
#endif


typedef struct  CONSOLE_S {
	volatile unsigned	u_setup;
	volatile unsigned	u_fifo;
	volatile unsigned	u_rx, u_tx;
} CONSOLE;

#define	_uart_txbusy	((_uart->u_fifo & 0x10000)==0)
#define	_uart_txidle	((_uart->u_tx   & 0x100)  ==0)


#define	ALTPIC(A)	(1<<(A))


#ifndef VIDPIPE_H
#define VIDPIPE_H

typedef struct __attribute__((packed)) VIDMODE_S {
	uint16_t	m_height,     m_width;
	uint16_t	m_vporch,     m_hporch;
	uint16_t	m_vsync,      m_hsync;
	uint16_t	m_raw_height, m_raw_width;
} VIDMODE;

typedef struct __attribute__((packed)) VIDPIPE_S {
	uint32_t	v_control, v_hdmifreq, v_sifreq, v_pxfreq;
	VIDMODE		v_in, v_src;
	const char	*v_overlay;
	uint16_t	v_ovheight, v_ovmemwords;
	uint16_t	v_ovypos,  v_ovhpos;
	unsigned	v_fps;
	uint32_t	v_unused[256-16];
	uint32_t	v_clrmap[256];
} VIDPIPE;

#endif // VIDPIPE_H


////////////////////////////////////////////////////////////////////////////////
//
// eMMC Card constants
// {{{
////////////////////////////////////////////////////////////////////////////////
//
//

struct EMMC_S;
// }}}


#define	SYSPIC(A)	(1<<(A))


#ifndef	CPUNET_H
#define	CPUNET_H
	////////////////////////////////////////////////////////////////////////
	//
	// CPU Net virtual packet FIFO structures
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//
typedef struct  CPUNET_S        {
	volatile unsigned
		net_rxbase, net_rxlen, net_rxwptr, net_rxrptr,
		net_txbase, net_txlen, net_txwptr, net_txrptr;
} CPUNET;

#endif	// CPUNET_H
	// }}}


#ifndef	WBSCOPE_H
#define	WBSCOPE_H

#define	WBSCOPE_NO_RESET	0x80000000u
#define	WBSCOPE_STOPPED		0x40000000u
#define	WBSCOPE_TRIGGERED	0x20000000u
#define	WBSCOPE_PRIMED		0x10000000u
#define	WBSCOPE_TRIGGER		(WBSCOPE_NO_RESET|0x08000000u)
#define	WBSCOPE_MANUAL		(WBSCOPE_TRIGGER)
#define	WBSCOPE_DISABLE		0x04000000u

typedef	struct	WBSCOPE_S {
	volatile unsigned s_ctrl, s_data;
} WBSCOPE;
#endif




#ifndef	WBSCOPE_H
#define	WBSCOPE_H

#define	WBSCOPE_NO_RESET	0x80000000u
#define	WBSCOPE_STOPPED		0x40000000u
#define	WBSCOPE_TRIGGERED	0x20000000u
#define	WBSCOPE_PRIMED		0x10000000u
#define	WBSCOPE_TRIGGER		(WBSCOPE_NO_RESET|0x08000000u)
#define	WBSCOPE_MANUAL		(WBSCOPE_TRIGGER)
#define	WBSCOPE_DISABLE		0x04000000u

typedef	struct	WBSCOPE_S {
	volatile unsigned s_ctrl, s_data;
} WBSCOPE;
#endif


#ifdef	REFCLKCOUNTER_ACCESS
#define	_BOARD_HAS_REFCLKCOUNTER
static volatile unsigned *const _sirefclkcounter = ((unsigned *)0x000406d8);
#endif	// REFCLKCOUNTER_ACCESS
#ifdef	NETCLK_ACCESS
#define	_BOARD_HAS_NETCLK
static volatile unsigned *const _netclk = ((unsigned *)0x00040680);
#endif	// NETCLK_ACCESS
#ifdef	FAN_ACCESS
#define	_BOARD_HAS_FAN
static volatile FAN *const _fan=((FAN *)0x00040300);
#endif	// FAN_ACCESS
#ifdef	I2CCPU_ACCESS
#define	_BOARD_HAS_I2CCPU
static volatile I2CCPU *const _i2c=((I2CCPU *)0x00040600);
#endif	// I2CCPU_ACCESS
#ifdef	I2CDMA_ACCESS
#define	_BOARD_HAS_I2CDMA
static volatile I2CDMA *const _i2cdma=((I2CDMA *)0x00040640);
#endif	// I2CDMA_ACCESS
#ifdef	SPIO_ACCESS
#define	_BOARD_HAS_SPIO
static volatile unsigned *const _spio = ((unsigned *)0x000406dc);
#endif	// SPIO_ACCESS
#ifdef	SDIO_ACCESS
#define	_BOARD_HAS_SDIO
static volatile struct SDIO_S *const _sdio = ((struct SDIO_S *)0x00040380);
#endif	// SDIO_ACCESS
#ifdef	GPIO_ACCESS
#define	_BOARD_HAS_GPIO
static volatile unsigned *const _gpio = ((unsigned *)0x000406c4);
#endif	// GPIO_ACCESS
#ifdef	CFG_ACCESS
#define	_BOARD_HAS_ICAPTETWO
static volatile unsigned *const _icape = ((unsigned *)0x00000480);
#endif	// CFG_ACCESS
#ifdef	I2CSCOPE_SCOPC
#define	_BOARD_HAS_I2CSCOPE
static volatile WBSCOPE *const _i2cscope = ((WBSCOPE *)0x00040080);
#endif	// I2CSCOPE_SCOPC
#ifdef	VERSION_ACCESS
#define	_BOARD_HAS_VERSION
static volatile unsigned *const _version = ((unsigned *)0x000406e0);
#endif	// VERSION_ACCESS
#ifdef	SIREFCLK_ACCESS
#define	_BOARD_HAS_SIREFCLK
static volatile unsigned *const _sirefclk = ((unsigned *)0x000406d4);
#endif	// SIREFCLK_ACCESS
#ifdef	SICLK
#define	_BOARD_HAS_SICLKCOUNTER
static volatile unsigned *const _siclk = ((unsigned *)0x000406d0);
#endif	// SICLK
#define	_BOARD_HAS_BUILDTIME
static volatile unsigned *const _buildtime = ((unsigned *)0x000406c0);
#ifdef	BUSCONSOLE_ACCESS
#define	_BOARD_HAS_BUSCONSOLE
static volatile CONSOLE *const _uart = ((CONSOLE *)0x00040180);
#endif	// BUSCONSOLE_ACCESS
#ifdef	VIDPIPE_ACCESS
#define	_BOARD_HAS_VIDPIPE
static volatile VIDPIPE *const _hdmi = ((VIDPIPE *)0x00040800);
#endif	// VIDPIPE_ACCESS
#ifdef	EMMC_ACCESS
#define	_BOARD_HAS_EMMC
static volatile struct EMMC_S *const _emmc = ((struct EMMC_S *)0x00040280);
#endif	// EMMC_ACCESS
#ifdef	BKRAM_ACCESS
#define	_BOARD_HAS_BKRAM
extern char	_bkram[0x00080000];
#endif	// BKRAM_ACCESS
#ifdef	CPUNET_ACCESS
#define	_BOARD_HAS_CPUNET
static volatile CPUNET *const _cpunet=((CPUNET *)0x00040200);
#endif	// CPUNET_ACCESS
#ifdef	EMMCSCOPE_SCOPC
#define	_BOARD_HAS_EMMCSCOPE
static volatile WBSCOPE *const _emmcscope = ((WBSCOPE *)0x00040000);
#endif	// EMMCSCOPE_SCOPC
#ifdef	EDID_ACCESS
#define	_BOARD_HAS_EDID
static volatile char *const _edid=((char *)0x00040700);
#endif	// EDID_ACCESS
#ifdef	NETSCOPE_SCOPC
#define	_BOARD_HAS_NETSCOPE
static volatile WBSCOPE *const _netscope = ((WBSCOPE *)0x00040100);
#endif	// NETSCOPE_SCOPC
//
// Interrupt assignments (2 PICs)
//
// PIC: altpic
#define	ALTPIC_UIC	ALTPIC(0)
#define	ALTPIC_UOC	ALTPIC(1)
#define	ALTPIC_UPC	ALTPIC(2)
#define	ALTPIC_UTC	ALTPIC(3)
#define	ALTPIC_MIC	ALTPIC(4)
#define	ALTPIC_MOC	ALTPIC(5)
#define	ALTPIC_MPC	ALTPIC(6)
#define	ALTPIC_MTC	ALTPIC(7)
#define	ALTPIC_GPIO	ALTPIC(8)
#define	ALTPIC_I2CSCOPE	ALTPIC(9)
#define	ALTPIC_UARTTX	ALTPIC(10)
#define	ALTPIC_UARTRX	ALTPIC(11)
#define	ALTPIC_EMMC	ALTPIC(12)
#define	ALTPIC_EMMCSCOPE	ALTPIC(13)
#define	ALTPIC_NETSCOPE	ALTPIC(14)
// PIC: syspic
#define	SYSPIC_DMAC	SYSPIC(0)
#define	SYSPIC_JIFFIES	SYSPIC(1)
#define	SYSPIC_TMC	SYSPIC(2)
#define	SYSPIC_TMB	SYSPIC(3)
#define	SYSPIC_TMA	SYSPIC(4)
#define	SYSPIC_ALT	SYSPIC(5)
#define	SYSPIC_SPIO	SYSPIC(6)
#define	SYSPIC_SDCARD	SYSPIC(7)
#define	SYSPIC_UARTRXF	SYSPIC(8)
#define	SYSPIC_UARTTXF	SYSPIC(9)
#define	SYSPIC_TXNET	SYSPIC(10)
#define	SYSPIC_RXNET	SYSPIC(11)
#endif	// BOARD_H
