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
// CmdLine:	autofpga -I .: -d -o . allclocks.txt siclk.txt sirefclk.txt global.txt wbdown.txt icape.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt bkram.txt ddr3.txt sdio.txt emmc.txt netrouter.txt cpunet.txt hdmi.txt cec.txt edid.txt netscope.txt hdmiclrscope.txt mem_bkram_only.txt mem_full.txt i2ccpu.txt fan.txt netclk.txt sirefclkcounter.txt
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




typedef	struct	DDR3_PHY_S {
	unsigned	ph_something;
} DDR3_PHY;



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
	unsigned	v_syncword;
	uint32_t	v_unused[512-17];
	uint32_t	v_clrmap[256];
} VIDPIPE;

#endif // VIDPIPE_H


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



typedef	struct	PKTVFIFO_S {
	char		*v_base;
	unsigned	v_memsize;
	volatile char	*v_wrptr, *v_rdptr;
} PKTVFIFO;

struct	ROUTER_S {
	PKTVFIFO	vfif[4];
};



#ifndef	CPUNET_H
#define	CPUNET_H
	////////////////////////////////////////////////////////////////////////
	//
	// CPU Net virtual packet FIFO structures
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//

#define	CPUNET_PROMISCUOUS	1
#define	CPUNET_EN		2
#define	CPUNET_ERROR		4
#define	CPUNET_RDRESET		8
#define	CPUNET_TXRESET		8
#define	CPUNET_WRRESET		16
#define	CPUNET_RXRESET		16

typedef struct  CPUNET_S        {
	// Control registers
	volatile unsigned	net_control;
		unsigned	net_mac[2];
		unsigned	net_ip[5];
	volatile unsigned	net_rxdrops;
	volatile unsigned	net_rxpkts;
	volatile unsigned	net_txpkts;
		unsigned	net_unused[5];
	//
	// RX side
		char		*net_txbase;
		unsigned	net_txlen;
	volatile char		*net_txwptr, *net_txrptr;
	//
	// TX side
		char		*net_rxbase;
		unsigned	net_rxlen;
	volatile char		*net_rxwptr, *net_rxrptr;
} CPUNET;

#endif	// CPUNET_H
	// }}}


