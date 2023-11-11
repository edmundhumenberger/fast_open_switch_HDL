////////////////////////////////////////////////////////////////////////////////
//
// Filename: 	routescope.cpp
// {{{
// Project:	10Gb Ethernet switch
//
// Purpose:	This file decodes the debug bits produced by the network
//		router and stored in the compressed Wishbone scope.
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
#include <unistd.h>
#include <strings.h>
#include <ctype.h>
#include <string.h>
#include <signal.h>
#include <assert.h>

#include "regdefs.h"
#include <design.h>
#include "devbus.h"
#include "scopecls.h"

#ifndef	R_ROUTESCOPE
int main(int argc, char **argv) {
	printf("This design was not built with a FAN scope within it.\n");
	exit(EXIT_FAILURE);
}
#else
#define	WBSCOPE		R_ROUTESCOPE
#define	WBSCOPEDATA	R_ROUTESCOPED

DEVBUS	*m_fpga;
void	closeup(int v) {
	m_fpga->kill();
	exit(0);
}

class	ROUTESCOPE : public SCOPE {
	const	unsigned DBGSEL = 1;
public:
	ROUTESCOPE(DEVBUS *fpga, unsigned addr, bool vecread)
		: SCOPE(fpga, addr, true, vecread) {};
	~ROUTESCOPE(void) {}
	virtual	void	decode(DEVBUS::BUSW val) const {
	}

	virtual	void	define_traces(void) {
		if (DBGSEL == 0) {
			register_trace("watchdog", 1,30);
			register_trace("CPU_VALID",1,29);
			register_trace("CPU_READY",1,28);
			register_trace("RX_VALID", 4,24);
			register_trace("RX_READY", 4,20);
			register_trace("RX_LAST",  4,16);
			register_trace("RX_ABORT", 4,12);
			register_trace("TX_VALID", 4, 8);
			register_trace("TX_READY", 4, 4);
			register_trace("mid_tx",   4, 0);
		} else if (DBGSEL == 1) {

			register_trace("M_VALID",1,30);
			register_trace("M_READY",1,29);
			register_trace("M_LAST", 1,28);
			register_trace("M_ABORT",1,27);

			register_trace("s_midpkt",1,26);
			register_trace("midpkt", 5,20);

			register_trace("V[4]",   1,19);
			register_trace("R[4]",   1,18);
			register_trace("L[4]",   1,17);
			register_trace("A[4]",   1,16);

			register_trace("V[3]",   1,15);
			register_trace("R[3]",   1,14);
			register_trace("L[3]",   1,13);
			register_trace("A[3]",   1,12);

			register_trace("V[2]",   1,11);
			register_trace("R[2]",   1,10);
			register_trace("L[2]",   1, 9);
			register_trace("A[2]",   1, 8);

			register_trace("V[1]",   1, 7);
			register_trace("R[1]",   1, 6);
			register_trace("L[1]",   1, 5);
			register_trace("A[1]",   1, 4);

			register_trace("V[0]",   1, 3);
			register_trace("R[0]",   1, 2);
			register_trace("L[0]",   1, 1);
			register_trace("A[0]",   1, 0);
		}
	}
};

int main(int argc, char **argv) {
	m_fpga = connect_devbus(NULL);

	signal(SIGSTOP, closeup);
	signal(SIGHUP, closeup);

	ROUTESCOPE *scope = new ROUTESCOPE(m_fpga, WBSCOPE, false);
	if (!scope->ready()) {
		printf("Scope is not yet ready:\n");
		scope->decode_control();
	} else {
		scope->print();
		scope->writevcd("routescope.vcd");
	}
	delete	m_fpga;
}
#endif
