/**************************************************************************
**                                                                        *
**  FILE        :  errno.h                                                *
**                                                                        *
**  DESCRIPTION :  Error number definitions.                              *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/


#ifndef _ERRNO_H
#define _ERRNO_H        1

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */

extern __far    int _Errno;
#pragma extern _Errno
extern  __far   int errno;

/*
 * Generic kernel/file-system errors. Merely used by FSS.
 */
#define EPERM           1       /* Operation not permitted */
#define ENOENT          2       /* No such file or directory */
#define EINTR           3       /* Interrupted system call */
#define EIO             4       /* I/O error */
#define EBADF           5       /* Bad file number */
#define EAGAIN          6       /* Resource temporarily unavailable */
#define ENOMEM          7       /* Cannot allocate memory */
#define EACCES          8       /* Permission denied */
#define EFAULT          9       /* Bad address */
#define EEXIST          10      /* File exists */
#define ENOTDIR         11      /* Not a directory*/
#define EISDIR          12      /* Is a directory */
#define EINVAL          13      /* Invalid argument */
#define ENFILE          14      /* File table overflow */
#define EMFILE          15      /* Too many open files */
#define ETXTBSY         16      /* Text file busy */
#define ENOSPC          17      /* No space left on device */
#define ESPIPE          18      /* Illegal seek */
#define EROFS           19      /* Read-only file system */
#define EPIPE           20      /* Broken pipe */
#define ELOOP           21      /* Too many levels of symbolic links */
#define ENAMETOOLONG    22      /* File name too long */

/*
 * Floating point errors
 */
#define EDOM            23      /* Argument too large */
#define ERANGE          24      /* Result too large */

/*
 * errors set by printf/scanf (nonstandard)
 */
#define ERR_FORMAT      25      /* illegal format string for printf/scanf */
#define ERR_NOFLOAT     26      /* floating point not supported */
#define ERR_NOLONG      27      /* long not supported */
#define ERR_NOPOINT     28      /* pointers not supported */

/*
 * encoding errors set by fgetwc, getwc, mbrtowc, etc ...
 */
#define EILSEQ          29      /* Invalid or incomplete multibyte or wide character */

/*
 * Errors set by RTOS
 */
#define ECANCELED       30      /* Operation canceled */
#define ENODEV          31      /* No such device */

/*
 * total number of errors
 */
#define _NERR           32      /* last error + 1 */

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _ERRNO_H */
