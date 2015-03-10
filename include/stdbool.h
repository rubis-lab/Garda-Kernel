/**************************************************************************
**                                                                        *
**  FILE        :  stdbool.h                                              *
**                                                                        *
**  DESCRIPTION :  Boolean type and values                                *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _STDBOOL_H
#define _STDBOOL_H      1

/*
 * 7.16 Boolean type and values
 */
#pragma nomisrac 19.4
#define bool                            _Bool
#pragma nomisrac restore
#define true                            1
#define false                           0
#define __bool_true_false_are_defined   1

#endif  /* _STDBOOL_H */
