#ifndef SORTER_H
#define SORTER_H

#define TRUE 1
#define FALSE 0
int num_rows;
int num_cols;
int target_col;
char* target;

typedef struct{
	char** content;
	char* line;
	size_t length;
	size_t cols;
}record;

char* delim = ",";
FILE *fp;

int main(int argc, char** argv);
char* str_strip(char* s);
int parse(FILE* input, record* temp);
char** get_token(char* input);
void print_col(record* data);
void print_data(record* data);
#endif