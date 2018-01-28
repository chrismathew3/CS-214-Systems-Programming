/*
    Creators: Chris Mathew & Jacek Zarski
    Project: Basic Data Sorter
    School: Rutgers University-New Brunswick
    Course: CS 214 Systems Programming
    Professor: Andrew Tjang
*/

#ifndef DATASORTER_SORTER_H
#define DATASORTER_SORTER_H

#define PORT "3490" // the port users will be connecting to
#define BACKLOG 10 // how many pending connections queue will hold
#define EXTRASMALL 512
#define SMALL 1024
#define MEDIUM 2048
#define LARGE 4096
#define MAX 8192
#define MAX_THREADS 1024

#define START "~"
#define END "^"
#define DMP "^~"

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<math.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ctype.h>
#include <dirent.h>
#include <libgen.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/un.h>
#include <sys/ioctl.h>
#include <sys/select.h>



/*  STRUCT DEFINITIONS */

//typedef struct record{
//    char **content;
//}record;

typedef struct record{

    int num_critic_for_reviews; // .
    int duration; // .
    int director_facebook_likes; // .
    int actor_3_facebook_likes; // .
    int actor_1_facebook_likes; // .
    int gross; // .
    int num_voted_users; // .
    int cast_total_facebook_likes; // .
    int num_user_for_reviews; // .
    int facenumber_in_poster; // .
    int budget; // .
    int title_year; // .
    int actor_2_facebook_likes; // .
    int movie_facebook_likes; // .


    double imdb_score; // .
    double aspect_ratio; // .


    char director_name[50]; // .
    char actor_2_name[50]; // .
    char actor_3_name[50]; // .
    char actor_1_name[50]; // .
    char language [50]; // .
    char country[50]; // .
    char content_rating[50]; // .


    char color[100]; // .
    char genres[100]; // .
    char movie_imdb_link [100]; // .


    char movie_title[500]; // .
    char plot_keywords [500]; // .
}record;

typedef struct socket_struct{
    int client_socket;
    int id;
}socket_struct;

typedef struct name{
    char file[100];
    int index;
}name;

/*  GLOBAL VARIABLES */
FILE* f_out;
FILE* p_out;
FILE* extra;
char *port;
char *delim = ",";
char dir_output[SMALL];
char target[50];
int cli_sock[5000];
socklen_t cli_lens[5000];
int cli_index = 0;
int ID = 0;
int thread_index = 0;
int thread_limit = 5000;
pthread_mutex_t master_mutex = PTHREAD_MUTEX_INITIALIZER;

/* GLOBAL STRUCTS & POINTERS */
pthread_t *threads;
socket_struct * sockets;
struct sockaddr_in client[5000];

void print_Data(record *Data, FILE *out, char *sortColumn, int size);
char *trim(char *input);
int split(char first[], char second[], int index);
void get_records(int sock, char file[]);
void sendcsv(char *filename, int client_socket);
void *client_thread(void *info);
void signal_callback_handler(int signum);
int main(int argc, char **argv);
int adjust_num(double num);
void MergeSort(record* arr, int h, char *t_col);
void Merge(record* L, record* R, record* result, int l, int h, char *sortColumn);

#endif
