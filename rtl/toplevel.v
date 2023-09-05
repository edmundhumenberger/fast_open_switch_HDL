////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./toplevel.v
// {{{
// Project:	10Gb Ethernet switch
//
// DO NOT EDIT THIS FILE!
// Computer Generated: This file is computer generated by AUTOFPGA. DO NOT EDIT.
// DO NOT EDIT THIS FILE!
//
// CmdLine:	autofpga -I .: -d -o . allclocks.txt siclk.txt sirefclk.txt global.txt wbdown.txt icape.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt bkram.txt sdio.txt emmc.txt netrouter.txt cpunet.txt hdmi.txt cec.txt edid.txt netscope.txt hdmiclrscope.txt mem_bkram_only.txt mem_flash_bkram.txt i2ccpu.txt fan.txt netclk.txt sirefclkcounter.txt
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
`default_nettype	none


//
// Here we declare our toplevel.v (toplevel) design module.
// All design logic must take place beneath this top level.
//
// The port declarations just copy data from the @TOP.PORTLIST
// key, or equivalently from the @MAIN.PORTLIST key if
// @TOP.PORTLIST is absent.  For those peripherals that don't need
// any top level logic, the @MAIN.PORTLIST should be sufficent,
// so the @TOP.PORTLIST key may be left undefined.
//
// The only exception is that any clocks with CLOCK.TOP tags will
// also appear in this list
//
module	toplevel(
			io_temp_sda, io_temp_scl,
			o_fan_pwm, o_fan_sys, i_fan_tach,
			io_i2c_sda, io_i2c_scl,
			o_i2c_mxrst_n,
		// SPIO interface
		i_sw, i_nbtn_u, i_nbtn_l, i_nbtn_c, i_nbtn_r, i_nbtn_d, o_led,
		// SDIO SD Card
o_sdcard_clk,
i_sdcard_cd_n,

		io_sdcard_cmd, io_sdcard_dat,
		// GPIO ports
		i_pi_reset_n, i_soft_reset, i_hdmitx_hpd_n,
		o_tp, o_si5324_rst, i_si5324_int,
		o_hdmirx_hpd_n,
		// UART/host to wishbone interface
		i_wbu_uart_rx, o_wbu_uart_tx,
		o_wbu_uart_cts_n,
		i_clk_200mhz_p, i_clk_200mhz_n,
		io_siref_clk_p, io_siref_clk_n,
		// cec ports
		io_hdmirx_cec, io_hdmitx_cec,
		i_clk_si_p, i_clk_si_n,
		i_hdmirx_clk_p, i_hdmirx_clk_n,
		i_hdmirx_p, i_hdmirx_n,
		o_hdmitx_clk_p, o_hdmitx_clk_n,
		o_hdmitx_p, o_hdmitx_n,
		// eMMC Card


		i_emmc_ds,

		io_emmc_cmd, io_emmc_dat,
			i_gnet_los, o_gnettx_disable,
			o_gnet_linkup, o_gnet_activity,
			o_gnet_p, o_gnet_n,
			i_gnet_p, i_gnet_n,
			i_clk_156mhz_p, i_clk_156mhz_n,
			io_hdmirx_scl, io_hdmirx_sda);
	//
	// Declaring any top level parameters.
	//
	// These declarations just copy data from the @TOP.PARAM key,
	// or from the @MAIN.PARAM key if @TOP.PARAM is absent.  For
	// those peripherals that don't do anything at the top level,
	// the @MAIN.PARAM key should be sufficient, so the @TOP.PARAM
	// key may be left undefined.
	//
	localparam	ICAPE_LGDIV=3;
	////////////////////////////////////////////////////////////////////////
	//
	// WBUBUS parameters
	// {{{
	// Baudrate :   1000000
	// Clock    : 100000000
	localparam [23:0] BUSUART = 24'h64;	//   1000000 baud
	localparam	DBGBUSBITS = $clog2(BUSUART);
	//
	// Maximum command is 6 bytes, where each byte takes 10 baud clocks
	// and each baud clock requires DBGBUSBITS to represent.  Here,
	// we'll add one more for good measure.
	localparam	DBGBUSWATCHDOG_RAW = DBGBUSBITS + 9;
	localparam	DBGBUSWATCHDOG = (DBGBUSWATCHDOG_RAW > 19)
				? DBGBUSWATCHDOG_RAW : 19;
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Variables/definitions/parameters used by the ZipCPU bus master
	// {{{
	//
	// A 32-bit address indicating where the ZipCPU should start running
	// from
`ifdef	BKROM_ACCESS
	localparam	RESET_ADDRESS = @$(/bkrom.BASE);
`else
`ifdef	FLASH_ACCESS
	localparam	RESET_ADDRESS = @$RESET_ADDRESS;
