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
// CmdLine:	autofpga -I .: -d -o . allclocks.txt siclk.txt sirefclk.txt global.txt wbdown.txt icape.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt bkram.txt ddr3.txt sdio.txt emmc.txt netrouter.txt cpunet.txt routescope.txt netscope.txt mem_bkram_only.txt mem_full.txt i2ccpu.txt fan.txt netclk.txt sirefclkcounter.txt
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
// terms of the 3rd version of the GNU General Public License as published by
// the Free Software Foundation.
//
// This project is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTIBILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program.  (It's in the $(ROOT)/doc directory.  Run make with no
// target there if the PDF file isn't present.)  If not, see
// <http://www.gnu.org/licenses/> for a copy.
// }}}
// License:	GPL, v3, as defined and found on www.gnu.org,
// {{{
//		http://www.gnu.org/licenses/gpl.html
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
// netscope compressed scope
#define	R_NETSCOPE       	0x02000000	// 02000000, wbregs names: NETSCOPE
#define	R_NETSCOPED      	0x02000004	// 02000000, wbregs names: NETSCOPED
// routescope compressed scope
#define	R_ROUTESCOPE     	0x02000080	// 02000080, wbregs names: ROUTESCOPE
#define	R_ROUTESCOPED    	0x02000084	// 02000080, wbregs names: ROUTESCOPED
// CONSOLE registers
#define	R_CONSOLE_FIFO   	0x02000104	// 02000100, wbregs names: UFIFO
#define	R_CONSOLE_UARTRX 	0x02000108	// 02000100, wbregs names: RX
#define	R_CONSOLE_UARTTX 	0x0200010c	// 02000100, wbregs names: TX
// eMMC Card addresses
#define	R_EMMC_CTRL      	0x02000180	// 02000180, wbregs names: EMMCCARD
#define	R_EMMC_DATA      	0x02000184	// 02000180, wbregs names: EMMCDATA
#define	R_EMMC_FIFOA     	0x02000188	// 02000180, wbregs names: EMMCFIFOA, EMMCFIF0, EMMCFIFA
#define	R_EMMC_FIFOB     	0x0200018c	// 02000180, wbregs names: EMMCFIFOB, EMMCFIF1, EMMCFIFB
#define	R_EMMC_PHY       	0x02000190	// 02000180, wbregs names: EMMCPHY
// Fan registers
#define	R_FAN_FPGAPWM    	0x02000200	// 02000200, wbregs names: FAN_FPGAPWM
#define	R_FAN_SYSPWM     	0x02000204	// 02000200, wbregs names: FAN_SYSPWM
#define	R_FAN_TACH       	0x02000208	// 02000200, wbregs names: FAN_TACH
#define	R_FAN_TEMP       	0x0200020c	// 02000200, wbregs names: FAN_TEMP
#define	R_FAN            	0x02000210	// 02000200, wbregs names: FAN_CTRL
#define	R_FAN_OVW        	0x02000214	// 02000200, wbregs names: FAN_OVW, FAN_OVERRIDE
#define	R_FAN_ADDR       	0x02000218	// 02000200, wbregs names: FAN_ADDR, FAN_ADDRESS
#define	R_FAN_CKCOUNT    	0x0200021c	// 02000200, wbregs names: FANCLK, FAN_CKCOUNT
// SDIO SD Card addresses
#define	R_SDIO_CTRL      	0x02000280	// 02000280, wbregs names: SDCARD
#define	R_SDIO_DATA      	0x02000284	// 02000280, wbregs names: SDDATA
#define	R_SDIO_FIFOA     	0x02000288	// 02000280, wbregs names: SDFIFOA, SDFIF0, SDFIFA
#define	R_SDIO_FIFOB     	0x0200028c	// 02000280, wbregs names: SDFIFOB, SDFIF1, SDFIFB
#define	R_SDIO_PHY       	0x02000290	// 02000280, wbregs names: SDPHY
// FPGA CONFIG REGISTERS: 0x4e0-0x4ff
#define	R_CFG_CRC        	0x02000300	// 02000300, wbregs names: FPGACRC
#define	R_CFG_FAR        	0x02000304	// 02000300, wbregs names: FPGAFAR
#define	R_CFG_FDRI       	0x02000308	// 02000300, wbregs names: FPGAFDRI
#define	R_CFG_FDRO       	0x0200030c	// 02000300, wbregs names: FPGAFDRO
#define	R_CFG_CMD        	0x02000310	// 02000300, wbregs names: FPGACMD
#define	R_CFG_CTL0       	0x02000314	// 02000300, wbregs names: FPGACTL0
#define	R_CFG_MASK       	0x02000318	// 02000300, wbregs names: FPGAMASK
#define	R_CFG_STAT       	0x0200031c	// 02000300, wbregs names: FPGASTAT
#define	R_CFG_LOUT       	0x02000320	// 02000300, wbregs names: FPGALOUT
#define	R_CFG_COR0       	0x02000324	// 02000300, wbregs names: FPGACOR0
#define	R_CFG_MFWR       	0x02000328	// 02000300, wbregs names: FPGAMFWR
#define	R_CFG_CBC        	0x0200032c	// 02000300, wbregs names: FPGACBC
#define	R_CFG_IDCODE     	0x02000330	// 02000300, wbregs names: FPGAIDCODE
#define	R_CFG_AXSS       	0x02000334	// 02000300, wbregs names: FPGAAXSS
#define	R_CFG_COR1       	0x02000338	// 02000300, wbregs names: FPGACOR1
#define	R_CFG_WBSTAR     	0x02000340	// 02000300, wbregs names: WBSTAR
#define	R_CFG_TIMER      	0x02000344	// 02000300, wbregs names: CFGTIMER
#define	R_CFG_BOOTSTS    	0x02000358	// 02000300, wbregs names: BOOTSTS
#define	R_CFG_CTL1       	0x02000360	// 02000300, wbregs names: FPGACTL1
#define	R_CFG_BSPI       	0x0200037c	// 02000300, wbregs names: FPGABSPI
// CPU Net Controller registers
#define	R_CPUNET         	0x02000380	// 02000380, wbregs names: CPUNET
#define	R_CPUNETMAC1     	0x02000384	// 02000380, wbregs names: CPUMAC1
#define	R_CPUNETMAC2     	0x02000388	// 02000380, wbregs names: CPUMAC2
#define	R_CPUNETIPV4     	0x0200038c	// 02000380, wbregs names: CPUIPV4
#define	R_CPUNETIPV6P1   	0x02000390	// 02000380, wbregs names: CPUIP6P1
#define	R_CPUNETIPV6P2   	0x02000394	// 02000380, wbregs names: CPUIP6P2
#define	R_CPUNETIPV6P3   	0x02000398	// 02000380, wbregs names: CPUIP6P3
#define	R_CPUNETIPV6P4   	0x0200039c	// 02000380, wbregs names: CPUIP6P4
#define	R_CPUNETRXDROPS  	0x020003a0	// 02000380, wbregs names: RXDROPS
#define	R_CPUNETRXPKTS   	0x020003a4	// 02000380, wbregs names: RXPKTS
#define	R_CPUNETTXPKTS   	0x020003a8	// 02000380, wbregs names: TXPKTS
#define	R_CPUNETTX_BASE  	0x020003c0	// 02000380, wbregs names: CNTXBASE, CPUNETTXBASE
#define	R_CPUNETTX_LEN   	0x020003c4	// 02000380, wbregs names: CNTXLEN, CPUNETTXLEN
#define	R_CPUNETTX_RPTR  	0x020003c8	// 02000380, wbregs names: CNTXRPTR, CPUNETTXRPTR
#define	R_CPUNETTX_WPTR  	0x020003cc	// 02000380, wbregs names: CNTXWPTR, CPUNETTXWPTR
#define	R_CPUNETRX_BASE  	0x020003d0	// 02000380, wbregs names: CNRXBASE, CPUNETRXBASE
#define	R_CPUNETRX_LEN   	0x020003d4	// 02000380, wbregs names: CNRXLEN, CPUNETRXLEN
#define	R_CPUNETRX_RPTR  	0x020003d8	// 02000380, wbregs names: CNRXRPTR, CPUNETRXRPTR
#define	R_CPUNETRX_WPTR  	0x020003dc	// 02000380, wbregs names: CNRXWPTR, CPUNETRXWPTR
#define	R_CPUNETRX_DBG   	0x020003e0	// 02000380, wbregs names: CNRXDBG, CPUNETRXDBG
#define	R_CPUNETTX_DBG   	0x020003e4	// 02000380, wbregs names: CNTXDBG, CPUNETTXDBG
// I2C Controller registers
#define	R_I2CCPU         	0x02000400	// 02000400, wbregs names: I2CCPU, I2CCPU_CTRL, I2CCPUCTRL
#define	R_I2CCPU_OVW     	0x02000404	// 02000400, wbregs names: I2CCPU_OVW, I2CCPU_OVERRIDE
#define	R_I2CCPU_ADDR    	0x02000408	// 02000400, wbregs names: I2CCPU_ADDR, I2CCPU_ADDRESS
#define	R_I2CCPU_CKCOUNT 	0x0200040c	// 02000400, wbregs names: I2CCPUCLK, I2CCPU_CKCOUNT
#define	R_I2CDMA         	0x02000410	// 02000410, wbregs names: I2CDMA
#define	R_I2CDMA_ADDR    	0x02000414	// 02000410, wbregs names: I2CDMAADDR
#define	R_I2CDMA_BASE    	0x02000418	// 02000410, wbregs names: I2CDMABASE
#define	R_I2CDMA_LEN     	0x0200041c	// 02000410, wbregs names: I2CDMALEN
#define	R_RXNETCK0       	0x02000420	// 02000420, wbregs names: RXNETCLK0, RXNETCK0
#define	R_RXNETCK1       	0x02000424	// 02000420, wbregs names: RXNETCLK1, RXNETCK1
#define	R_RXNETCK2       	0x02000428	// 02000420, wbregs names: RXNETCLK2, RXNETCK2
#define	R_RXNETCK3       	0x0200042c	// 02000420, wbregs names: RXNETCLK3, RXNETCK3
#define	R_TXNETCLK       	0x02000430	// 02000420, wbregs names: TXNETCLK
#define	R_BUILDTIME      	0x02000440	// 02000440, wbregs names: BUILDTIME
#define	R_GPIO           	0x02000444	// 02000444, wbregs names: GPIO, GPI, GPO
#define	R_NETDBG         	0x02000448	// 02000448, wbregs names: NETDBG
#define	R_NETLOCK        	0x0200044c	// 0200044c, wbregs names: NETLOCK
#define	R_NETRESET       	0x02000450	// 02000450, wbregs names: NETRESET
#define	R_SICLKFREQ      	0x02000454	// 02000454, wbregs names: SICLKFREQ
#define	R_SIREFCLK       	0x02000458	// 02000458, wbregs names: SIREFCLK
#define	R_SIREFFREQ      	0x0200045c	// 0200045c, wbregs names: SIREFFREQ
#define	R_SPIO           	0x02000460	// 02000460, wbregs names: SPIO
#define	R_VERSION        	0x02000464	// 02000464, wbregs names: VERSION
#define	R_ROUTER         	0x02000500	// 02000500, wbregs names: ROUTER
#define	R_ROUTER0        	0x02000500	// 02000500, wbregs names: ROUTER0
#define	R_ROUTERSZ0      	0x02000504	// 02000500, wbregs names: ROUTERSZ0
#define	R_ROUTERWR0      	0x02000508	// 02000500, wbregs names: ROUTERWR0
#define	R_ROUTERRD0      	0x0200050c	// 02000500, wbregs names: ROUTERRD0
#define	R_ROUTER1        	0x02000510	// 02000500, wbregs names: ROUTER1
#define	R_ROUTERSZ1      	0x02000514	// 02000500, wbregs names: ROUTERSZ1
#define	R_ROUTERWR1      	0x02000518	// 02000500, wbregs names: ROUTERWR1
#define	R_ROUTERRD1      	0x0200051c	// 02000500, wbregs names: ROUTERRD1
#define	R_ROUTER2        	0x02000520	// 02000500, wbregs names: ROUTER2
#define	R_ROUTERSZ2      	0x02000524	// 02000500, wbregs names: ROUTERSZ2
#define	R_ROUTERWR2      	0x02000528	// 02000500, wbregs names: ROUTERWR2
#define	R_ROUTERRD2      	0x0200052c	// 02000500, wbregs names: ROUTERRD2
#define	R_ROUTER3        	0x02000530	// 02000500, wbregs names: ROUTER3
#define	R_ROUTERSZ3      	0x02000534	// 02000500, wbregs names: ROUTERSZ3
#define	R_ROUTERWR3      	0x02000538	// 02000500, wbregs names: ROUTERWR3
#define	R_ROUTERRD3      	0x0200053c	// 02000500, wbregs names: ROUTERRD3
#define	R_ROUTERPK0      	0x02000540	// 02000500, wbregs names: ROUTERPK0
#define	R_ROUTERBY0      	0x02000544	// 02000500, wbregs names: ROUTERBY0
#define	R_ROUTERFP0      	0x02000548	// 02000500, wbregs names: ROUTERFP0
#define	R_ROUTERFB0      	0x0200054c	// 02000500, wbregs names: ROUTERFB0
#define	R_ROUTERPK1      	0x02000550	// 02000500, wbregs names: ROUTERPK1
#define	R_ROUTERBY1      	0x02000554	// 02000500, wbregs names: ROUTERBY1
#define	R_ROUTERFP1      	0x02000558	// 02000500, wbregs names: ROUTERFP1
#define	R_ROUTERFB1      	0x0200055c	// 02000500, wbregs names: ROUTERFB1
#define	R_ROUTERPK2      	0x02000560	// 02000500, wbregs names: ROUTERPK2
#define	R_ROUTERBY2      	0x02000564	// 02000500, wbregs names: ROUTERBY2
#define	R_ROUTERFP2      	0x02000568	// 02000500, wbregs names: ROUTERFP2
#define	R_ROUTERFB2      	0x0200056c	// 02000500, wbregs names: ROUTERFB2
#define	R_ROUTERPK3      	0x02000570	// 02000500, wbregs names: ROUTERPK3
#define	R_ROUTERBY3      	0x02000574	// 02000500, wbregs names: ROUTERBY3
#define	R_ROUTERFP3      	0x02000578	// 02000500, wbregs names: ROUTERFP3
#define	R_ROUTERFB3      	0x0200057c	// 02000500, wbregs names: ROUTERFB3
#define	R_ROUTERNWH0     	0x02000580	// 02000500, wbregs names: ROUTERNWH0
#define	R_ROUTERNWL0     	0x02000584	// 02000500, wbregs names: ROUTERNWL0
#define	R_ROUTERLKH0     	0x02000588	// 02000500, wbregs names: ROUTERLKH0
#define	R_ROUTERLKL0     	0x0200058c	// 02000500, wbregs names: ROUTERLKL0
#define	R_ROUTERNWH1     	0x02000590	// 02000500, wbregs names: ROUTERNWH1
#define	R_ROUTERNWL1     	0x02000594	// 02000500, wbregs names: ROUTERNWL1
#define	R_ROUTERLKH1     	0x02000598	// 02000500, wbregs names: ROUTERLKH1
#define	R_ROUTERLKL1     	0x0200059c	// 02000500, wbregs names: ROUTERLKL1
#define	R_ROUTERNWH2     	0x020005a0	// 02000500, wbregs names: ROUTERNWH2
#define	R_ROUTERNWL2     	0x020005a4	// 02000500, wbregs names: ROUTERNWL2
#define	R_ROUTERLKH2     	0x020005a8	// 02000500, wbregs names: ROUTERLKH2
#define	R_ROUTERLKL2     	0x020005ac	// 02000500, wbregs names: ROUTERLKL2
#define	R_ROUTERNWH3     	0x020005b0	// 02000500, wbregs names: ROUTERNWH3
#define	R_ROUTERNWL3     	0x020005b4	// 02000500, wbregs names: ROUTERNWL3
#define	R_ROUTERLKH3     	0x020005b8	// 02000500, wbregs names: ROUTERLKH3
#define	R_ROUTERLKL3     	0x020005bc	// 02000500, wbregs names: ROUTERLKL3
#define	R_ROUTERNWH4     	0x020005c0	// 02000500, wbregs names: ROUTERNWH4
#define	R_ROUTERNWL4     	0x020005c4	// 02000500, wbregs names: ROUTERNWL4
#define	R_ROUTERLKH4     	0x020005c8	// 02000500, wbregs names: ROUTERLKH4
#define	R_ROUTERLKL4     	0x020005cc	// 02000500, wbregs names: ROUTERLKL4
#define	R_ROUTERDBG0     	0x020005d0	// 02000500, wbregs names: ROUTERDBG0
#define	R_ROUTERDBG1     	0x020005d4	// 02000500, wbregs names: ROUTERDBG1
#define	R_ROUTERDBG2     	0x020005d8	// 02000500, wbregs names: ROUTERDBG2
#define	R_ROUTERDBG3     	0x020005dc	// 02000500, wbregs names: ROUTERDBG3
#define	R_ROUTERDBG4     	0x020005e0	// 02000500, wbregs names: ROUTERDBG4
#define	R_ROUTERNEVER    	0x020005e8	// 02000500, wbregs names: ROUTERNV, RTNEVER
#define	R_ROUTERALWAYS   	0x020005ec	// 02000500, wbregs names: ROUTERAL, RTALWAYS
#define	R_ROUTERDBGS     	0x020005fc	// 02000500, wbregs names: ROUTERDBGS
#define	R_DDR3_PHY       	0x02000600	// 02000600, wbregs names: DDR3_PHY
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
#define	R_ZIPU10         	0x800000e8	// 80000000, wbregs names: UR10
#define	R_ZIPU11         	0x800000ec	// 80000000, wbregs names: UR11
#define	R_ZIPU12         	0x800000f0	// 80000000, wbregs names: UR12, UFP
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
