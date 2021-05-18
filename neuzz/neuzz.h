//
// Created by lrjia on 2021/5/18.
//

#ifndef NEUZZ_NEUZZ_H
#define NEUZZ_NEUZZ_H

#include <errno.h>
#include <string.h>

/* Error-checking versions of read() and write() that call RPFATAL() as appropriate. */
static inline void ck_write(int fd, char* buf, size_t _len, const char* fn) {
    ssize_t _res = write(fd, buf, _len); \
    if (_res != _len)
        fprintf(stderr, "Short write to %ld %s errno: %s\n", _res, fn,strerror(errno));
}

static inline void ck_read(int fd, char* buf, size_t _len, const char* fn) {
    ssize_t _res = read(fd, buf, _len);
    if (_res != _len)
        fprintf(stderr, "Short read from %ld %s\n",_res, fn);
}

#include "gen_bitmap.h"

#endif //NEUZZ_NEUZZ_H
