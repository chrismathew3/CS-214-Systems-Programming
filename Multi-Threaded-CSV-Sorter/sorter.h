/*
	Creators: Chris Mathew & Jacek Zarski
	Project: Basic Data Sorter
	School: Rutgers University-New Brunswick
	Course: CS 214 Systems Programming
	Professor: Andrew Tjang
*/

#ifndef DATASORTER_SORTER_H
#define DATASORTER_SORTER_H

#define BUFSIZE 1024
#define MAX_THREADS 1024


#define TRUE 1
#define FALSE 0
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <libgen.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>



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
char* str_strip(char* s);
void parse(FILE* input);
void print_col(record* data);
void print_data(record* data, FILE* out);
char** get_token(char* line);
void *csv_thread(void *pp);
int get_target_col(record head, char *column);
void *dir_thread(void *t);
void parser(char *csvPath);
void traverseDir(char* name);
void outputfile(record* input, int rows, char* column, char* dir);
void MergeSort(record* arr, int h, int t_col);
void Merge(record* L, record* R, record* result, int l, int h, int target_col);

#include "mergesort.c"


#endif
