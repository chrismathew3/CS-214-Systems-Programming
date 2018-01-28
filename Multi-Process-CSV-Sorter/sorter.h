/*
	Creators: Chris Mathew & Jacek Zarski
	Project: Basic Data Sorter
	School: Rutgers University-New Brunswick
	Course: CS 214 Systems Programming
	Professor: Andrew Tjang
*/

#ifndef DATASORTER_SORTER_H
#define DATASORTER_SORTER_H

#define BUFSIZE 1024m
#define MAX_PIDS 1024


#define TRUE 1
#define FALSE 0

volatile pid_t* pids;
volatile int* pidIndex;
int num_rows;
int num_cols;
int target_col;
int num_forks;
int num_children;
char* s_text;
char* str_csv;
char* target;
char* pdir;
char* odir;

typedef struct{
    char** content;
    char* line;
    size_t length;
    size_t num_cols;
    size_t num_rows;
}record;


#include "mergesort.c"


char* delim = ",";
FILE *fp;

int main(int argc, char** argv);
char* str_strip(char* s);
int parse(FILE* input, record* temp);
void print_col(record* data, FILE* fp);
void print_data(record* data);
char** get_token(char* line);
void Merge(record* L, record* R, record* result, int l, int h);
void MergeSort(record* arr, int h);
void child_csv(FILE* fp, char* out);
int get_target_col(record head);
void traverse_dir(const char *name, int p);

#endif 
