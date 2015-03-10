/**************************************************************************
**                                                                        *
**  FILE        :  fcntl.h                                                *
**                                                                        *
**  DESCRIPTION :  Definition of open() flags and prototype               *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _FCNTL_H
#define _FCNTL_H

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */



extern  int     open(const char *, int, ... /* mode_t */);

#define O_ACCMODE       0x0003
#define O_RDONLY        0x0000  /* read only */
#define O_WRONLY        0x0001  /* write only */
#define O_RDWR          0x0002  /* read and write */
#define O_NDELAY        0x0004  /* non blocking I/O */
#define O_APPEND        0x0008  /* append mode */
#define O_SYNC          0x0010  /* synchronized file update */
#define O_NONBLOCK      0x0080  /* non blocking I/O */
#define O_CREAT         0x0100  /* create file */
#define O_TRUNC         0x0200  /* truncate file */
#define O_EXCL          0x0400  /* exclusive open */
#define O_NOCTTY        0x0800  /* don't allocate controlling tty */
#define O_BINARY        0x8000  /* binary file */

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif /* _FCNTL_H */
