/**************************************************************************
**                                                                        *
**  FILE        :  dbg.h                                                  *
**                                                                        *
**  DESCRIPTION :  debugger call interface for filesystem access,         *
**                 simulation time measurement, application exit.         *
**                                                                        *
**  Copyright 1996-2010 Altium BV                                         *
**                                                                        *
**************************************************************************/

#ifndef _DBG_H
#define _DBG_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <time.h>       /* clock_t */
#include <io.h>

typedef enum
{
        _DBG_EXIT       = 1,
        _DBG_CLOCK      = 2,
        _DBG_OPEN       = 3,
        _DBG_READ       = 4,
        _DBG_WRITE      = 5,
        _DBG_LSEEK      = 6,
        _DBG_CLOSE      = 7,
        _DBG_RENAME     = 8,
        _DBG_UNLINK     = 9,
        _DBG_ACCESS     = 10,
        _DBG_GETCWD     = 11,
        _DBG_CHDIR      = 12,
        _DBG_STAT       = 13,
        _DBG_ARGCV      = 14
} _dbg_nr_t;


typedef struct
{
        int                             _errno;
        _dbg_nr_t                       nr;
        union
        {
                struct
                {
                        int             status;
                } exit;
                struct
                {
                        const char *    pathname;
                        uint_least16_t  flags;
                        /* no mode argument */
                } open;
                struct
                {
                        uint_least8_t   fd;
                        void *          buffer;
                        size_t          nbytes;
                } read;
                struct
                {
                        uint_least8_t   fd;
                        const void *    buffer;
                        size_t          nbytes;
                } write;
                struct
                {
                        uint_least8_t   fd;
                        uint_least8_t   whence;
                        long            offset;
                } lseek;
                struct
                {
                        uint_least8_t   fd;
                } close;
                struct
                {
                        const char *    oldpath;
                        const char *    newpath;
                } rename;
                struct
                {
                        const char *    pathname;
                } unlink;
                struct
                {
                        const char *    pathname;
                        int             mode;
                } access;
                struct
                {
                        char *          buf;
                        size_t          size;
                } getcwd;
                struct
                {
                        const char *    pathname;
                } chdir;
                struct
                {
                        const char *    pathname;
                        struct stat *   buf;
                } stat;
                struct
                {
                        const char *    buf;
                        size_t          size;
                } argcv;                
                clock_t                 clock_result;
                int_least8_t            open_result;
                int                     read_result;
                int                     write_result;
                long                    lseek_result;
                int_least8_t            close_result;
                int                     rename_result;
                int                     unlink_result;
                int                     access_result;
                char *                  getcwd_result;
                int                     chdir_result;
                int                     stat_result;
                int                     argcv_result;
        } u;
} _dbg_request_t;


extern  void                            _dbg_trap_tc(void);
extern  int                             _argcv(const char *, size_t size);
extern  __far   _dbg_request_t  _dbg_request;

#ifdef  __cplusplus
}
#endif

#endif /* _DBG_H */
