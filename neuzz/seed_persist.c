//
// Created by lrjia on 2021/5/18.
//

#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "seed_persist.h"
#include "neuzz.h"
#include "gen_bitmap.h"


/* User-facing macro to sprintf() to a dynamically allocated buffer. */
#define alloc_printf(_str...) ({ \
    char* _tmp; \
    int _len = snprintf(NULL, 0, _str); \
    if (_len < 0) perror("Whoa, snprintf() fails?!"); \
    _tmp = malloc(_len + 1); \
    snprintf((char*)_tmp, _len + 1, _str); \
    _tmp; \
})


void save_seed(char* content,size_t len_,char *locate,char* id_str){
    char *mut_fn = alloc_printf("%s/%s_%d_%06d", locate, id_str, round_cnt, mut_cnt);
    int mut_fd = open(mut_fn, O_WRONLY | O_CREAT | O_EXCL, 0600);
    ck_write(mut_fd, content, len_, mut_fn);
    close(mut_fd);
    mut_cnt = mut_cnt + 1;

    gen_bitmap(NULL,mut_fn,NULL);
    free(mut_fn);
}


void save_crash(char *content, size_t len_) {
    save_seed(content,len_,"./crashes","crash");
}

void add_to_queue(char* content,size_t len_){
    save_seed(content,len_,out_dir,"id");
}
