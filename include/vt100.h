/**************************************************************************
**                                                                        *
**  FILE        :  vt100.h                                                *
**                                                                        *
**  DESCRIPTION :  Definitions of VT100 escape sequences.                 *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _VT100_H
#define _VT100_H

/* cursor motion */
#define VT100_CURSOR_DN   "\033D"  
#define VT100_CURSOR_DN_L "\033E"  
#define VT100_CURSOR_UP   "\033M"  
#define VT100_CURSOR_HOME "\033[H"
#define VT100_CURSOR_N_UP "\033[%dA"    /* printf argument: lines */
#define VT100_CURSOR_N_RT "\033[%dB"    /* printf argument: cols  */
#define VT100_CURSOR_N_LT "\033[%dC"    /* printf argument: cols  */
#define VT100_CURSOR_N_DN "\033[%dD"    /* printf argument: lines */
#define VT100_CURSOR_SET  "\033[%d;%dH" /* printf arguments: row, col */

/* erasing the screen */
#define VT100_CLR_FM_CRSR "\033[J"
#define VT100_CLR_TO_CRSR "\033[1J"
#define VT100_CLR_SCREEN  "\033[2J"

/* erasing current line */
#define VT100_CLL_FM_CRSR "\033[K"
#define VT100_CLL_TO_CRSR "\033[1K"
#define VT100_CLR_LINE    "\033[2K"

/* inserting and deleting */
#define VT100_INS_CHARS   "\033[%d"     /* printf argument: cols */
#define VT100_DEL_CHARS   "\033[%dP"    /* printf argument: cols */
#define VT100_INS_LINES   "\033[%dL"    /* printf argument: cols */
#define VT100_DEL_LINES   "\033[%dM"    /* printf argument: cols */

/* character attributes */
#define VT100_NORMAL      "\033[m"
#define VT100_ALL_OFF     "\033[0m"
#define VT100_BOLD_ON     "\033[1m"
#define VT100_BOLD_OFF    "\033[22m"
#define VT100_UNDERL_ON   "\033[4m"
#define VT100_UNDERL_OFF  "\033[24m"
#define VT100_BLINK_ON    "\033[5m"
#define VT100_BLINK_OFF   "\033[25m"
#define VT100_REVERSE_ON  "\033[7m"
#define VT100_REVERSE_OFF "\033[27m"
#define VT100_INVIS_ON    "\033[8m"
#define VT100_INVIS_OFF   "\033[28m"

/* screen attributes */
#define VT100_ECHO_ON     "\033[12l"
#define VT100_ECHO_OFF    "\033[12h"
#define VT100_WRAP_ON     "\033[?7l"
#define VT100_WRAP_OFF    "\033[?7h"
#define VT100_CURSOR_ON   "\033[?25h"
#define VT100_CURSOR_OFF  "\033[?25l"
#define VT100_ENQ_SIZE    "\033[?92l"   /* response: "\033[?%d,%dc" rows, cols */

#endif /* _VT100_H */