`else
	localparam	RESET_ADDRESS = 524288;
`endif	// FLASH_ACCESS
`endif	// BKROM_ACCESS
	//
	// The number of valid bits on the bus
	localparam	ZIP_ADDRESS_WIDTH = 14; // Zip-CPU address width
	//
	// Number of ZipCPU interrupts
	localparam	ZIP_INTS = 16;
	//
	// ZIP_START_HALTED
	//
	// A boolean, indicating whether or not the ZipCPU be halted on startup?
`ifdef	BKROM_ACCESS
	localparam	ZIP_START_HALTED=1'b0;
`else
	localparam	ZIP_START_HALTED=1'b1;
`endif
	// }}}
	localparam	NETDEVS = 4;
	//
	// Declaring our input and output ports.  We listed these above,
	// now we are declaring them here.
	//
	// These declarations just copy data from the @TOP.IODECLS key,
	// or from the @MAIN.IODECL key if @TOP.IODECL is absent.  For
	// those peripherals that don't do anything at the top level,
	// the @MAIN.IODECL key should be sufficient, so the @TOP.IODECL
	// key may be left undefined.
	//
	// We start with any @CLOCK.TOP keys
	//
	inout	wire	io_temp_sda, io_temp_scl;
	output	wire	o_fan_pwm, o_fan_sys;
	input	wire	i_fan_tach;
	inout	wire	io_i2c_sda, io_i2c_scl;
	output	wire	o_i2c_mxrst_n;
	// SPIO interface
	input	wire	[8-1:0]	i_sw;
	input	wire	i_nbtn_c, i_nbtn_d, i_nbtn_l, i_nbtn_r, i_nbtn_u;
	output	wire	[8-1:0]	o_led;
	// SDIO SD Card
	// {{{
	output	wire		o_sdcard_clk;


	input	wire		i_sdcard_cd_n;

	inout	wire		io_sdcard_cmd;
	inout	wire	[4-1:0]	io_sdcard_dat;
	// }}}
	// GPIO wires
	input	wire		i_pi_reset_n, i_soft_reset, i_hdmitx_hpd_n;
	output	wire	[3:0]	o_tp;
	output	wire		o_si5324_rst, o_hdmirx_hpd_n;
	input	wire		i_si5324_int;
	input	wire		i_wbu_uart_rx;
	output	wire		o_wbu_uart_tx;
	// input wire		i_wbu_uart_rts_n; // FT*'s perspective
	output wire		o_wbu_uart_cts_n;
	input	wire	i_clk_200mhz_p, i_clk_200mhz_n;
	inout	wire	io_siref_clk_p, io_siref_clk_n;
	// CEC wires
	inout	wire		io_hdmirx_cec, io_hdmitx_cec;
	input	wire	i_clk_si_p, i_clk_si_n;
	input	wire		i_hdmirx_clk_p, i_hdmirx_clk_n;
	input	wire	[2:0]	i_hdmirx_p, i_hdmirx_n;
	output	wire		o_hdmitx_clk_p, o_hdmitx_clk_n;
	output	wire	[2:0]	o_hdmitx_p, o_hdmitx_n;
	// eMMC Card
	// {{{

	input	wire		i_emmc_ds;


	inout	wire		io_emmc_cmd;
	inout	wire	[8-1:0]	io_emmc_dat;
	// }}}
	// 10Gb Ethernet
	input	wire	[4-1:0]	i_gnet_los;
	output	wire	[4-1:0]	o_gnettx_disable;
	output	wire	[4-1:0]	o_gnet_linkup;
	output	wire	[4-1:0]	o_gnet_activity;
	output	wire	[4-1:0]	o_gnet_p, o_gnet_n;
	input	wire	[4-1:0]	i_gnet_p, i_gnet_n;
	input	wire			i_clk_156mhz_p, i_clk_156mhz_n;
	inout	wire	io_hdmirx_scl, io_hdmirx_sda;


	//
	// Declaring component data, internal wires and registers
	//
	// These declarations just copy data from the @TOP.DEFNS key
	// within the component data files.
	//
	// FAN definitions
	// {{{
	wire	i_fan_sda, i_fan_scl,
		o_fan_sda, o_fan_scl;
	// }}}
	// I2CCPU definitions
	// {{{
	wire	i_i2c_sda, i_i2c_scl,
		o_i2c_sda, o_i2c_scl;
	reg		r_i2c_mxrst_n;
	reg	[2:0]	r_i2c_mxrst_dly;
	// }}}
	wire	[8-1:0]	w_led;
	wire	[5-1:0]	w_btn;
	// SDIO SD Card definitions
	// {{{
	wire		w_sdio_cfg_ddr;
	wire		w_sdio_cfg_ds, w_sdio_cfg_dscmd;
	wire	[4:0]	w_sdio_cfg_sample_shift;
	wire		w_sdio_pp_cmd;
	wire		w_sdio_pp_data;
		//
	wire	[7:0]	w_sdio_sdclk;
	wire		w_sdio_cmd_en;
	wire	[1:0]	w_sdio_cmd_data;
	wire		w_sdio_data_en;
	wire		w_sdio_rx_en;
	wire	[31:0]	w_sdio_tx_data;
		//
	wire	[1:0]	w_sdio_cmd_strb;
	wire	[1:0]	w_sdio_cmd_idata;
	wire		w_sdio_card_busy;
	wire	[1:0]	w_sdio_rx_strb;
	wire	[15:0]	w_sdio_rx_data;
		//
	wire		w_sdio_ac_valid;
	wire	[1:0]	w_sdio_ac_data;
	wire		w_sdio_ad_valid;
	wire	[31:0]	w_sdio_ad_data;

	wire		w_sdio_ck;
	wire		w_sdio_ds;
	wire	[31:0]	w_sdio_debug;
	// }}}

	// GPIO declarations.  The two wire busses are just virtual lists of
	// input (or output) ports.
	wire	[16-1:0]	i_gpio;
	wire	[8-1:0]	o_gpio;
	wire	s_clk200;
	wire		s_clk, s_reset, sysclk_locked, s_clk_nobuf,
			clk_feedback, clk_feedback_bufd,
			s_lcl_pixclk_nobuf, s_clk4x_unbuffered,
			s_clk300_nobuf, s_clk300;
	reg	[2:0]	pipe_reset;
	reg	[6:0]	refdly_reset_ctr;
	wire		refdly_ready;
	// Verilator lint_off UNUSED
	wire		ign_cpu_stall, ign_cpu_ack;
	wire	[31:0]	ign_cpu_idata;
