////////////////////////////////////////////////////////////////////////////////
//
// Filename:	clkcheck.c
// {{{
// Project:	10Gb Ethernet switch
//
// Purpose:	The original Helllo World program.  If everything works, this
//		will print Hello World to the UART, and then halt the CPU--if
//	run with no O/S.
//
//
////////////////////////////////////////////////////////////////////////////////
//
// Gisselquist Technology asserts no ownership rights over this particular
// hello world program.
//
////////////////////////////////////////////////////////////////////////////////
//
// }}}
#include <stdio.h>
#include "board.h"
#include <zipsys.h>

#ifdef	_BOARD_HAS_REFCLKCOUNTER
#define	VALID_CLKCHECK
#elif	defined(_BOARD_HAS_SICLKCOUNTER)
#define	VALID_CLKCHECK
#elif	defined(_BOARD_HAS_NETCLK)
#define	VALID_CLKCHECK
#elif	defined(_BOARD_HAS_VIDPIPE)
#define	VALID_CLKCHECK
#endif

void	clkreport(const char *nm, const unsigned counts) {
	if (counts > 1000000)
		printf("%-20s: %9.6f MHz\n", nm, (double)counts / 1e6);
	else if (counts > 1000)
		printf("%-20s:    %6.3f kHz\n", nm, (double)counts / 1e3);
	else // if (counts > 0)
		printf("%-20s:       %3d  Hz\n", nm, counts);
}

int main(int argc, char **argv) {
#ifndef	VALID_CLKCHECK
	printf("clkcheck requires a valid clock to check\n");
#else
	while(1) {
		_zip->z_tma = 100000000;	// One second
		while(_zip->z_tma != 0)
			;
printf("---\n");
#ifdef	_BOARD_HAS_NETCLK
		clkreport("NET.RX[0]", _netclk[0]);
		clkreport("NET.RX[1]", _netclk[1]);
		clkreport("NET.RX[2]", _netclk[2]);
		clkreport("NET.RX[3]", _netclk[3]);
		clkreport("NET.TX",    _netclk[4]);
#endif
#ifdef	_BOARD_HAS_REFCLKCOUNTER
		clkreport("Si5324 RefClk", (*_sirefclkcounter));
#endif
#ifdef	_BOARD_HAS_SICLKCOUNTER
		clkreport("Si5324", (*_siclk));
#endif
#ifdef	_BOARD_HAS_VIDPIPE
		clkreport("HDMI.RX",_hdmi->v_hdmifreq);
		clkreport("Si5324", _hdmi->v_sifreq);
		clkreport("PixClk", _hdmi->v_pxfreq);
#endif
	}
#endif
}
