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
// CmdLine:	autofpga -I .: -d -o . allclocks.txt global.txt wbdown.txt icape.txt version.txt gpio.txt spio.txt wbuconsole.txt zipmaster.txt smiconsole.txt bkram.txt flash.txt sdio.txt smiscope.txt flashscope.txt fanscope.txt cfgscope.txt sdioscope.txt mem_bkram_only.txt mem_flash_bkram.txt i2ccpu.txt fan.txt sirefclk.txt i2cscope.txt netled.txt
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
		o_gnet_linkup, o_gnet_activity,
		o_siref_clk_p, o_siref_clk_n,
		// SPIO interface
		i_sw, i_nbtn_u, i_nbtn_l, i_nbtn_c, i_nbtn_r, i_nbtn_d, o_led,
		// GPIO ports
		i_pi_reset_n, i_soft_reset, i_hdmitx_hpd_n,
		o_tp, o_si5324_rst, i_si5324_int,
		o_hdmirx_hpd_n,
		// UART/host to wishbone interface
		i_wbu_uart_rx, o_wbu_uart_tx,
		o_wbu_uart_cts_n,
		i_clk_200mhz_p, i_clk_200mhz_n,
		// SMI
		i_smi_oen, i_smi_wen, i_smi_sa, io_smi_sd,
		// SDIO SD Card
		o_sdcard_clk, io_sdcard_cmd, io_sdcard_dat, i_sdcard_cd_n,
		// Top level Quad-SPI I/O ports
		o_flash_cs_n, io_flash_dat,
			io_i2c_sda, io_i2c_scl,
			o_i2c_mxrst_n,
			io_temp_sda, io_temp_scl,
			o_fan_pwm, o_fan_sys, i_fan_tach);
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
	localparam	RESET_ADDRESS = 48234496;
