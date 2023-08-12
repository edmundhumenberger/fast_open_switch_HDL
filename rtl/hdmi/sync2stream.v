////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	sync2stream.v
// {{{
// Project:	10Gb Ethernet switch
//
// Purpose:	Given a VGA input, synchronize to it, count its size, and then
//		generate an AXI video stream output to encapsulate the stream.
//
//	NOTE: There's no FIFO here.  The outgoing video stream therefore
//	cannot handle *ANY* backpressure.
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
//
`default_nettype	none
// }}}
module	sync2stream #(
		// {{{
		parameter [0:0]	OPT_TUSER_IS_SOF = 0,
		parameter	LGDIM = 16
		// }}}
	) (
		// {{{
		input	wire				i_clk,
		input	wire				i_reset,
		//
		input	wire				i_pix_valid,
		input	wire				i_hsync,
		input	wire				i_vsync,
		input	wire	[24-1:0]		i_pixel,
		//
		output	reg				M_AXIS_TVALID,
		input	wire				M_AXIS_TREADY,
		output	reg	[24-1:0]		M_AXIS_TDATA,	// Color
		output	wire				M_AXIS_TLAST,	// Vsync
		output	wire				M_AXIS_TUSER,	// Hsync
		//
		output	reg	[LGDIM-1:0]		o_width,
		output	reg	[LGDIM-1:0]		o_hfront,
		output	reg	[LGDIM-1:0]		o_hsync,
		output	reg	[LGDIM-1:0]		o_raw_width,
		output	reg				o_hsync_pol,
		//
		output	reg	[LGDIM-1:0]		o_height,
		output	reg	[LGDIM-1:0]		o_vfront,
		output	reg	[LGDIM-1:0]		o_vsync,
		output	reg	[LGDIM-1:0]		o_raw_height,
		output	reg				o_vsync_pol,
		//
		output	wire				o_locked
		// }}}
	);

	// Register/wire declarations
	// {{{
	wire		new_data_row, hsync, vsync;
	reg	[LGDIM:0]	hcount_pix, hcount_shelf, hcount_sync, hcount_tot;
	reg		hin_shelf, last_pv, hlocked;

	reg	linestart, has_pixels, has_vsync, newframe, last_hs,
		this_line_had_vsync, this_line_had_pixels, last_line_had_pixels;

	reg	[LGDIM:0]	vcount_lines, vcount_shelf, vcount_sync, vcount_tot;
	reg		vin_shelf, vlost_lock, vlocked, hpol, vpol;
	reg		empty_row;

	reg		M_AXIS_HLAST, M_AXIS_VLAST;
	// }}}

	// Adjust for sync inversion (if necessary)
	// {{{
	assign	hsync = hpol ^ i_hsync;
	assign	vsync = vpol ^ i_vsync;
	// }}}

	initial	last_pv = 0;
	always @(posedge i_clk)
		last_pv <= i_pix_valid;

	assign	new_data_row = (!last_pv)&&(i_pix_valid);

	////////////////////////////////////////////////////////////////////////
	//
	// Horizontal mode line
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//

	// hcount* _pix, _shelf, _sync, _tot
	// {{{
	initial	hcount_pix   = 0;
	initial	hcount_shelf = 0;
	initial	hcount_sync  = 0;
	initial	hcount_tot   = 0;
	initial	hin_shelf    = 1'b1;
	initial	empty_row    = 1;
	always @(posedge i_clk)
	if (i_reset)
		// Assume polarities are inverted until we have reason to
		// believe otherwise
		{ hpol, vpol } <= 2'b11;
	else if (!i_pix_valid && last_pv)
		{ hpol, vpol } <= { i_hsync, i_vsync };

	always @(posedge i_clk)
	if (new_data_row)
	begin
		hcount_pix   <= 1;
		hcount_shelf <= 0;
		hcount_sync  <= 0;
		hcount_tot   <= 1;
		hin_shelf    <= 1;
		empty_row    <= 0;
	end else begin
		if (!hcount_tot[LGDIM])
			hcount_tot <= hcount_tot + 1'b1;
		if (!hcount_pix[LGDIM] && i_pix_valid)
			hcount_pix <= hcount_pix + 1'b1;
		if (!hcount_sync[LGDIM] && !i_pix_valid && hsync)
			hcount_sync <= hcount_sync + 1'b1;
		if (!hcount_sync[LGDIM]&& hsync && !last_hs && hcount_sync != 0)
			// If we see the same sync twice, with no valid data
			// in between, then the row is empty.
			empty_row <= 1;
		if(!hcount_shelf[LGDIM] && !i_pix_valid
					&& (last_pv || !hsync) && hin_shelf)
			hcount_shelf <= hcount_shelf + 1'b1;
		if (hsync && !i_pix_valid)
			hin_shelf <= 1'b0;
	end
	// }}}

	// o_width, o_raw_width, o_hfront, o_hsync
	// {{{
	initial	o_width     = 0;
	initial	o_raw_width = 0;
	initial	o_hfront    = 0;
	initial	o_hsync     = 0;
	always @(posedge i_clk)
	if (new_data_row && !empty_row)
	begin
		o_width     <= hcount_pix[LGDIM-1:0]; // -16'd10;
		o_raw_width <= hcount_tot[LGDIM-1:0]; // +16'd1;
		o_hfront    <= hcount_pix[LGDIM-1:0] + hcount_shelf[LGDIM-1:0]; // + 16'd11;
		o_hsync     <= hcount_pix[LGDIM-1:0] + hcount_shelf[LGDIM-1:0] + hcount_sync[LGDIM-1:0];

		o_hsync_pol <= hpol;
	end
	// }}}

	// hlocked
	// {{{
	always @(posedge i_clk)
	if (i_reset)
		hlocked <= 0;
	else if (new_data_row && !empty_row)
	begin
		hlocked <= 1;
		if ({ 1'b0, o_width } != hcount_pix)
			hlocked <= 0;
		if ({ 1'b0, o_raw_width } != hcount_tot)
			hlocked <= 0;
	end
	// }}}

	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Vertical mode line
	// {{{
	////////////////////////////////////////////////////////////////////////
	//
	//

	// last_hs
	// {{{
	initial	last_hs = 1'b0;
	always @(posedge i_clk)
		last_hs <= hsync;
	// }}}

	// linestart, has_pixels, has_vsync, newframe
	// {{{
	initial	linestart  = 1'b0;
	initial	has_pixels = 1'b0;
	initial	has_vsync  = 1'b0;
	initial	newframe   = 1'b0;
	always @(posedge i_clk)
	if (!last_hs && hsync && !last_pv)
	begin
		linestart  <= 1'b1;
		has_pixels <= 1'b0;
		has_vsync  <= 1'b0;
		this_line_had_vsync  <= has_vsync;
		this_line_had_pixels <= has_pixels;
		last_line_had_pixels <= last_line_had_pixels;
		newframe <= (has_pixels)&&(!this_line_had_pixels);
	end else begin
		linestart  <= 1'b0;
		newframe   <= 1'b0;
		if (i_pix_valid)
			has_pixels <= 1'b1;
		else if (vsync && !last_pv)
			has_vsync  <= 1'b1;
	end
	// }}}

	// vcount* _lines, _shelf, _sync, _tot, _lock
	// {{{
	initial	vcount_lines = 1;
	initial	vcount_shelf = 0;
	initial	vcount_sync  = 0;
	initial	vcount_tot   = 1;
	always @(posedge i_clk)
	if (linestart)
	begin
		if (newframe)
		begin
			// We'll get here *after* the first line of a new frame
			// {{{
			vcount_lines <= 1;
			vcount_shelf <= 0;
			vcount_sync  <= 0;
			vcount_tot   <= 1;
			vin_shelf    <= 1'b1;
			// }}}
		end else begin
			// Count up
			// {{{
			if (!vcount_tot[LGDIM])
				vcount_tot <= vcount_tot + 1'b1;
			if ((!vcount_lines[LGDIM])&&(this_line_had_pixels))
				vcount_lines <= vcount_lines + 1'b1;
			if ((!vcount_sync[LGDIM])&&(this_line_had_vsync))
				vcount_sync <= vcount_sync + 1'b1;
			if ((!vcount_shelf[LGDIM])&&(!this_line_had_pixels)
					&&(!this_line_had_vsync)&&(vin_shelf))
				vcount_shelf <= vcount_shelf + 1'b1;
			if (this_line_had_vsync)
				vin_shelf <= 1'b0;
			// }}}
		end
	end

	initial	vlost_lock   = 1;
	always @(posedge i_clk)
	if (i_reset)
		vlost_lock <= 1'b1;
	else if (!hlocked)
		vlost_lock <= 1'b1;
	else if (linestart && newframe)
		vlost_lock <= !hlocked;
	// }}}

	// o_height, o_raw_height, o_vfront, o_vsync
	// {{{
	initial	o_height    = 0;
	initial	o_raw_height= 0;
	initial	o_vfront    = 0;
	initial	o_vsync     = 0;
	always @(posedge i_clk)
	if (newframe)
	begin
		o_height     <= vcount_lines[LGDIM-1:0];
		o_raw_height <= vcount_tot[LGDIM-1:0];
		o_vfront     <= vcount_shelf[LGDIM-1:0] + vcount_lines[LGDIM-1:0];
		o_vsync      <= vcount_sync[LGDIM-1:0] + vcount_shelf[LGDIM-1:0]
					+ vcount_lines[LGDIM-1:0] - 1;
		o_vsync_pol <= vpol;
	end
	// }}}

	// vlocked, o_locked
	// {{{
	initial	vlocked = 0;
	always @(posedge i_clk)
	begin
		if (newframe)
		begin
			vlocked <= !vlost_lock && !vcount_tot[LGDIM];
			if ({ 1'b0, o_height } != vcount_lines)
				vlocked <= 0;
			if ({ 1'b0, o_raw_height } != vcount_tot)
				vlocked <= 0;
		end

		if (!hlocked)
			vlocked <= 0;
		if (i_reset)
			vlocked <= 0;
	end

	assign	o_locked = vlocked;
	// }}}

	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Pixel stream outputs
	// {{{

	// M_AXIS_TVALID
	// {{{
	always @(posedge i_clk)
		M_AXIS_TVALID <= i_pix_valid;
	// }}}

	// M_AXIS_TDATA
	// {{{
	always @(posedge i_clk)
		M_AXIS_TDATA <= i_pixel;
	// }}}

	// M_AXIS_HLAST -- last data in line signal
	// {{{
	always @(posedge i_clk)
		M_AXIS_HLAST <= !i_reset && i_pix_valid && (hcount_pix == o_width-1);
	// }}}

	// M_AXIS_VLAST -- last data in frame signal
	// {{{
	always @(posedge i_clk)
		M_AXIS_VLAST <= !i_reset && i_pix_valid
			&& (hcount_pix == o_width-1)
			&& (vcount_lines == o_height-1);
	// }}}

	// Adjust between VLAST == TLAST and TUSER == start of frame encodings
	// (I've chosen the former, Xilinx chose the latter)
	generate if (OPT_TUSER_IS_SOF)
	begin : XILINXS_ENCODING
		reg	sof;

		assign	M_AXIS_TLAST = M_AXIS_HLAST;

		always @(posedge i_clk)
		if (M_AXIS_TVALID)
			sof <= M_AXIS_VLAST;

		assign	M_AXIS_TUSER = sof;

	end else begin : VLAST_IS_TLAST

		assign	M_AXIS_TLAST = M_AXIS_VLAST;

		assign	M_AXIS_TUSER = M_AXIS_HLAST;

	end endgenerate
	// }}}

	// Keep Verilator happy
	// {{{
	// Verilator lint_off UNUSED
	wire	unused;
	assign	unused = &{ 1'b0, M_AXIS_TREADY };
	// Verilator lint_on  UNUSED
	// }}}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Formal properties
// {{{
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
`ifdef	FORMAL
	reg	f_past_valid;
	(* anyconst *)	reg	fh_syncpol, fv_syncpol;
	(* anyconst *)	reg	[LGDIM:0]	fh_width, fv_height,
					fh_front, fv_front,
					fh_sync,  fv_sync,
					fh_raw,   fv_raw,
					fc_hpos,  fc_vpos;
	(* anyconst *)	reg	[23:0]	fc_pixel;
	reg	[LGDIM:0]	f_hpos, f_vpos;
	reg			f_hsync, f_vsync,
				f_valid, fv_valid;

	initial	f_past_valid = 0;
	always @(posedge i_clk)
		f_past_valid <= 1;

	always @(*)
	if (!f_past_valid)
		assume(i_reset);

	////////////////////////////////////////////////////////////////////////
	//
	// Input assumptions
	// {{{
	always @(*)
	begin
		assume(fh_width >= 4);
		assume(fh_front > fh_width);
		assume(fh_sync  > fh_front);
		assume(fh_raw   > fh_sync + 10);

		assume(fv_height >= 2);
		assume(fv_front > fv_height);
		assume(fv_sync  > fv_front);
		assume(fv_raw   > fv_sync);
	end

	always @(*)
	if (i_reset)
	begin
		assume(f_hpos < fh_raw);
		assume(f_vpos < fv_raw);
	end

	always @(posedge i_clk)
	begin
		f_hpos <= f_hpos + 1;
		if (f_hpos +1 >= fh_raw)
			f_hpos <= 0;
		if (f_hpos +1 == fh_front)
		begin
			f_vpos <= f_vpos + 1;
			if (f_vpos + 1 >= fv_raw)
				f_vpos <= 0;
		end
	end

	always @(posedge i_clk)
	if (i_reset)
		f_valid <= 0;
	else if (i_pix_valid && !last_pv && !has_vsync)
		f_valid <= 1;

	// When are the vertical counters valid?
	always @(posedge i_clk)
	if (i_reset)
		fv_valid <= 0;
	else if (f_valid && i_px_valid && f_vpos == 0
				&& !this_line_had_pixels && !has_vsync)
		fv_valid <= 1;

	always @(*)
	begin
		assume(i_pix_valid == ((f_hpos < fh_width)
						&& (f_vpos < fv_height)));
		f_hsync = (f_hpos >= fh_front && f_hpos < fh_sync);
		f_vsync = (f_vpos >= fv_front && f_vpos < fv_sync);

		if (!i_pix_valid)
		begin
			assume(i_hsync == (f_hsync ^ fh_syncpol));
			assume(i_vsync == (f_hsync ^ fh_syncpol));
		end
	end

	always @(*)
	if (fc_hpos == f_hpos && fc_vpos == f_vpos && i_pix_valid)
		assume(i_pixel == fc_pixel);
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Intermediate counting assertions
	// {{{

	always @(*)
	if (!i_reset)
	begin
		assert(hcount_pix   <= (1<<LGDIM));
		assert(hcount_tot   <= (1<<LGDIM));
		assert(hcount_sync  <= (1<<LGDIM));
		assert(hcount_shelf <= (1<<LGDIM));
	end

	// empty_row
	// {{{
	always @(*)
	if (!i_reset && f_valid && f_hpos > 0 && f_vpos < fv_height)
	begin
		assert(!empty_row);
	end else if (!i_reset && f_valid && f_hpos > 0 && f_hpos < fh_raw
							&& f_vpos == fv_height)
		assert(!empty_row);

	always @(*)
	if (!i_reset && f_valid && hcount_tot > fh_raw)
	begin
		assert(f_vpos >= fv_height);
		if (f_hpos > fh_front)
			assert(empty_row);
		if (f_vpo > fv_height)
			assert(empty_row);
	end
	// }}}

	// hcount* assertions
	// {{{
	always @(*)
	if (!i_reset && f_valid && !empty_row)
	begin
		assert((hcount_tot == (1<<LGDIM) && f_hpos >= (1<<LGDIM))
				|| (hcount_tot == { 1'b0, fh_pos[LGDIM-1:0]}));

		if (f_hpos < fh_width)
		begin
			assert((hcount_pix == (1<<LGDIM))&&f_hpos >= (1<<LGDIM))
				|| (hcount_pix == { 1'b0, fh_pos[LGDIM-1:0]}));
		end else begin
			assert((hcount_pix == (1<<LGDIM))&&f_hpos >= (1<<LGDIM))
				|| (hcount_pix == fh_width));
		end

		if (f_hpos > fh_width)
		begin
			assert(hpol == fh_syncpol);
			assert(vpol == fv_syncpol);
		end

		if (f_hpos == 0)
		begin
		end else if (i_pix_valid && f_hpos < fh_width)
		begin
			assert(hcount_tot == hcount_pix);
			assert(hin_shelf);
			assert(hin_sync  == 0);
			assert(hin_shelf == 0);
			assert(empty_row == 0);
		end

		if (f_hpos >= fh_width && f_hpos <= fh_front)
		begin
			assert(hcount_sync == 0);
			assert(hcount_shelf == (f_hpos-fh_width));
			assert(hin_shelf);
		end else if (f_hpos > fh_front && f_hpos < fh_sync)
		begin
			assert(hcount_shelf == (f_hfront - fh_width));
			assert(hcount_sync  == (f_hpos   - fh_front);
			assert(!hin_shelf);
		end else if (f_hpos > fh_sync)
		begin
			assert(hcount_shelf == (fh_front - fh_width));
			assert(hcount_sync  == (fh_sync  - fh_front));
			assert(!hin_shelf);
		end
	end
	// }}}

	always @(*)
	if (!i_reset && f_valid && f_vpos < fv_height && f_hpos < fh_sync)
	begin
		assert(f_hpos == 0 || has_pixels);
	end

	always @(*)
	if (!i_reset && fv_valid)
		assert(f_valid);

	always @(*)
	if (!i_reset && f_valid)
	begin
		if (fv_valid)
		begin
			assert(this_line_had_pixels == (f_vpos != 0 && f_vpos <= fv_height);
			assert(last_line_had_pixels == (f_vpos > 1 && f_vpos <= fv_height+1);
			assert(this_line_had_vsync  == (f_vpos > fv_front && f_vpos <= fv_sync+1);
		end

		if (f_hpos < fh_front || f_hpos > fh_front+3)
			assert(has_vsync == (f_vpos >= fv_front && f_vpos < fv_sync));
	end

	always @(posedge i_clk)
	if (!i_reset && f_valid)
	begin
		assert(linestart == (f_hpos == fh_front + 1));
	end

	always @(posedge i_clk)
	if (!i_reset && fv_valid && !linestart)
	begin
		// {{{
		assert(vcount_tot == fv_vpos);
		if (fv_vpos < fv_height)
			assert(vcount_lines == fv_vpos);
		else
			assert(vcount_lines == fv_height);

		assert(vin_shelf == (fv_vpos < fv_front));

		if (fv_vpos < fv_height)
		begin
			assert(vcount_shelf == 0);
		end else if (fv_vpos < fv_front)
		begin
			assert(vcount_shelf == (fv_vpos - fv_height));
		end else
			assert(vcount_shelf == (fv_front - fv_height));

		if (fv_vpos < fv_front)
		begin
			assert(vcount_sync == 0);
		end else begin
			assert(vcount_sync == (fv_vpos - fv_front));
		end

		if (!fv_valid) assert(o_height == 0);
		if (o_height == 0)
		begin
			// assert(o_height == 0);
			assert(o_vfront == 0);
			assert(o_vsync  == 0);
			assert(o_raw_front  == 0);
			assert(o_vsync_pol  == 0);
			assert(vlost_lock);
		end else begin
			assert(o_height    == fv_height);
			assert(o_vfront    == fv_front);
			assert(o_vsync     == fv_sync);
			assert(o_raw_front == fv_raw);
			assert(o_vsync_pol == fv_syncpol);
		end
	end

	always @(posedge i_clk)
	if (!i_reset)
	begin
		if (!$past(hlocked))
			assert(vlost_lock);
		if (!fv_valid)
			assert(vlost_lock);
		if (!$past(i_reset))
			assert(!$rose(vlost_lock));
	end
	
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// Output assertions
	// {{{
	always @(posedge i_clk)
	if (i_reset || $past(i_reset))
	begin
	end else if (o_width == 0)
	begin
		assert(o_height == 0);
		assert(o_sync   == 0);
		assert(o_hfront == 0);
		assert(o_hsync  == 0);
		assert(o_raw_width == 0);
		assert(!hlocked);
	end else begin
		assert(o_width     == fh_width);
		assert(o_hsync     == fh_sync);
		assert(o_hfront   == fh_front);
		assert(o_raw_width == fh_raw);
		assert(o_hsync_pol == fh_syncpol);

		assert(!$fell(hlocked));
	end
	// }}}
	////////////////////////////////////////////////////////////////////////
	//
	// "Careless" assumptions
	// {{{

	always @(*)
	begin
		assume(!fh_width[LGDIM]);
		assume(!fh_front[LGDIM]);
		assume(!fh_sync[LGDIM]);
		assume(!fh_raw[LGDIM]);

		assume(!fv_height[LGDIM]);
		assume(!fv_front[LGDIM]);
		assume(!fv_sync[LGDIM]);
		assume(!fv_raw[LGDIM]);
	end
	// }}}
`endif
// }}}
endmodule