#ifdef	REFCLKCOUNTER_ACCESS
#define	_BOARD_HAS_REFCLKCOUNTER
static volatile unsigned *const _sirefclkcounter = ((unsigned *)0x02000cdc);
#endif	// REFCLKCOUNTER_ACCESS
#ifdef	NETCLK_ACCESS
#define	_BOARD_HAS_NETCLK
static volatile unsigned *const _netclk = ((unsigned *)0x02000c80);
#endif	// NETCLK_ACCESS
#ifdef	FAN_ACCESS
#define	_BOARD_HAS_FAN
static volatile FAN *const _fan=((FAN *)0x02000400);
#endif	// FAN_ACCESS
#ifdef	I2CCPU_ACCESS
#define	_BOARD_HAS_I2CCPU
static volatile I2CCPU *const _i2c=((I2CCPU *)0x02000c00);
#endif	// I2CCPU_ACCESS
#ifdef	I2CDMA_ACCESS
#define	_BOARD_HAS_I2CDMA
static volatile I2CDMA *const _i2cdma=((I2CDMA *)0x02000c40);
#endif	// I2CDMA_ACCESS
#ifdef	HDMICLRSCOPE_SCOPE
#define	_BOARD_HAS_HDMICLRSCOPE
static volatile WBSCOPE *const _hdmiclrscope = ((WBSCOPE *)0x02000000);
#endif	// HDMICLRSCOPE_SCOPE
#ifdef	SPIO_ACCESS
#define	_BOARD_HAS_SPIO
static volatile unsigned *const _spio = ((unsigned *)0x02000ce0);
#endif	// SPIO_ACCESS
#ifdef	SDIO_ACCESS
#define	_BOARD_HAS_SDIO
static volatile struct SDIO_S *const _sdio = ((struct SDIO_S *)0x02000500);
#endif	// SDIO_ACCESS
#ifdef	GPIO_ACCESS
#define	_BOARD_HAS_GPIO
static volatile unsigned *const _gpio = ((unsigned *)0x02000cc4);
#endif	// GPIO_ACCESS
#ifdef	CFG_ACCESS
#define	_BOARD_HAS_ICAPTETWO
static volatile unsigned *const _icape = ((unsigned *)0x00000700);
#endif	// CFG_ACCESS
#ifdef	VERSION_ACCESS
#define	_BOARD_HAS_VERSION
static volatile unsigned *const _version = ((unsigned *)0x02000ce4);
#endif	// VERSION_ACCESS
#ifdef	SIREFCLK_ACCESS
#define	_BOARD_HAS_SIREFCLK
static volatile unsigned *const _sirefclk = ((unsigned *)0x02000cd8);
#endif	// SIREFCLK_ACCESS
#ifdef	DDR3_PHY_ACCESS
#define	_BOARD_HAS_DDR3_PHY
static volatile DDR3_PHY *const _ddr3_phy = ((DDR3_PHY *)0x02000a00);
#endif	// DDR3_PHY_ACCESS
#ifdef	SICLK
#define	_BOARD_HAS_SICLKCOUNTER
static volatile unsigned *const _siclk = ((unsigned *)0x02000cd4);
#endif	// SICLK
#define	_BOARD_HAS_BUILDTIME
static volatile unsigned *const _buildtime = ((unsigned *)0x02000cc0);
#ifdef	BUSCONSOLE_ACCESS
#define	_BOARD_HAS_BUSCONSOLE
static volatile CONSOLE *const _uart = ((CONSOLE *)0x02000200);
#endif	// BUSCONSOLE_ACCESS
#ifdef	VIDPIPE_ACCESS
#define	_BOARD_HAS_VIDPIPE
static volatile VIDPIPE *const _hdmi = ((VIDPIPE *)0x02001000);
#endif	// VIDPIPE_ACCESS
#ifdef	NETSCOPE_SCOPC
#define	_BOARD_HAS_NETSCOPE
static volatile WBSCOPE *const _netscope = ((WBSCOPE *)0x02000100);
#endif	// NETSCOPE_SCOPC
#ifdef	EDID_ACCESS
#define	_BOARD_HAS_EDID
static volatile char *const _edid=((char *)0x02000d00);
#endif	// EDID_ACCESS
#ifdef	EMMC_ACCESS
#define	_BOARD_HAS_EMMC
static volatile struct EMMC_S *const _emmc = ((struct EMMC_S *)0x02000300);
#endif	// EMMC_ACCESS
#ifdef	BKRAM_ACCESS
#define	_BOARD_HAS_BKRAM
extern char	_bkram[0x00080000];
#endif	// BKRAM_ACCESS
#ifdef	DDR3_CONTROLLER_ACCESS
#define	_BOARD_HAS_DDR3_CONTROLLER
extern char	_ddr3_controller[0x40000000];
#endif	// DDR3_CONTROLLER_ACCESS
#ifdef	NETRESET_ACCESS
static volatile unsigned *const _netreset = ((unsigned *)0x02000cd0);
#endif	// NETRESET_ACCESS
#ifdef	ETH_ROUTER
static struct ROUTER_S *const _gnet = ((struct ROUTER_S *)0x02000600);
#endif	// ETH_ROUTER
#ifdef	CPUNET_ACCESS
#define	_BOARD_HAS_CPUNET
static volatile CPUNET *const _cpunet=((CPUNET *)0x02000800);
#endif	// CPUNET_ACCESS
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
#define	ALTPIC_HDMICLRSCOPE	ALTPIC(8)
#define	ALTPIC_GPIO	ALTPIC(9)
#define	ALTPIC_UARTTX	ALTPIC(10)
#define	ALTPIC_UARTRX	ALTPIC(11)
#define	ALTPIC_NETSCOPE	ALTPIC(12)
#define	ALTPIC_EMMC	ALTPIC(13)
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