`else
	localparam	RESET_ADDRESS = 16777216;
`endif	// FLASH_ACCESS
`endif	// BKROM_ACCESS
	//
	// The number of valid bits on the bus
	localparam	ZIP_ADDRESS_WIDTH = 20; // Zip-CPU address width
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
	output	wire	[3:0]	o_gnet_linkup, o_gnet_activity;
	output	wire	o_siref_clk_p, o_siref_clk_n;
	// SPIO interface
	input	wire	[8-1:0]	i_sw;
	input	wire	i_nbtn_c, i_nbtn_d, i_nbtn_l, i_nbtn_r, i_nbtn_u;
	output	wire	[8-1:0]	o_led;
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
	// SMI
	input	wire		i_smi_oen, i_smi_wen;
	input	wire	[5:0]	i_smi_sa;
	inout	wire	[17:0]	io_smi_sd;
	// SDIO SD Card
	// {{{
	output	wire		o_sdcard_clk;
	inout	wire		io_sdcard_cmd;
	inout	wire	[4-1:0]	io_sdcard_dat;
	input	wire		i_sdcard_cd_n;
	// }}}
	// Quad SPI flash
	output	wire		o_flash_cs_n;
	inout	wire	[3:0]	io_flash_dat;
	inout	wire	io_i2c_sda, io_i2c_scl;
	output	wire	o_i2c_mxrst_n;
	inout	wire	io_temp_sda, io_temp_scl;
	output	wire	o_fan_pwm, o_fan_sys;
	input	wire	i_fan_tach;


	//
	// Declaring component data, internal wires and registers
	//
	// These declarations just copy data from the @TOP.DEFNS key
	// within the component data files.
	//
	// Definitions for the clock generation circuit
	wire		s_sirefclk_clk, w_sirefclk_pll_locked,
			w_sirefclk_ce;
	wire		s_clk4x; // s_clk4x_unbuffered,
			// s_clksync, s_clksync_unbuffered;
	wire	[7:0]	w_sirefclk_word;
	wire	[8-1:0]	w_led;
	wire	[5-1:0]	w_btn;
	// GPIO declarations.  The two wire busses are just virtual lists of
	// input (or output) ports.
	wire	[16-1:0]	i_gpio;
	wire	[8-1:0]	o_gpio;
	wire	s_clk200;
	wire		s_clk, s_reset, sysclk_locked, s_clk_nobuf,
			clk_feedback, clk_feedback_bufd,
			s_lcl_pixclk_nobuf, s_clk4x_unbuffered, s_clk300;
	reg	[2:0]	pipe_reset;
	reg	[6:0]	refdly_reset_ctr;
	wire		refdly_ready;
	// Verilator lint_off UNUSED
	wire		ign_cpu_stall, ign_cpu_ack;
	wire	[31:0]	ign_cpu_idata;
	// Verilator lint_on  UNUSED
	// SMI
	genvar		smi_gk;
	wire		w_smi_oen;
	wire	[17:0]	i_smi_sd;
	wire	[17:0]	o_smi_sd;
	// SDIO SD Card definitions
	// {{{
	wire	i_sdcard_ds;
	// }}}
	wire		w_flash_sck, w_flash_cs_n;
	wire	[1:0]	flash_bmod;
	wire	[3:0]	flash_dat;
	// I2CCPU definitions
	// {{{
	wire	i_i2c_sda, i_i2c_scl,
		o_i2c_sda, o_i2c_scl;
	reg		r_i2c_mxrst_n;
	reg	[2:0]	r_i2c_mxrst_dly;
	// }}}
	// FAN definitions
	// {{{
	wire	i_fan_sda, i_fan_scl,
		o_fan_sda, o_fan_scl;
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
		// 10Gb Ethernet LED controls
		o_gnet_linkup, o_gnet_activity,
		// Clock Generator ports
		w_sirefclk_word, w_sirefclk_ce,
		i_sw, w_btn, w_led,
		// GPIO wires
		i_gpio, o_gpio,
		// UART/host to wishbone interface
		i_wbu_uart_rx, o_wbu_uart_tx,
		o_wbu_uart_cts_n,
		s_clk200,
		// Reset wire for the ZipCPU
		1'b0, 1'b0, 1'b0, 7'h0, 32'h0,
		ign_cpu_stall, ign_cpu_ack, ign_cpu_idata, s_reset,
		// SMI bus control
		i_smi_oen, i_smi_wen, i_smi_sa,
		i_smi_sd, o_smi_sd, w_smi_oen,
		// SDIO SD Card
		o_sdcard_clk, i_sdcard_ds,
		io_sdcard_cmd, io_sdcard_dat,
		!i_sdcard_cd_n,
		// Quad SPI flash
		w_flash_cs_n, w_flash_sck, flash_dat, io_flash_dat, flash_bmod,
		// I2CCPU
		i_i2c_sda, i_i2c_scl,
		o_i2c_sda, o_i2c_scl,
		// FAN/fan
		i_fan_sda, i_fan_scl,
		o_fan_sda, o_fan_scl,
		o_fan_pwm, o_fan_sys, i_fan_tach);


	//
	// Our final section to the toplevel is used to provide all of
	// that special logic that couldnt fit in main.  This logic is
	// given by the @TOP.INSERT tag in our data files.
	//


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

	xgenclk
	u_xsirefclk(
		// {{{
		.i_clk(s_clk), .i_hsclk(s_clk4x),
		.i_ce(w_sirefclk_ce),
		.i_word(w_sirefclk_word),
		.o_pin({ o_siref_clk_p, o_siref_clk_n }),
		.o_clk(s_sirefclk_clk)
		// }}}
	);
	// }}}

	assign	o_led = { w_led[8-1:2], (w_led[1] || !sysclk_locked),
			w_led[0] | s_reset };

	assign	w_btn = ~{ i_nbtn_u, i_nbtn_l, i_nbtn_c, i_nbtn_r, i_nbtn_d };

	////////////////////////////////////////////////////////////////////////
	//
	// GPIO adjustments
	// {{{
	// Set to '1' when there's something to say.  Hence, the reset
	//	inputs will be '1' when the reset is active, the HDMI detect
	//	will be '1' when an HDMI is detected, the PLL lock signals
	//	will be '1' when not locked, etc.
	assign	i_gpio = { 11'h0,
		1'b0,	// Was pxrx_locked
		!i_hdmitx_hpd_n,
		i_si5324_int,!sysclk_locked,!i_pi_reset_n,i_soft_reset };
	assign	o_tp = o_gpio[3:0];
	assign	o_si5324_rst = o_gpio[4];
	assign	o_hdmirx_hpd_n = o_gpio[5];
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
		.CLKOUT2_DIVIDE(30),		// Divide by 5x
		.CLKOUT3_DIVIDE(4)		// Multiply by 3/2
	) u_syspll (
		.CLKOUT0(s_clk_nobuf),		// 100MHz
		.CLKOUT1(s_clk4x_unbuffered),	// 400MHz
		.CLKOUT2(s_lcl_pixclk_nobuf),	//  40MHz
		.CLKOUT3(s_clk300),		// 300MHz
		//
		.CLKFBOUT(clk_feedback),
		.LOCKED(sysclk_locked),
		.CLKIN1(s_clk200),	// 200MHz
		.PWRDWN(1'b0),
		.CLKFBIN(clk_feedback_bufd)
	);

	BUFG	feedback_buffer(.I(clk_feedback), .O(clk_feedback_bufd));
	BUFG	sysclk_buffer(.I(s_clk_nobuf), .O(s_clk));
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
	// SMI bi-directional IO handling
	// {{{
	generate for (smi_gk=0; smi_gk<18; smi_gk=smi_gk+1)
	begin : GEN_SMI
		IOBUF u_smiio (
			.I(o_smi_sd[smi_gk]),
			.O(i_smi_sd[smi_gk]),
			.T(w_smi_oen),
			.IO(io_smi_sd[smi_gk])
		);
	end endgenerate
	// }}}

	assign	i_sdcard_ds = 1'b0;

	////////////////////////////////////////////////////////////////////////
	//
	// QSPI Flash IO pin handling
	// {{{
	//
	// Wires for setting up the QSPI flash wishbone peripheral
	//
	//
	// QSPI)BMOD, Quad SPI bus mode, Bus modes are:
	//	0?	Normal serial mode, one bit in one bit out
	//	10	Quad SPI mode, going out
	//	11	Quad SPI mode coming from the device (read mode)
	assign io_flash_dat = (!flash_bmod[1])?({2'b11,1'bz,flash_dat[0]})
				:((flash_bmod[0])?(4'bzzzz):(flash_dat[3:0]));
	assign	o_flash_cs_n = w_flash_cs_n;

	/*
	IOBUF flash_dat0 (
		// {{{
		.I(o_flash_dat[0]),
		.T(flash_bmod == 2'b11),
		.O(i_flash_dat[0]),
		.IO(io_flash_dat[0])
		// }}}
	);

	IOBUF flash_dat1 (
		// {{{
		.I(o_flash_dat[1]),
		.T(flash_bmod != 2'b10),
		.O(i_flash_dat[1]),
		.IO(io_flash_dat[1])
		// }}}
	);

	IOBUF flash_dat2 (
		// {{{
		.I(!flash_bmod[1] || o_flash_dat[2]),
		.T(flash_bmod == 2'b11),
		.O(i_flash_dat[2]),
		.IO(io_flash_dat[2])
		// }}}
	);

	IOBUF flash_dat3 (
		// {{{
		.I(!flash_bmod[1] || o_flash_dat[3]),
		.T(flash_bmod == 2'b11),
		.O(i_flash_dat[3]),
		.IO(io_flash_dat[3])
		// }}}
	);
	*/

	// The following primitive is necessary in many designs order to gain
	// access to the o_flash_sck pin.  It's not necessary on the Arty,
	// simply because they provide two pins that can drive the QSPI
	// clock pin.
	wire	[3:0]	su_nc;	// Startup primitive, no connect
	STARTUPE2 #(
		// Leave PROG_USR false to avoid activating the program
		// event security feature.  Notes state that such a feature
		// requires encrypted bitstreams.
		.PROG_USR("FALSE"),
		// Sets the configuration clock frequency (in ns) for
		// simulation.
		.SIM_CCLK_FREQ(0.0)
	) STARTUPE2_inst (
		// CFGCLK, 1'b output: Config main clock output -- no connect
		.CFGCLK(su_nc[0]),
		// CFGMCLK, 1'b output: Config internal oscillator clock output
		.CFGMCLK(su_nc[1]),
		// EOS, 1'b: Active high output indicating the End Of Startup.
		.EOS(su_nc[2]),
		// PREQ, 1'b output: PROGRAM request to fabric output
		//	Only enabled if PROG_USR is set.  This lets the fabric
		//	know that a request has been made (either JTAG or pin
		//	pulled low) to program the device
		.PREQ(su_nc[3]),
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
		// USRCLKO, 1-bit input: User CCLK input -- This is why I am using this
		// module at all.
		.USRCCLKO(w_flash_sck),
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
		//	this active high sets the DONE pin to high impedence,
		//	setting it low allows the output of this pin to be as
		//	stated above.
		.USRDONETS(1'b1)
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



endmodule // end of toplevel.v module definition
