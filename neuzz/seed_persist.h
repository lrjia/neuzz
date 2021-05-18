//
// Created by lrjia on 2021/5/18.
//

#ifndef NEUZZ_SEED_PERSIST_H
#define NEUZZ_SEED_PERSIST_H

void save_crash(char* content,size_t len_);
void add_to_queue(char* content,size_t len_);
extern int round_cnt;
extern int mut_cnt;
extern char* out_dir;

#endif //NEUZZ_SEED_PERSIST_H
