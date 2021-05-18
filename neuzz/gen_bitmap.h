//
// Created by lrjia on 2021/5/18.
//

#ifndef NEUZZ_GEN_BITMAP_H
#define NEUZZ_GEN_BITMAP_H

#include "stdio.h"
#include "string.h"
#include <unistd.h>
#include <dirent.h>
#include <malloc.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef __x86_64__
typedef unsigned long long u64;
#else
typedef uint64_t u64;
#endif /* ^__x86_64__ */

void gen_bitmap(char* test_file_argv[],char* file_dir,char* out_dir);

void gen_all_bitmap(char* test_file_argv[],char* seed_dir,char* out_dir_);

#endif //NEUZZ_GEN_BITMAP_H
