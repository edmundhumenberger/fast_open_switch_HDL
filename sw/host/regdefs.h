////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./regdefs.h
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
#ifndef	REGDEFS_H
#define	REGDEFS_H


//
// The @REGDEFS.H.INCLUDE tag
//
// @REGDEFS.H.INCLUDE for masters
// @REGDEFS.H.INCLUDE for peripherals
// And finally any master REGDEFS.H.INCLUDE tags
// End of definitions from REGDEFS.H.INCLUDE


//
// Register address definitions, from @REGS.#d
//
// hdmiclrscope scope
#define	R_HDMICLRSCOPE   	0x02000000	// 02000000, wbregs names: HDMICLRSCOPE
#define	R_HDMICLRSCOPED  	0x02000004	// 02000000, wbregs names: HDMICLRSCOPED
// netscope compressed scope
#define	R_NETSCOPE       	0x02000100	// 02000100, wbregs names: NETSCOPE
#define	R_NETSCOPED      	0x02000104	// 02000100, wbregs names: NETSCOPED
// CONSOLE registers
#define	R_CONSOLE_FIFO   	0x02000204	// 02000200, wbregs names: UFIFO
#define	R_CONSOLE_UARTRX 	0x02000208	// 02000200, wbregs names: RX
#define	R_CONSOLE_UARTTX 	0x0200020c	// 02000200, wbregs names: TX
// eMMC Card addresses
#define	R_EMMC_CTRL      	0x02000300	// 02000300, wbregs names: EMMCCARD
#define	R_EMMC_DATA      	0x02000304	// 02000300, wbregs names: EMMCDATA
#define	R_EMMC_FIFOA     	0x02000308	// 02000300, wbregs names: EMMCFIFOA, EMMCFIF0, EMMCFIFA
#define	R_EMMC_FIFOB     	0x0200030c	// 02000300, wbregs names: EMMCFIFOB, EMMCFIF1, EMMCFIFB
#define	R_EMMC_PHY       	0x02000310	// 02000300, wbregs names: EMMCPHY
#define	R_FAN_FPGAPWM    	0x02000400	// 02000400, wbregs names: FAN_FPGAPWM
#define	R_FAN_SYSPWM     	0x02000404	// 02000400, wbregs names: FAN_SYSPWM
#define	R_FAN_TACH       	0x02000408	// 02000400, wbregs names: FAN_TACH
#define	R_FAN_TEMP       	0x0200040c	// 02000400, wbregs names: FAN_TEMP
#define	R_FAN            	0x02000410	// 02000400, wbregs names: FAN_CTRL
#define	R_FAN_OVW        	0x02000414	// 02000400, wbregs names: FAN_OVW, FAN_OVERRIDE
#define	R_FAN_ADDR       	0x02000418	// 02000400, wbregs names: FAN_ADDR, FAN_ADDRESS
#define	R_FAN_CKCOUNT    	0x0200041c	// 02000400, wbregs names: FANCLK, FAN_CKCOUNT
// SDIO SD Card addresses
#define	R_SDIO_CTRL      	0x02000500	// 02000500, wbregs names: SDCARD
#define	R_SDIO_DATA      	0x02000504	// 02000500, wbregs names: SDDATA
#define	R_SDIO_FIFOA     	0x02000508	// 02000500, wbregs names: SDFIFOA, SDFIF0, SDFIFA
#define	R_SDIO_FIFOB     	0x0200050c	// 02000500, wbregs names: SDFIFOB, SDFIF1, SDFIFB
#define	R_SDIO_PHY       	0x02000510	// 02000500, wbregs names: SDPHY
// FPGA CONFIG REGISTERS: 0x4e0-0x4ff
#define	R_CFG_CRC        	0x02000700	// 02000700, wbregs names: FPGACRC
#define	R_CFG_FAR        	0x02000704	// 02000700, wbregs names: FPGAFAR
#define	R_CFG_FDRI       	0x02000708	// 02000700, wbregs names: FPGAFDRI
#define	R_CFG_FDRO       	0x0200070c	// 02000700, wbregs names: FPGAFDRO
#define	R_CFG_CMD        	0x02000710	// 02000700, wbregs names: FPGACMD
#define	R_CFG_CTL0       	0x02000714	// 02000700, wbregs names: FPGACTL0
#define	R_CFG_MASK       	0x02000718	// 02000700, wbregs names: FPGAMASK
#define	R_CFG_STAT       	0x0200071c	// 02000700, wbregs names: FPGASTAT
#define	R_CFG_LOUT       	0x02000720	// 02000700, wbregs names: FPGALOUT
#define	R_CFG_COR0       	0x02000724	// 02000700, wbregs names: FPGACOR0
#define	R_CFG_MFWR       	0x02000728	// 02000700, wbregs names: FPGAMFWR
#define	R_CFG_CBC        	0x0200072c	// 02000700, wbregs names: FPGACBC
#define	R_CFG_IDCODE     	0x02000730	// 02000700, wbregs names: FPGAIDCODE
#define	R_CFG_AXSS       	0x02000734	// 02000700, wbregs names: FPGAAXSS
#define	R_CFG_COR1       	0x02000738	// 02000700, wbregs names: FPGACOR1
#define	R_CFG_WBSTAR     	0x02000740	// 02000700, wbregs names: WBSTAR
#define	R_CFG_TIMER      	0x02000744	// 02000700, wbregs names: CFGTIMER
#define	R_CFG_BOOTSTS    	0x02000758	// 02000700, wbregs names: BOOTSTS
#define	R_CFG_CTL1       	0x02000760	// 02000700, wbregs names: FPGACTL1
#define	R_CFG_BSPI       	0x0200077c	// 02000700, wbregs names: FPGABSPI
// CPU Net Controller registers
#define	R_CPUNETRX_BASE  	0x02000800	// 02000800, wbregs names: CPUNETRXBASE
#define	R_CPUNETRX_LEN   	0x02000804	// 02000800, wbregs names: CPUNETRXLEN
#define	R_CPUNETRX_RPTR  	0x02000808	// 02000800, wbregs names: CPUNETRXRPTR
#define	R_CPUNETRX_WPTR  	0x0200080c	// 02000800, wbregs names: CPUNETRXWPTR
#define	R_CPUNETTX_BASE  	0x02000810	// 02000800, wbregs names: CPUNETTXBASE
#define	R_CPUNETTX_LEN   	0x02000814	// 02000800, wbregs names: CPUNETTXLEN
#define	R_CPUNETTX_RPTR  	0x02000818	// 02000800, wbregs names: CPUNETTXRPTR
#define	R_CPUNETTX_WPTR  	0x0200081c	// 02000800, wbregs names: CPUNETTXWPTR
#define	R_DDR3_PHY       	0x02000a00	// 02000a00, wbregs names: DDR3_PHY
// I2C Controller registers
#define	R_I2CCPU         	0x02000c00	// 02000c00, wbregs names: I2CCPU, I2CCPU_CTRL, I2CCPUCTRL
#define	R_I2CCPU_OVW     	0x02000c04	// 02000c00, wbregs names: I2CCPU_OVW, I2CCPU_OVERRIDE
#define	R_I2CCPU_ADDR    	0x02000c08	// 02000c00, wbregs names: I2CCPU_ADDR, I2CCPU_ADDRESS
#define	R_I2CCPU_CKCOUNT 	0x02000c0c	// 02000c00, wbregs names: I2CCPUCLK, I2CCPU_CKCOUNT
#define	R_I2CDMA         	0x02000c40	// 02000c40, wbregs names: I2CDMA
#define	R_I2CDMA_ADDR    	0x02000c44	// 02000c40, wbregs names: I2CDMAADDR
#define	R_I2CDMA_BASE    	0x02000c48	// 02000c40, wbregs names: I2CDMABASE
#define	R_I2CDMA_LEN     	0x02000c4c	// 02000c40, wbregs names: I2CDMALEN
#define	R_RXNETCK0       	0x02000c80	// 02000c80, wbregs names: RXNETCLK0, RXNETCK0
#define	R_RXNETCK1       	0x02000c84	// 02000c80, wbregs names: RXNETCLK1, RXNETCK1
#define	R_RXNETCK2       	0x02000c88	// 02000c80, wbregs names: RXNETCLK2, RXNETCK2
#define	R_RXNETCK3       	0x02000c8c	// 02000c80, wbregs names: RXNETCLK3, RXNETCK3
#define	R_TXNETCLK       	0x02000c90	// 02000c80, wbregs names: TXNETCLK
#define	R_BUILDTIME      	0x02000cc0	// 02000cc0, wbregs names: BUILDTIME
#define	R_GPIO           	0x02000cc4	// 02000cc4, wbregs names: GPIO, GPI, GPO
#define	R_NETDBG         	0x02000cc8	// 02000cc8, wbregs names: NETDBG
#define	R_NETLOCK        	0x02000ccc	// 02000ccc, wbregs names: NETLOCK
#define	R_SICLKFREQ      	0x02000cd0	// 02000cd0, wbregs names: SICLKFREQcreate_clock, -period, 5.2, -name, SIREF, -waveform, {0.0, 2.6, }, -add, [get_ports, i_clk_si_p]
#define	R_SIREFCLK       	0x02000cd4	// 02000cd4, wbregs names: SIREFCLK
#define	R_SIREFFREQ      	0x02000cd8	// 02000cd8, wbregs names: SIREFFREQ
#define	R_SPIO           	0x02000cdc	// 02000cdc, wbregs names: SPIO
#define	R_VERSION        	0x02000ce0	// 02000ce0, wbregs names: VERSION
// HDMI video processing pipe registers
#define	R_VIDPIPE        	0x02001000	// 02001000, wbregs names: VIDPIPE, VIDCTRL
#define	R_HDMIFREQ       	0x02001004	// 02001000, wbregs names: HDMIFREQ
#define	R_SIFREQ         	0x02001008	// 02001000, wbregs names: SIFREQ
#define	R_PXFREQ         	0x0200100c	// 02001000, wbregs names: PXFREQ
#define	R_INSIZE         	0x02001010	// 02001000, wbregs names: INSIZE
#define	R_INPORCH        	0x02001014	// 02001000, wbregs names: INPORCH
#define	R_INSYNC         	0x02001018	// 02001000, wbregs names: INSYNC
#define	R_INRAW          	0x0200101c	// 02001000, wbregs names: INRAW
#define	R_HDMISIZE       	0x02001020	// 02001000, wbregs names: HDMISIZE
#define	R_HDMIPORCH      	0x02001024	// 02001000, wbregs names: HDMIPORCH
#define	R_HDMISYNC       	0x02001028	// 02001000, wbregs names: HDMISYNC
#define	R_HDMIRAW        	0x0200102c	// 02001000, wbregs names: HDMIRAW
#define	R_OVADDR         	0x02001030	// 02001000, wbregs names: OVADDR
#define	R_OVSIZE         	0x02001034	// 02001000, wbregs names: OVSIZE
#define	R_OVOFFSET       	0x02001038	// 02001000, wbregs names: OVOFFSET
#define	R_FPS            	0x0200103c	// 02001000, wbregs names: FPS
#define	R_SYNCWORD       	0x02001040	// 02001000, wbregs names: VSYNCWORD
#define	R_VIDRCAP        	0x02001044	// 02001000, wbregs names: VIDRCAP
#define	R_VIDGCAP        	0x02001048	// 02001000, wbregs names: VIDGCAP
#define	R_VIDBCAP        	0x0200104c	// 02001000, wbregs names: VIDBCAP
#define	R_CMAP           	0x02001800	// 02001000, wbregs names: CMAP
#define	R_BKRAM          	0x04000000	// 04000000, wbregs names: RAM
#define	R_DDR3_CONTROLLER	0x40000000	// 40000000, wbregs names: DDR3_CONTROLLER
// ZipCPU control/debug registers
#define	R_ZIPCTRL        	0x80000000	// 80000000, wbregs names: CPU, ZIPCTRL
#define	R_ZIPREGS        	0x80000080	// 80000000, wbregs names: ZIPREGS
#define	R_ZIPS0          	0x80000080	// 80000000, wbregs names: SR0
#define	R_ZIPS1          	0x80000084	// 80000000, wbregs names: SR1
#define	R_ZIPS2          	0x80000088	// 80000000, wbregs names: SR2
#define	R_ZIPS3          	0x8000008c	// 80000000, wbregs names: SR3
#define	R_ZIPS4          	0x80000090	// 80000000, wbregs names: SR4
#define	R_ZIPS5          	0x80000094	// 80000000, wbregs names: SR5
#define	R_ZIPS6          	0x80000098	// 80000000, wbregs names: SR6
#define	R_ZIPS7          	0x8000009c	// 80000000, wbregs names: SR7
#define	R_ZIPS8          	0x800000a0	// 80000000, wbregs names: SR8
#define	R_ZIPS9          	0x800000a4	// 80000000, wbregs names: SR9
#define	R_ZIPS10         	0x800000a8	// 80000000, wbregs names: SR10
#define	R_ZIPS11         	0x800000ac	// 80000000, wbregs names: SR11
#define	R_ZIPS12         	0x800000b0	// 80000000, wbregs names: SR12
#define	R_ZIPSSP         	0x800000b4	// 80000000, wbregs names: SSP, SR13
#define	R_ZIPCC          	0x800000b8	// 80000000, wbregs names: ZIPCC, CC, SCC, SR14
#define	R_ZIPPC          	0x800000bc	// 80000000, wbregs names: ZIPPC, PC, SPC, SR15
#define	R_ZIPUSER        	0x800000c0	// 80000000, wbregs names: ZIPUSER
#define	R_ZIPU0          	0x800000c0	// 80000000, wbregs names: UR0
#define	R_ZIPU1          	0x800000c4	// 80000000, wbregs names: UR1
#define	R_ZIPU2          	0x800000c8	// 80000000, wbregs names: UR2
#define	R_ZIPU3          	0x800000cc	// 80000000, wbregs names: UR3
#define	R_ZIPU4          	0x800000d0	// 80000000, wbregs names: UR4
#define	R_ZIPU5          	0x800000d4	// 80000000, wbregs names: UR5
#define	R_ZIPU6          	0x800000d8	// 80000000, wbregs names: UR6
#define	R_ZIPU7          	0x800000dc	// 80000000, wbregs names: UR7
#define	R_ZIPU8          	0x800000e0	// 80000000, wbregs names: UR8
#define	R_ZIPU9          	0x800000e4	// 80000000, wbregs names: UR9
#define	R_ZIPU10         	0x800000e8	// 80000000, wbregs names: SR10
#define	R_ZIPU11         	0x800000ec	// 80000000, wbregs names: SR11
#define	R_ZIPU12         	0x800000f0	// 80000000, wbregs names: SR12
#define	R_ZIPUSP         	0x800000f4	// 80000000, wbregs names: USP, UR13
#define	R_ZIPUCC         	0x800000f8	// 80000000, wbregs names: ZIPUCC, UCC
#define	R_ZIPUPC         	0x800000fc	// 80000000, wbregs names: ZIPUPC, UPC
#define	R_ZIPSYSTEM      	0x80000100	// 80000000, wbregs names: ZIPSYSTEM, ZIPSYS
#define	R_ZIPPIC         	0x80000100	// 80000000, wbregs names: ZIPPIC
#define	R_ZIPWDOG        	0x80000104	// 80000000, wbregs names: ZIPWDOG
#define	R_ZIPBDOG        	0x80000108	// 80000000, wbregs names: ZIPBDOG
#define	R_ZIPAPIC        	0x8000010c	// 80000000, wbregs names: ZIPAPIC
#define	R_ZIPTIMA        	0x80000110	// 80000000, wbregs names: ZIPTIMA
#define	R_ZIPTIMB        	0x80000114	// 80000000, wbregs names: ZIPTIMB
#define	R_ZIPTIMC        	0x80000118	// 80000000, wbregs names: ZIPTIMC
#define	R_ZIPJIFF        	0x8000011c	// 80000000, wbregs names: ZIPJIFF
#define	R_ZIPMTASK       	0x80000120	// 80000000, wbregs names: ZIPMTASK
#define	R_ZIPMMSTL       	0x80000124	// 80000000, wbregs names: ZIPMMSTL
#define	R_ZIPMPSTL       	0x80000128	// 80000000, wbregs names: ZIPMPSTL
#define	R_ZIPMINSN       	0x8000012c	// 80000000, wbregs names: ZIPMINSN
#define	R_ZIPUTASK       	0x80000130	// 80000000, wbregs names: ZIPUTASK
#define	R_ZIPUMSTL       	0x80000134	// 80000000, wbregs names: ZIPUMSTL
#define	R_ZIPUPSTL       	0x80000138	// 80000000, wbregs names: ZIPUPSTL
#define	R_ZIPUINSN       	0x8000013c	// 80000000, wbregs names: ZIPUINSN
#define	R_ZIPDMAC        	0x80000140	// 80000000, wbregs names: ZIPDMAC


