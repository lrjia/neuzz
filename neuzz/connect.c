//
// Created by lrjia on 2021/5/18.
//

#include "connect.h"
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>


void send_to_file(char *str) {
    printf("starting send\n");
    bool is_send = false;
    static int last_file_line = 0;
    while (!is_send) {
        FILE *fp = NULL;
        fp = fopen("./neuzz.log", "a");
        if (fp == NULL) {
            sleep(1);
            continue;
        }
        fprintf(fp, "%s\n", str);
        fclose(fp);
        is_send = true;
    }
    printf("send\n");
}

void receive_from_file(char *buf) {
    printf("starting receive\n");
    bool received = false;
    static int last_file_line = 0;
    while (!received) {
        FILE *fp = NULL;
        fp = fopen("./nn.log", "r");
        if (fp == NULL) {
            sleep(1);
            continue;
        }
        int line = 0;
        while (!feof(fp)) {
            if (fgets(buf, 6, fp) != NULL) {
                line++;
                if (line > last_file_line) {
                    assert(strcmp(buf, "start") == 0);
                    last_file_line++;
                    printf("receive\n");
                    received = true;
                    break;//每次只读取一个start信号
                }
            }
        }
        fclose(fp);
        if(!received){
            sleep(1);
        }
    }
    printf("received\n");
}