`ifdef	VERILATOR
	wire		ign_cpu_prof_stb;
	wire	[14+$clog2(512/8)-1:0] ign_cpu_prof_addr;
	wire [31:0]	ign_cpu_prof_ticks;
`endif
	// Verilator lint_on  UNUSED
	// Definitions for the clock generation circuit
	wire		s_sirefclk_clk, w_sirefclk_ce;
			// w_sirefclk_pll_locked	-- not used at present
	wire		s_clk4x; // s_clk4x_unbuffered,
			// s_clksync, s_clksync_unbuffered;
	wire	[7:0]	w_sirefclk_word;
	// CEC declarations.
	wire	i_hdmirx_cec, i_hdmitx_cec;
	wire	o_hdmirx_cec, o_hdmitx_cec;
	wire	s_siclk_unbuf, s_siclk;
	wire	[9:0]	hdmirx_red, hdmirx_grn, hdmirx_blu;
	wire	[9:0]	hdmitx_red, hdmitx_grn, hdmitx_blu;
	wire	[1:0]	w_pxclk_sel;
	wire		hdmirx_clk, hdmi_ck, hdmi_serdes_clk;
	wire		pxrx_locked, pix_reset_n;
	wire [15-1:0]	set_hdmi_delay, actual_hdmi_delay;
	// eMMC Card definitions
	// {{{
	wire		w_emmc_cfg_ddr;
	wire		w_emmc_cfg_ds, w_emmc_cfg_dscmd;
	wire	[4:0]	w_emmc_cfg_sample_shift;
	wire		w_emmc_pp_cmd;
	wire		w_emmc_pp_data;
		//
	wire	[7:0]	w_emmc_sdclk;
	wire		w_emmc_cmd_en;
	wire	[1:0]	w_emmc_cmd_data;
	wire		w_emmc_data_en;
	wire		w_emmc_rx_en;
	wire	[31:0]	w_emmc_tx_data;
		//
	wire	[1:0]	w_emmc_cmd_strb;
	wire	[1:0]	w_emmc_cmd_idata;
	wire		w_emmc_card_busy;
	wire	[1:0]	w_emmc_rx_strb;
	wire	[15:0]	w_emmc_rx_data;
		//
	wire		w_emmc_ac_valid;
	wire	[1:0]	w_emmc_ac_data;
	wire		w_emmc_ad_valid;
	wire	[31:0]	w_emmc_ad_data;

	wire		w_emmc_ck;
	wire		w_emmc_ds;
	wire	[31:0]	w_emmc_debug;
	// }}}

	wire	[3:0]	su_emmc_nc;	// Unused / noconnect wires
	wire	i_emmc_cd_n;

	assign	i_emmc_cd_n = 1'b0;
	// 10Gb Ethernet
	wire	[4-1:0]		gnet_rx_clk, gnet_tx_clk;
	wire	[32*4-1:0]	gnet_rx_data;
	wire	[32*4-1:0]	gnet_tx_data;
	wire	[4-1:0]		gnet_phy_fault;
	wire	[4:0]		gnet_locked;
	// I2CCPU definitions
	// {{{
	wire	i_edid_sda, i_edid_scl,
		o_edid_sda, o_edid_scl;
	// }}}


	//
	// Time to call the main module within main.v.  Remember, the purpose
	// of the main.v module is to contain all of our portable logic.
	// Things that are Xilinx (or even Altera) specific, or for that
	// matter anything that requires something other than on-off logic,
	// such as the high impedence states required by many wires, is
	// kept in this (toplevel.v) module.  Everything else goes in
	// main.v.
	//
	// We automatically place s_clk, and s_reset here.  You may need
	// to define those above.  (You did, didn't you?)  Other
	// component descriptions come from the keys @TOP.MAIN (if it
	// exists), or @MAIN.PORTLIST if it does not.
	//

	main	thedesign(s_clk, s_reset,
		// sirefclk
		s_sirefclk_clk,
		// FAN/fan
		i_fan_sda, i_fan_scl,
		o_fan_sda, o_fan_scl,
		o_fan_pwm, o_fan_sys, i_fan_tach,
		// I2CCPU
		i_i2c_sda, i_i2c_scl,
		o_i2c_sda, o_i2c_scl,
		i_sw, w_btn, w_led,
		// SDIO SD Card
		!i_sdcard_cd_n,
		//
		w_sdio_cfg_ddr,
		w_sdio_cfg_ds,
		w_sdio_cfg_dscmd,
		w_sdio_cfg_sample_shift,
		w_sdio_pp_cmd,
		w_sdio_pp_data,
		//
		w_sdio_sdclk,
		w_sdio_cmd_en,
		w_sdio_cmd_data,
		w_sdio_data_en,
		w_sdio_rx_en,
		w_sdio_tx_data,
		//
		w_sdio_cmd_strb,
		w_sdio_cmd_idata,
		w_sdio_card_busy,
		w_sdio_rx_strb,
		w_sdio_rx_data,
		//
		w_sdio_ac_valid,
		w_sdio_ac_data,
		w_sdio_ad_valid,
		w_sdio_ad_data,
		w_sdio_debug,
		// GPIO wires
		i_gpio, o_gpio,
		// UART/host to wishbone interface
		i_wbu_uart_rx, o_wbu_uart_tx,
		o_wbu_uart_cts_n,
		s_clk200,
		// (Unused) ZipCPU Simulation port
		1'b0, 1'b0, 1'b0, 7'h0, 32'h0,
		ign_cpu_stall, ign_cpu_ack, ign_cpu_idata,
`ifdef	VERILATOR
		ign_cpu_prof_stb, ign_cpu_prof_addr, ign_cpu_prof_ticks,
`endif
		// ZipCPU reset port
		s_reset,
		// Clock Generator ports
		w_sirefclk_word, w_sirefclk_ce,
		// CEC wires
		i_hdmirx_cec, o_hdmirx_cec,
		i_hdmitx_cec, o_hdmitx_cec,
		s_siclk,
		// HDMI control ports
		hdmirx_clk, hdmi_ck,	// Depending on s_siclk
		hdmirx_red, hdmirx_grn, hdmirx_blu,
		hdmitx_red, hdmitx_grn, hdmitx_blu,
		set_hdmi_delay, actual_hdmi_delay,
		pix_reset_n, pxrx_locked,
		w_pxclk_sel,
		// eMMC Card
		!i_emmc_cd_n,
		//
		w_emmc_cfg_ddr,
		w_emmc_cfg_ds,
		w_emmc_cfg_dscmd,
		w_emmc_cfg_sample_shift,
		w_emmc_pp_cmd,
		w_emmc_pp_data,
		//
		w_emmc_sdclk,
		w_emmc_cmd_en,
		w_emmc_cmd_data,
		w_emmc_data_en,
		w_emmc_rx_en,
		w_emmc_tx_data,
		//
		w_emmc_cmd_strb,
		w_emmc_cmd_idata,
		w_emmc_card_busy,
		w_emmc_rx_strb,
		w_emmc_rx_data,
		//
		w_emmc_ac_valid,
		w_emmc_ac_data,
		w_emmc_ad_valid,
		w_emmc_ad_data,
		w_emmc_debug,
		gnet_rx_clk, gnet_rx_data,
		gnet_tx_clk, gnet_tx_data,
		gnet_phy_fault, o_gnet_linkup, o_gnet_activity,
		i_gnet_los, gnet_locked,
		// I2CCPU
		i_edid_sda, i_edid_scl,
		o_edid_sda, o_edid_scl);


	//
	// Our final section to the toplevel is used to provide all of
	// that special logic that couldnt fit in main.  This logic is
	// given by the @TOP.INSERT tag in our data files.
	//


	////////////////////////////////////////////////////////////////////////
	//
	// FAN IO buffers
	// {{{

	// We need these in order to (properly) ensure the high impedance
	// states (pull ups) of the I2C I/O lines.  Our goals are:
	//
	//	o_fan_X	io_fan_X		Derived:T
	//	1'b0		1'b0			1'b0
	//	1'b1		1'bz			1'b1
	//
	IOBUF fansclp(
		// {{{
		.I(1'b0),
		.T(o_fan_scl),
		.O(i_fan_scl),
		.IO(io_temp_scl)
		// }}}
	);

	IOBUF fansdap(
		// {{{
		.I(1'b0),
		.T(o_fan_sda),
		.O(i_fan_sda),
		.IO(io_temp_sda)
		// }}}
	);
	// }}}

	////////////////////////////////////////////////////////////////////////
	//
	// I2C IO buffers
	// {{{

	// We need these in order to (properly) ensure the high impedance
	// states (pull ups) of the I2C I/O lines.  Our goals are:
	//
	//	o_i2c_X	io_i2c_X		Derived:T
	//	1'b0		1'b0			1'b0
	//	1'b1		1'bz			1'b1
	//
	IOBUF i2csclp(
		// {{{
		.I(1'b0),
		.T(o_i2c_scl),
		.O(i_i2c_scl),
		.IO(io_i2c_scl)
		// }}}
	);

	IOBUF i2csdap(
		// {{{
		.I(1'b0),
		.T(o_i2c_sda),
		.O(i_i2c_sda),
		.IO(io_i2c_sda)
		// }}}
	);

	initial	{ r_i2c_mxrst_n, r_i2c_mxrst_dly } = 0;
	always @(posedge s_clk or negedge sysclk_locked)
	if (!sysclk_locked)
		{ r_i2c_mxrst_n, r_i2c_mxrst_dly } <= 0;
	else
		{ r_i2c_mxrst_n, r_i2c_mxrst_dly } <= { r_i2c_mxrst_dly, 1'b1 };

	assign	o_i2c_mxrst_n = r_i2c_mxrst_n;
	// }}}

	assign	o_led = { w_led[8-1:2], (w_led[1] || !sysclk_locked),
			w_led[0] | s_reset };

	assign	w_btn = ~{ i_nbtn_u, i_nbtn_l, i_nbtn_c, i_nbtn_r, i_nbtn_d };

	sdfrontend #(
		.OPT_SERDES(1'b0),
		.OPT_DDR(1'b1),
		.NUMIO(4)
	) u_sdio_frontend (
		// {{{
		.i_clk(s_clk), .i_hsclk(s_clk4x), .i_reset(s_reset),
		// Configuration
		.i_cfg_ddr(w_sdio_cfg_ddr),
		.i_cfg_ds(w_sdio_cfg_ds),
		.i_cfg_dscmd(w_sdio_cfg_dscmd),
		.i_sample_shift(w_sdio_cfg_sample_shift),
		.i_pp_cmd(w_sdio_pp_cmd),
		.i_pp_data(w_sdio_pp_data),
		// Run-time inputs
		.i_sdclk(w_sdio_sdclk),
		.i_cmd_en(w_sdio_cmd_en),
		.i_cmd_data(w_sdio_cmd_data),
		.i_data_en(w_sdio_data_en),
		.i_rx_en(w_sdio_rx_en),
		.i_tx_data(w_sdio_tx_data),
		// Return values
		.o_cmd_strb(w_sdio_cmd_strb),
		.o_cmd_data(w_sdio_cmd_idata),
		.o_data_busy(w_sdio_card_busy),
		.o_rx_strb( w_sdio_rx_strb),
		.o_rx_data( w_sdio_rx_data),
		//
		.MAC_VALID(w_sdio_ac_valid),
		.MAC_DATA( w_sdio_ac_data),
		.MAD_VALID(w_sdio_ad_valid),
		.MAD_DATA( w_sdio_ad_data),
		// IO ports
		.o_ck(w_sdio_ck),
		.i_ds(w_sdio_ds),
		.io_cmd(io_sdcard_cmd),
		.io_dat(io_sdcard_dat),
		.o_debug(w_sdio_debug)
		// }}}
	);


	assign	o_sdcard_clk = w_sdio_ck;

	assign	w_sdio_ds    = 1'b0;


	////////////////////////////////////////////////////////////////////////
	//
	// GPIO adjustments
	// {{{
	// Set to '1' when there's something to say.  Hence, the reset
	//	inputs will be '1' when the reset is active, the HDMI detect
	//	will be '1' when an HDMI is detected, the PLL lock signals
	//	will be '1' when not locked, etc.
	assign	i_gpio = { 10'h0,
		!pxrx_locked,
		!i_hdmitx_hpd_n,
		i_si5324_int,!sysclk_locked,!i_pi_reset_n,i_soft_reset };
	assign	o_tp = o_gpio[3:0];
	assign	o_si5324_rst = o_gpio[4];
	assign	o_hdmirx_hpd_n = !o_gpio[5];
	// o_trace = o_gpio[6]; // But this is for simulation only, so ignore
	// o_error = o_gpio[7]; // SIM ONLY: Internal error detection
	// }}}

	////////////////////////////////////////////////////////////////////////
	//
	// 200MHz clock ingestion
	// {{{
	IBUFDS
	ibuf_ck200 (
		.I(i_clk_200mhz_p), .IB(i_clk_200mhz_n),
		.O(s_clk200)
	);
	// }}}

	////////////////////////////////////////////////////////////////////////
	//
	// Default clock setup
	// {{{
	// assign	s_clk=s_clk200;
	// assign	sysclk_locked = 1'b1;

	initial	pipe_reset = -1;
	always @(posedge s_clk or negedge sysclk_locked)
	if (!sysclk_locked)
		pipe_reset <= -1;
	else
		pipe_reset <= { pipe_reset[1:0], 1'b0 };

	assign	s_reset = pipe_reset[2];

	PLLE2_BASE #(
		.CLKFBOUT_MULT(6),		// 200MHz*6 => 1200MHz
		.CLKFBOUT_PHASE(0.0),
		.CLKIN1_PERIOD(5),
		.CLKOUT0_DIVIDE(12),		// Divide by 2x
		.CLKOUT1_DIVIDE(3),		// Multiply by 2x
		.CLKOUT2_DIVIDE(14),		// Multiply by 6/14
		.CLKOUT3_DIVIDE(4)		// Multiply by 3/2
	) u_syspll (
		.CLKOUT0(s_clk_nobuf),		// 100MHz
		.CLKOUT1(s_clk4x_unbuffered),	// 400MHz
		.CLKOUT2(s_lcl_pixclk_nobuf),	//  85.7MHz
		.CLKOUT3(s_clk300_nobuf),	// 300MHz
		//
		.CLKFBOUT(clk_feedback),
		.LOCKED(sysclk_locked),
		.CLKIN1(s_clk200),	// 200MHz
		.PWRDWN(1'b0),
		.CLKFBIN(clk_feedback_bufd)
	);

	BUFG	feedback_buffer(.I(clk_feedback), .O(clk_feedback_bufd));
	BUFG	sysclk_buffer(.I(s_clk_nobuf), .O(s_clk));
	BUFG	clk300_buf(.I(s_clk300_nobuf), .O(s_clk300));
	// BUFG	sysclk_buffer(.I(s_lcl_pixclk_nobuf), .O(s_lcl_pixclk));

	// IDELAYCTRL
	// {{{
	// Min reset width of 52ns, or 9 clocks at 150MHz
	always @(posedge s_clk300 or negedge sysclk_locked)
	if (!sysclk_locked)
		refdly_reset_ctr <= 0;
	else if (!refdly_reset_ctr[5])
		refdly_reset_ctr <= refdly_reset_ctr + 1;

	IDELAYCTRL
	u_dlyctrl (.REFCLK(s_clk300), .RST(refdly_reset_ctr[5]),
		.RDY(refdly_ready));
	// }}}
	// }}}

	////////////////////////////////////////////////////////////////////////
	//
	// Clock generator for the Si5324
	// {{{
/*
	PLLE2_BASE #(
		// {{{
		.CLKFBOUT_MULT(8),
		.CLKFBOUT_PHASE(0.0),
		.CLKIN1_PERIOD(10),
		.CLKOUT0_DIVIDE(4),
		.CLKOUT1_DIVIDE(2)
		// }}}
	) gen_sysclk(
		// {{{
		.CLKIN1(i_clk),
		.CLKOUT0(s_clk_200mhz_unbuffered),
		.CLKOUT1(s_clk4x_unbuffered),
		.PWRDWN(1'b0), .RST(1'b0),
		.CLKFBOUT(sysclk_feedback),
		.CLKFBIN(sysclk_feedback),
		.LOCKED(sysclk_locked)
		// }}}
	);
*/
	// BUFG	clksync_buf(.I(s_clksync_unbuffered), .O(s_clk));
	BUFG	clk4x_buf(.I(s_clk4x_unbuffered), .O(s_clk4x));

	xgenclk #(
		.OPT_LCLCLOCK(1'b1)
	) u_xsirefclk(
		// {{{
		.i_clk(s_clk), .i_hsclk(s_clk4x),
		.i_ce(w_sirefclk_ce),
		.i_word(w_sirefclk_word),
		.o_pin({ io_siref_clk_p, io_siref_clk_n }),
		.o_clk(s_sirefclk_clk)
		// }}}
	);
	// }}}

	// CEC logic
	IOBUF hdmirx_cec (.T(o_hdmirx_cec), .I(1'b0), .O(i_hdmirx_cec), .IO(io_hdmirx_cec));
	IOBUF hdmitx_cec (.T(o_hdmitx_cec), .I(1'b0), .O(i_hdmitx_cec), .IO(io_hdmitx_cec));

	IBUFDS_GTE2
	u_siclk_buf(
		.I(i_clk_si_p), .IB(i_clk_si_n),
		.CEB(1'b0),
		.O(s_siclk_unbuf)
	);

	BUFG
	u_siclk_bufg (
		.I(s_siclk_unbuf),
		.O(s_siclk)
	);

	////////////////////////////////////////////////////////////////////////
	//
	// HDMI
	// {{{

	// Start with clock generation and propagation
	// {{{
	xpxclk
	u_xpxclk (
		.i_sysclk(s_clk),		// System clock
		.i_cksel(w_pxclk_sel),		// Clock select switch
		//
		.i_hdmirx_clk_p(i_hdmirx_clk_p),	// HDMI RX input clock
		.i_hdmirx_clk_n(i_hdmirx_clk_n),
		.i_lcl_pixclk(s_lcl_pixclk_nobuf),	// Locally generated clk
		.i_siclk(s_siclk),			// Si5324 clock
		//
		.o_hdmick_locked(pxrx_locked),
		.o_hdmirx_clk(hdmirx_clk),	// Clk for measurement only
		.o_pixclk(hdmi_ck),		// Pixel clock
		.o_hdmick(hdmi_serdes_clk)	// HS pixel clock
	);
	// }}}

	// Ingest the HDMI data lines
	// {{{
	xhdmiin
	u_hdmirx_red(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_delay(set_hdmi_delay[14:10]),
		.o_delay(actual_hdmi_delay[14:10]),
		.i_hs_wire({ i_hdmirx_p[2], i_hdmirx_n[2] }),
		.o_word(hdmirx_red)
	);

	xhdmiin
	u_hdmirx_grn(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_delay(set_hdmi_delay[9:5]),
		.o_delay(actual_hdmi_delay[9:5]),
		.i_hs_wire({ i_hdmirx_p[1], i_hdmirx_n[1] }),
		.o_word(hdmirx_grn)
	);

	xhdmiin
	u_hdmirx_blu(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_delay(set_hdmi_delay[4:0]),
		.o_delay(actual_hdmi_delay[4:0]),
		.i_hs_wire({ i_hdmirx_p[0], i_hdmirx_n[0] }),
		.o_word(hdmirx_blu)
	);
	// }}}

	// Output the HDMI TX data lines
	// {{{
	xhdmiout
	u_hdmitx_clk(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_word(10'b11111_00000),
		.o_port({ o_hdmitx_clk_p, o_hdmitx_clk_n })
	);

	xhdmiout
	u_hdmitx_red(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_word(hdmitx_red),
		.o_port({ o_hdmitx_p[2], o_hdmitx_n[2] })
	);

	xhdmiout
	u_hdmitx_grn(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_word(hdmitx_grn),
		.o_port({ o_hdmitx_p[1], o_hdmitx_n[1] })
	);

	xhdmiout
	u_hdmitx_blu(
		.i_clk(hdmi_ck), .i_hsclk(hdmi_serdes_clk),
		.i_reset_n(pix_reset_n),
		.i_word(hdmitx_blu),
		.o_port({ o_hdmitx_p[0], o_hdmitx_n[0] })
	);
	// }}}

	// }}}

	sdfrontend #(
		.OPT_SERDES(1'b0),
		.OPT_DDR(1'b0),
		.NUMIO(8)
	) u_emmc_frontend (
		// {{{
		.i_clk(s_clk), .i_hsclk(s_clk4x), .i_reset(s_reset),
		// Configuration
		.i_cfg_ddr(w_emmc_cfg_ddr),
		.i_cfg_ds(w_emmc_cfg_ds),
		.i_cfg_dscmd(w_emmc_cfg_dscmd),
		.i_sample_shift(w_emmc_cfg_sample_shift),
		.i_pp_cmd(w_emmc_pp_cmd),
		.i_pp_data(w_emmc_pp_data),
		// Run-time inputs
		.i_sdclk(w_emmc_sdclk),
		.i_cmd_en(w_emmc_cmd_en),
		.i_cmd_data(w_emmc_cmd_data),
		.i_data_en(w_emmc_data_en),
		.i_rx_en(w_emmc_rx_en),
		.i_tx_data(w_emmc_tx_data),
		// Return values
		.o_cmd_strb(w_emmc_cmd_strb),
		.o_cmd_data(w_emmc_cmd_idata),
		.o_data_busy(w_emmc_card_busy),
		.o_rx_strb( w_emmc_rx_strb),
		.o_rx_data( w_emmc_rx_data),
		//
		.MAC_VALID(w_emmc_ac_valid),
		.MAC_DATA( w_emmc_ac_data),
		.MAD_VALID(w_emmc_ad_valid),
		.MAD_DATA( w_emmc_ad_data),
		// IO ports
		.o_ck(w_emmc_ck),
		.i_ds(w_emmc_ds),
		.io_cmd(io_emmc_cmd),
		.io_dat(io_emmc_dat),
		.o_debug(w_emmc_debug)
		// }}}
	);


	STARTUPE2 #(
		// {{{
		// Leave PROG_USR false to avoid activating the program
		// event security feature.  Notes state that such a feature
		// requires encrypted bitstreams.
		.PROG_USR("FALSE"),
		// Sets the configuration clock frequency (in ns) for
		// simulation.
		.SIM_CCLK_FREQ(0.0)
		// }}}
	) STARTUPE2_inst (
		// CFGCLK, 1'b output: Config main clock output -- no connect
		.CFGCLK(su_emmc_nc[0]),
		// CFGMCLK, 1'b output: Config internal oscillator clock output
		.CFGMCLK(su_emmc_nc[1]),
		// EOS, 1'b: Active high output indicating the End Of Startup.
		.EOS(su_emmc_nc[2]),
		// PREQ, 1'b output: PROGRAM request to fabric output
		//	Only enabled if PROG_USR is set.  This lets the fabric
		//	know that a request has been made (either JTAG or pin
		//	pulled low) to program the device
		.PREQ(su_emmc_nc[3]),
		// CLK, 1'b input: User start-up clock input
		.CLK(1'b0),
		// GSR, 1'b input: Global Set/Reset input
		.GSR(1'b0),
		// GTS, 1'b input: Global 3-state input
		.GTS(1'b0),
		// KEYCLEARB, 1'b input: Clear AES Decrypter Key from BBRAM
		.KEYCLEARB(1'b0),
		// PACK, 1-bit input: PROGRAM acknowledge input
		//	This pin is only enabled if PROG_USR is set.  This
		//	allows the FPGA to acknowledge a request for reprogram
		//	to allow the FPGA to get itself into a reprogrammable
		//	state first.
		.PACK(1'b0),
		// USRCLKO, 1-bit input: User CCLK input -- This is why I
		// am using this module at all--I need to drive the CCLK pin
		// as part of the (current) eMMC design
		.USRCCLKO(w_emmc_ck),
		// USRCCLKTS, 1'b input: User CCLK 3-state enable input
		//	An active high here places the clock into a high
		//	impedence state.  Since we wish to use the clock as an
		//	active output always, we drive this pin low.
		.USRCCLKTS(1'b0),
		// USRDONEO, 1'b input: User DONE pin output control
		//	Set this to "high" to make sure that the DONE LED pin
		//	is high.
		.USRDONEO(1'b1),
		// USRDONETS, 1'b input: User DONE 3-state enable output
		//	This enables the FPGA DONE pin to be active.  Setting
		//	this high sets the DONE pin to high impedence (normal
		//	DONE pin operation).  Setting it low allows the output
		//	of this pin to be driven by USRDONE0 above.
		.USRDONETS(1'b1)
	);

	// }}}

	assign	w_emmc_ds = i_emmc_ds;


	assign	o_gnettx_disable = 0;

	xgtxphy #(
		.NDEV(4)
	) u_gnet_gtx_phy (
		// {{{
		.i_wb_clk(s_clk),
		.o_phy_fault(gnet_phy_fault),
		.o_lock_status(gnet_locked),
		//
		.S_CLK(  gnet_tx_clk),
		.S_DATA( gnet_tx_data),
		//
		.M_CLK(  gnet_rx_clk),
		.M_DATA( gnet_rx_data),
		//
		.i_refck_p(i_clk_156mhz_p), .i_refck_n(i_clk_156mhz_n),
		.i_rx_p(i_gnet_p), .i_rx_n(i_gnet_n),
		.o_tx_p(o_gnet_p), .o_tx_n(o_gnet_n)
		// }}}
	);

	////////////////////////////////////////////////////////////////////////
	//
	// EDID I2C IO buffers
	// {{{

	// We need these in order to (properly) ensure the high impedance
	// states (pull ups) of the I2C I/O lines.  Our goals are:
	//
	//	o_edid_X	io_edid_X		Derived:T
	//	1'b0		1'b0			1'b0
	//	1'b1		1'bz			1'b1
	//
	IOBUF edidsclp(
		// {{{
		.I(1'b0),
		.T(o_edid_scl),
		.O(i_edid_scl),
		.IO(io_hdmirx_scl)
		// }}}
	);

	IOBUF edidsdap(
		// {{{
		.I(1'b0),
		.T(o_edid_sda),
		.O(i_edid_sda),
		.IO(io_hdmirx_sda)
		// }}}
	);

	// }}}



endmodule // end of toplevel.v module definition