//
// The @REGDEFS.H.DEFNS tag
//
// @REGDEFS.H.DEFNS for masters
#define	BAUDRATE	1000000
// @REGDEFS.H.DEFNS for peripherals
#define	BKRAMBASE	0x04000000
#define	BKRAMLEN	0x00080000
#define	DDR3_CONTROLLERBASE	0x40000000
#define	DDR3_CONTROLLERLEN	0x40000000
// @REGDEFS.H.DEFNS at the top level
// End of definitions from REGDEFS.H.DEFNS
//
// The @REGDEFS.H.INSERT tag
//
// @REGDEFS.H.INSERT for masters
// @REGDEFS.H.INSERT for peripherals
////////////////////////////////////////////////////////////////////////////////
//
// ZipCPU register definitions
// {{{

#define	CPU_GO		0x0000
#define	CPU_HALT	0x0001
#define	CPU_STALL	0x0002
#define	CPU_STEP	0x0004
#define	CPU_RESET	0x0008
#define	CPU_CLRCACHE	0x0010
// (Reserved)		0x00e0
#define	CPU_SLEEPING	0x0100
#define	CPU_GIE		0x0200
#define	CPU_INT		0x0400
#define	CPU_BREAK	0x0800
#define	CPU_EXINT	0xfffff000
//
#define	CPU_sR0		0x0020
#define	CPU_sSP		0x002d
#define	CPU_sCC		0x002e
#define	CPU_sPC		0x002f
#define	CPU_uR0		0x0030
#define	CPU_uSP		0x003d
#define	CPU_uCC		0x003e
#define	CPU_uPC		0x003f

#ifdef	BKROM_ACCESS
#define	RESET_ADDRESS	@$[0x%08x](bkrom.REGBASE)
#else
#ifdef	FLASH_ACCESS
#define	RESET_ADDRESS	@$[0x%08x](RESET_ADDRESS)
#else
#define	RESET_ADDRESS	0x04000000
#endif	// FLASH_ACCESS
#endif	// BKROM_ACCESS
// }}}
// @REGDEFS.H.INSERT from the top level
typedef	struct {
	unsigned	m_addr;
	const char	*m_name;
} REGNAME;

extern	const	REGNAME	*bregs;
extern	const	int	NREGS;
// #define	NREGS	(sizeof(bregs)/sizeof(bregs[0]))

extern	unsigned	addrdecode(const char *v);
extern	const	char *addrname(const unsigned v);
// End of definitions from REGDEFS.H.INSERT


#endif	// REGDEFS_H
