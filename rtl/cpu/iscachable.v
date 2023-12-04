////////////////////////////////////////////////////////////////////////////////
//
// Filename:	./iscachable.v
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
`default_nettype none
//
module iscachable(
		// {{{
		input	wire	[31-1:0]	i_addr,
		output	reg			o_cachable
		// }}}
	);

	always @(*)
	begin
		o_cachable = 1'b0;
		// Bus master: wbwide
		// Bus master: wb32
		// Bus master: wb32_dio
		// Bus master: wb32_sio
		// bkram
		if ((i_addr[30:0] & 31'h7e000000) == 31'h04000000)
			o_cachable = 1'b1;
		// ddr3_controller
		if ((i_addr[30:0] & 31'h40000000) == 31'h40000000)
			o_cachable = 1'b1;
	end

endmodule
