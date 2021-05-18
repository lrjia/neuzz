//
// Created by lrjia on 2021/5/18.
//

#include "gen_bitmap.h"
#include<stdlib.h>
#include <assert.h>
#include <stdbool.h>

static char **test_file_argv=NULL;
static char* out_dir="./raw_bitmap";

void gen_bitmap(char **test_file_argv_, char *file_dir, char *out_dir_) {
    if(test_file_argv_!=NULL)
        test_file_argv = test_file_argv_;
    if(out_dir_!=NULL)
        out_dir = out_dir_;
    if (test_file_argv==NULL || out_dir==NULL) {
        perror("no test_file_argv or out_dir for gen_bitmap");
        assert(false);
    }


    char* argv[50]={0};
    int i=0;
    argv[i++] = "./afl-showmap";
    argv[i++]="-q";
    argv[i++]="-e";
    argv[i++]="-o";

    char* fileName=strrchr(file_dir,'/');
    if(fileName==NULL) fileName=file_dir;
    char out_file_dir[100];
    strcpy(out_file_dir,out_dir);
    strcat(out_file_dir,fileName);
    strcat(out_file_dir,".bitmap");
    argv[i++]= out_file_dir;

    argv[i++]="-m";
    argv[i++]="512";
    argv[i++]="-t";
    argv[i++]="500";

    int j=0;
    while (test_file_argv[j]){
        if(test_file_argv[j][0]!='@'){
            argv[i++]=test_file_argv[j];
        }
        j++;
    }

    argv[i++]=file_dir;
    char str_zero[]={0};
    argv[i]=str_zero;

//    int err=execv("./afl-showmap", argv);
    char command[1000]={0};
    for (int k = 0; strlen(argv[k])>0; ++k) {
        strcat(command,argv[k]);
        strcat(command," ");
    }
    int err=system(command);
         if(err==-1){
        perror("error when exec afl-showmap");
    }
}

void gen_all_bitmap(char **test_file_argv_, char *seed_dir, char *out_dir_) {
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;
    if ((dp = opendir(seed_dir)) == NULL) {
        fprintf(stderr, "cannot open directory: %s\n", seed_dir);
        return;
    }
    int cnt = 0;
    u64 start_us, stop_us;
    while ((entry = readdir(dp)) != NULL) {
        char *file_name = (char *) malloc(strlen(seed_dir) + strlen(entry->d_name) + 10);
        strcpy(file_name, seed_dir);
        strcat(file_name, "/");
        strcat(file_name, entry->d_name);
        if (stat(file_name, &statbuf) == -1)
            continue;

        if (S_ISREG(statbuf.st_mode)) {
            char *tmp = NULL;
            tmp = strstr(entry->d_name, ".");
            if (tmp != entry->d_name) {
                gen_bitmap(test_file_argv_, file_name, out_dir_);
            }
        }
    }
}

