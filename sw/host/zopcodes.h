////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	zopcodes.h
// {{{
// Project:	10Gb Ethernet switch
//
// Purpose:	A structure defined to keep track of our various opcodes and
//		some of their shortcut synonyms.
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
#ifndef	ZOPCODES_H
#define	ZOPCODES_H

#include <stdint.h>

// MACROS used in the instruction definition list.
#define	ZIP_OPUNUSED	-1
#define	ISUSEROP(A)	((a&(~0x0f))==0x000)
#define	ISSUPROP(A)	((a&(~0x0f))==0x010)
#define	ISLCLROP(A)	((a&(~0x0f))==0x020)
#define	ZIP_BITFIELD(LN,MN)	(((LN&0x0ff)<<8)+(MN&0x0ff)) // A generic bitfield
#define	ZIP_REGFIELD(MN)	(0x00000400 +(MN&0x0ff)) // Normal register field
#define	ZIP_URGFIELD(MN)	(0x0100400 +(MN&0x0ff))	// User register field
#define	ZIP_IMMFIELD(LN,MN)	(0x40000000 + (((LN&0x0ff)<<8)+(MN&0x0ff))) // Sgn extnd
#define	ZIP_SRGFIELD(MN)	(0x0200400 +(MN&0x0ff))
#define	ZIP_SP	0xd0000

typedef	uint32_t	ZIPI;	// A Zip CPU instruction

typedef	struct {
	char	s_opstr[8];	// OPCode name
	ZIPI	s_mask,		// Bits that must match 4 this pattern to match
		s_val;		// What those masked bits must be
	//
	// The following describe not the value, but the bits where there
	// respective vaules will be found within the instruction.  For example,
	// an instruction with no immediate will have an s_i value of -1
	// (ZIP_OPUNUSED), whereas an instruction with an immediate value of -1
	// might have an s_i value of ZIP_BITFIELD(14,0), or 0x0400.  The
	// opcode itself will tell you what the value is--not this structure
	// describing the opcode.
	//
	int	s_result,	// Register where the result will be placed
		s_ra,		// A register, often the result
		s_rb,		// B register, source operand (if used)
		s_i,		// Immediate value, added to B if B is used
		s_cf;		// Condition flags.
} ZOPCODE;

extern	const	char	*zip_regstr[49], *zip_ccstr[8];

extern	const ZOPCODE	*zip_oplist, *zip_opbottomlist;
extern	const int	nzip_oplist, nzip_opbottom;

// Disassemble an opcode
extern	void zipi_to_double_string(const uint32_t, const ZIPI, char *, char *);
extern	const	char	*zop_regstr[];
extern	const	char	*zop_ccstr[];
extern	unsigned int	zop_early_branch(const unsigned int pc, const ZIPI ins);

#endif