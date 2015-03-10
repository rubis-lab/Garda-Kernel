/**************************************************************************
**                                                                        *
**  FILE        :  unistd.h                                               *
**                                                                        *
**  DESCRIPTION :  Declarations of the standard UNIX I/O functions.       *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _UNISTD_H
#define _UNISTD_H

#ifdef  __cplusplus
extern "C" {
#endif  /* defined(__cplusplus) */


#ifndef _OFF_T_DEF
typedef long            off_t;
#define _OFF_T_DEF
#endif

#ifndef _SIZE_T_DEF
typedef unsigned int    size_t;
#define _SIZE_T_DEF     1
#endif

#ifndef _SSIZE_T_DEF
typedef signed int      ssize_t;
#define _SSIZE_T_DEF
#endif

/*
 * mode definitions for acess():
 */
#define R_OK    4               /* test for read permission */
#define W_OK    2               /* test for write permission */
#define X_OK    1               /* test for execute permission */
#define F_OK    0               /* test for existence */

/*
 * struct definition for stat():
 */

struct  stat
{
        unsigned short st_dev;
        unsigned short st_ino;
        unsigned short st_mode;
        unsigned short st_nlink;
        unsigned short st_uid;
        unsigned short st_gid;
        unsigned short st_rdev;
        unsigned long  st_size;
        unsigned long  st_atime;
        unsigned long  st_mtime;
        unsigned long  st_ctime;
};

        
/*
 * st_mode flags:
 */
#define _S_IFMT         0170000         /* these bits determine file type       */
#define _S_IFDIR        0040000         /* directory                            */
#define _S_IFCHR        0020000         /* character device                     */
#define _S_IFBLK        0060000         /* block device                         */
#define _S_IFREG        0100000         /* regular file                         */
#define _S_IFIFO        0010000         /* FIFO                                 */
#define _S_IFLNK        0120000         /* symbolic link                        */
#define _S_IFSOCK       0140000         /* socket                               */
#define _S_ISUID        04000           /* set user ID on execution             */
#define _S_ISGID        02000           /* set group ID on execution            */
#define _S_ISVTX        01000           /* save swapped text after use (sticky) */
#define _S_IREAD        0400            /* read by owner                        */
#define _S_IWRITE       0200            /* write by owner                       */
#define _S_IEXEC        0100            /* execute by owner                     */

#define S_IFMT          _S_IFMT
#define S_IFDIR         _S_IFDIR
#define S_IFCHR         _S_IFCHR
#define S_IFBLK         _S_IFBLK
#define S_IFREG         _S_IFREG
#define S_IFIFO         _S_IFIFO
#define S_IFLNK         _S_IFLNK
#define S_IFSOCK        _S_IFSOCK

/*
 * test macros for file types:
 */
#define _S_ISTYPE(mode, mask)   (((mode) & _S_IFMT) == (mask))

#define S_ISDIR(mode)   _S_ISTYPE((mode), _S_IFDIR)
#define S_ISCHR(mode)   _S_ISTYPE((mode), _S_IFCHR)
#define S_ISBLK(mode)   _S_ISTYPE((mode), _S_IFBLK)
#define S_ISREG(mode)   _S_ISTYPE((mode), _S_IFREG)
#define S_ISFIFO(mode)  _S_ISTYPE((mode), _S_IFIFO)
#define S_ISLNK(mode)   _S_ISTYPE((mode), _S_IFLNK)
#define S_ISSOCK(mode)  _S_ISTYPE((mode), _S_IFSOCK)


extern  void    _exit(int);
extern  int     close (int);
extern  int     unlink (const char *);
extern  ssize_t read (int, void *, size_t);
extern  ssize_t write (int, const void *, size_t);
extern  int     stat (const char *, struct stat *);
extern  int     lstat (const char *, struct stat *);
extern  int     fstat (int, struct stat *);
extern  off_t   lseek (int, off_t, int);
extern  char    *getcwd (char *, size_t);
extern  int     chdir (const char *);
extern  int     access (const char *, int);
extern  int     rename (const char *, const char *);

#ifdef  __cplusplus
}
#endif  /* defined(__cplusplus) */

#endif  /* _UNISTD_H */
