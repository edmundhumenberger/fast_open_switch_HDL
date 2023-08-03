////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./regdefs.cpp
// {{{
// Project:	10Gb Ethernet switch
//
// DO NOT EDIT THIS FILE!
// Computer Generated: This file is computer generated by AUTOFPGA. DO NOT EDIT.
// DO NOT EDIT THIS FILE!
//
// CmdLine:	autofpga -I .: -d -o . allclocks.txt global.txt wbdown.txt icape.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt bkram.txt sdio.txt emmc.txt netrouter.txt cpunet.txt sdioscope.txt emmcscope.txt netscope.txt mem_bkram_only.txt mem_flash_bkram.txt i2ccpu.txt fan.txt sirefclk.txt i2cscope.txt
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
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "regdefs.h"

const	REGNAME	raw_bregs[] = {
	{ R_EMMCSCOPE     ,	"EMMCSCOPE"      	},
	{ R_EMMCSCOPED    ,	"EMMCSCOPED"     	},
	{ R_I2CSCOPE      ,	"I2CSCOPE"       	},
	{ R_I2CSCOPED     ,	"I2CSCOPED"      	},
	{ R_NETSCOPE      ,	"NETSCOPE"       	},
	{ R_NETSCOPED     ,	"NETSCOPED"      	},
	{ R_SDIOSCOPE     ,	"SDIOSCOPE"      	},
	{ R_SDIOSCOPED    ,	"SDIOSCOPED"     	},
	{ R_I2CCPU        ,	"I2CCPU"         	},
	{ R_I2CCPU        ,	"I2CCPU_CTRL"    	},
	{ R_I2CCPU        ,	"I2CCPUCTRL"     	},
	{ R_I2CCPU_OVW    ,	"I2CCPU_OVW"     	},
	{ R_I2CCPU_OVW    ,	"I2CCPU_OVERRIDE"	},
	{ R_I2CCPU_ADDR   ,	"I2CCPU_ADDR"    	},
	{ R_I2CCPU_ADDR   ,	"I2CCPU_ADDRESS" 	},
	{ R_I2CCPU_CKCOUNT,	"I2CCPUCLK"      	},
	{ R_I2CCPU_CKCOUNT,	"I2CCPU_CKCOUNT" 	},
	{ R_I2CDMA        ,	"I2CDMA"         	},
	{ R_I2CDMA_ADDR   ,	"I2CDMAADDR"     	},
	{ R_I2CDMA_BASE   ,	"I2CDMABASE"     	},
	{ R_I2CDMA_LEN    ,	"I2CDMALEN"      	},
	{ R_CONSOLE_FIFO  ,	"UFIFO"          	},
	{ R_CONSOLE_UARTRX,	"RX"             	},
	{ R_CONSOLE_UARTTX,	"TX"             	},
	{ R_CPUNETRX_BASE ,	"CPUNETRXBASE"   	},
	{ R_CPUNETRX_LEN  ,	"CPUNETRXLEN"    	},
	{ R_CPUNETRX_RPTR ,	"CPUNETRXRPTR"   	},
	{ R_CPUNETRX_WPTR ,	"CPUNETRXWPTR"   	},
	{ R_EMMC_CTRL     ,	"EMMCCARD"       	},
	{ R_EMMC_DATA     ,	"EMMCDATA"       	},
	{ R_EMMC_FIFOA    ,	"EMMCFIFOA"      	},
	{ R_EMMC_FIFOA    ,	"EMMCFIF0"       	},
	{ R_EMMC_FIFOA    ,	"EMMCFIFA"       	},
	{ R_EMMC_FIFOB    ,	"EMMCFIFOB"      	},
	{ R_EMMC_FIFOB    ,	"EMMCFIF1"       	},
	{ R_EMMC_FIFOB    ,	"EMMCFIFB"       	},
	{ R_EMMC_PHY      ,	"EMMCPHY"        	},
	{ R_FAN_FPGAPWM   ,	"FAN_FPGAPWM"    	},
	{ R_FAN_SYSPWM    ,	"FAN_SYSPWM"     	},
	{ R_FAN_TACH      ,	"FAN_TACH"       	},
	{ R_FAN_TEMP      ,	"FAN_TEMP"       	},
	{ R_FAN           ,	"FAN_CTRL"       	},
	{ R_FAN_OVW       ,	"FAN_OVW"        	},
	{ R_FAN_OVW       ,	"FAN_OVERRIDE"   	},
	{ R_FAN_ADDR      ,	"FAN_ADDR"       	},
	{ R_FAN_ADDR      ,	"FAN_ADDRESS"    	},
	{ R_FAN_CKCOUNT   ,	"FANCLK"         	},
	{ R_FAN_CKCOUNT   ,	"FAN_CKCOUNT"    	},
	{ R_SDIO_CTRL     ,	"SDCARD"         	},
	{ R_SDIO_DATA     ,	"SDDATA"         	},
	{ R_SDIO_FIFOA    ,	"SDFIFOA"        	},
	{ R_SDIO_FIFOA    ,	"SDFIF0"         	},
	{ R_SDIO_FIFOA    ,	"SDFIFA"         	},
	{ R_SDIO_FIFOB    ,	"SDFIFOB"        	},
	{ R_SDIO_FIFOB    ,	"SDFIF1"         	},
	{ R_SDIO_FIFOB    ,	"SDFIFB"         	},
	{ R_SDIO_PHY      ,	"SDPHY"          	},
	{ R_BUILDTIME     ,	"BUILDTIME"      	},
	{ R_GPIO          ,	"GPIO"           	},
	{ R_GPIO          ,	"GPI"            	},
	{ R_GPIO          ,	"GPO"            	},
	{ R_NETDBG        ,	"NETDBG"         	},
	{ R_NETLOCK       ,	"NETLOCK"        	},
	{ R_SIREFCLK      ,	"SIREFCLK"       	},
	{ R_SPIO          ,	"SPIO"           	},
	{ R_VERSION       ,	"VERSION"        	},
	{ R_CFG_CRC       ,	"FPGACRC"        	},
	{ R_CFG_FAR       ,	"FPGAFAR"        	},
	{ R_CFG_FDRI      ,	"FPGAFDRI"       	},
	{ R_CFG_FDRO      ,	"FPGAFDRO"       	},
	{ R_CFG_CMD       ,	"FPGACMD"        	},
	{ R_CFG_CTL0      ,	"FPGACTL0"       	},
	{ R_CFG_MASK      ,	"FPGAMASK"       	},
	{ R_CFG_STAT      ,	"FPGASTAT"       	},
	{ R_CFG_LOUT      ,	"FPGALOUT"       	},
	{ R_CFG_COR0      ,	"FPGACOR0"       	},
	{ R_CFG_MFWR      ,	"FPGAMFWR"       	},
	{ R_CFG_CBC       ,	"FPGACBC"        	},
	{ R_CFG_IDCODE    ,	"FPGAIDCODE"     	},
	{ R_CFG_AXSS      ,	"FPGAAXSS"       	},
	{ R_CFG_COR1      ,	"FPGACOR1"       	},
	{ R_CFG_WBSTAR    ,	"WBSTAR"         	},
	{ R_CFG_TIMER     ,	"CFGTIMER"       	},
	{ R_CFG_BOOTSTS   ,	"BOOTSTS"        	},
	{ R_CFG_CTL1      ,	"FPGACTL1"       	},
	{ R_CFG_BSPI      ,	"FPGABSPI"       	},
	{ R_BKRAM         ,	"RAM"            	},
	{ R_ZIPCTRL       ,	"CPU"            	},
	{ R_ZIPCTRL       ,	"ZIPCTRL"        	},
	{ R_ZIPREGS       ,	"ZIPREGS"        	},
	{ R_ZIPS0         ,	"SR0"            	},
	{ R_ZIPS1         ,	"SR1"            	},
	{ R_ZIPS2         ,	"SR2"            	},
	{ R_ZIPS3         ,	"SR3"            	},
	{ R_ZIPS4         ,	"SR4"            	},
	{ R_ZIPS5         ,	"SR5"            	},
	{ R_ZIPS6         ,	"SR6"            	},
	{ R_ZIPS7         ,	"SR7"            	},
	{ R_ZIPS8         ,	"SR8"            	},
	{ R_ZIPS9         ,	"SR9"            	},
	{ R_ZIPS10        ,	"SR10"           	},
	{ R_ZIPS11        ,	"SR11"           	},
	{ R_ZIPS12        ,	"SR12"           	},
	{ R_ZIPSSP        ,	"SSP"            	},
	{ R_ZIPSSP        ,	"SR13"           	},
	{ R_ZIPCC         ,	"ZIPCC"          	},
	{ R_ZIPCC         ,	"CC"             	},
	{ R_ZIPCC         ,	"SCC"            	},
	{ R_ZIPCC         ,	"SR14"           	},
	{ R_ZIPPC         ,	"ZIPPC"          	},
	{ R_ZIPPC         ,	"PC"             	},
	{ R_ZIPPC         ,	"SPC"            	},
	{ R_ZIPPC         ,	"SR15"           	},
	{ R_ZIPUSER       ,	"ZIPUSER"        	},
	{ R_ZIPU0         ,	"UR0"            	},
	{ R_ZIPU1         ,	"UR1"            	},
	{ R_ZIPU2         ,	"UR2"            	},
	{ R_ZIPU3         ,	"UR3"            	},
	{ R_ZIPU4         ,	"UR4"            	},
	{ R_ZIPU5         ,	"UR5"            	},
	{ R_ZIPU6         ,	"UR6"            	},
	{ R_ZIPU7         ,	"UR7"            	},
	{ R_ZIPU8         ,	"UR8"            	},
	{ R_ZIPU9         ,	"UR9"            	},
	{ R_ZIPU10        ,	"SR10"           	},
	{ R_ZIPU11        ,	"SR11"           	},
	{ R_ZIPU12        ,	"SR12"           	},
	{ R_ZIPUSP        ,	"USP"            	},
	{ R_ZIPUSP        ,	"UR13"           	},
	{ R_ZIPUCC        ,	"ZIPUCC"         	},
	{ R_ZIPUCC        ,	"UCC"            	},
	{ R_ZIPUPC        ,	"ZIPUPC"         	},
	{ R_ZIPUPC        ,	"UPC"            	},
	{ R_ZIPSYSTEM     ,	"ZIPSYSTEM"      	},
	{ R_ZIPSYSTEM     ,	"ZIPSYS"         	},
	{ R_ZIPPIC        ,	"ZIPPIC"         	},
	{ R_ZIPWDOG       ,	"ZIPWDOG"        	},
	{ R_ZIPBDOG       ,	"ZIPBDOG"        	},
	{ R_ZIPAPIC       ,	"ZIPAPIC"        	},
	{ R_ZIPTIMA       ,	"ZIPTIMA"        	},
	{ R_ZIPTIMB       ,	"ZIPTIMB"        	},
	{ R_ZIPTIMC       ,	"ZIPTIMC"        	},
	{ R_ZIPJIFF       ,	"ZIPJIFF"        	},
	{ R_ZIPMTASK      ,	"ZIPMTASK"       	},
	{ R_ZIPMMSTL      ,	"ZIPMMSTL"       	},
	{ R_ZIPMPSTL      ,	"ZIPMPSTL"       	},
	{ R_ZIPMINSN      ,	"ZIPMINSN"       	},
	{ R_ZIPUTASK      ,	"ZIPUTASK"       	},
	{ R_ZIPUMSTL      ,	"ZIPUMSTL"       	},
	{ R_ZIPUPSTL      ,	"ZIPUPSTL"       	},
	{ R_ZIPUINSN      ,	"ZIPUINSN"       	},
	{ R_ZIPDMAC       ,	"ZIPDMAC"        	}
};

// REGSDEFS.CPP.INSERT for any bus masters
// And then from the peripherals
// And finally any master REGS.CPP.INSERT tags
#define	RAW_NREGS	(sizeof(raw_bregs)/sizeof(bregs[0]))

const	REGNAME		*bregs = raw_bregs;
const	int	NREGS = RAW_NREGS;

unsigned	addrdecode(const char *v) {
	if (isalpha(v[0])) {
		for(int i=0; i<NREGS; i++)
			if (strcasecmp(v, bregs[i].m_name)==0)
				return bregs[i].m_addr;
		fprintf(stderr, "Unknown register: %s\n", v);
		exit(-2);
	} else
		return strtoul(v, NULL, 0);
}

const	char *addrname(const unsigned v) {
	for(int i=0; i<NREGS; i++)
		if (bregs[i].m_addr == v)
			return bregs[i].m_name;
	return NULL;
}

