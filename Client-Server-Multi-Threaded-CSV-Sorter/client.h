#ifndef CLIENT_H
#define CLIENT_H

#define EXTRASMALL 512
#define SMALL 1024
#define MEDIUM 2048 /* Max Text Line Length*/
#define LARGE 4096 /* Max # of bytes you can get at once */
#define MAX 8192

#define START "~"
#define END "^"
#define DUMP "^~"

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ctype.h>
#include <dirent.h>
#include <libgen.h>
#include <fcntl.h>
#include <limits.h>
#include <pthread.h>

typedef struct record{
    char** content;
    char* line;
    size_t length;
    int num_cols;
    int num_rows;
}record;

typedef struct middleware{
    char *file_path;
    char *focus_col;
}middleware;

int main(int argc, char** argv);
void *csv_thread(void *csvName);
long get_target_col(record head, char *column);
void *dir_thread(void *dirName);
void sendcsv(char *csvPath);
void traverseDir(char* name);
void outputfile( char* dir);
void *get_in_addr(struct sockaddr *sa);

#endif
