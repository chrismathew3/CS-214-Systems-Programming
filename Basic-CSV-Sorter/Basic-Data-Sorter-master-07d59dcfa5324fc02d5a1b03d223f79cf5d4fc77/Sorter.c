/*
	Creators: Chris Mathew & Jacek Zarski
	Project: Basic Data Sorter
	School: Rutgers University-New Brunswick
	Course: CS 214 Systems Programming
	Professor: Andrew Tjang
*/


#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "sorter.h"


void print_col(record* data){
	int a = 0;
	while(a < num_rows-1)
	{
		printf("%s,", data[a].content[target_col]);
		a++;
	}
	printf("%s", data[num_rows-1].content[target_col]);
}

/* FOR DEBUGGING PURPOSES */
void print_data(record* data){
	int a = 0;
	int b;
	while(a < num_rows)
	{
		b = 0;
		while(b < num_cols)
		{
			printf("%s", data[a].content[b]);
			b++;
		}
		a++;
	} 
}



char** get_token(char* line){
	int i, j, k;
    i = 0;//current position in line;
    j = 0;//current position in tmp;
    k = 0;//current position in result;
    
    char** output = (char**)malloc(sizeof(char*) * (num_cols + 1)); //return value;
    char* temp = (char*)malloc(500);//store each word;
	size_t quote = FALSE;//1 quote start, 0 quote end;
	
    //go through each character;
    while(i < strlen(line)){
		
		/*reach the start '"' */
		if(line[i] == '"' && quote == FALSE){
			quote = TRUE;
		}
				
		else if(line[i] == '"' && quote == TRUE){
			//store value in result
			output[k] = (char*) malloc((j + 1) * sizeof(char));
			temp = str_strip(temp);
			strcpy(output[k], temp);
			memset(&temp[0], 0, strlen(temp));
			quote = FALSE;
			j = 0;
			k++;
			i++;
		}

		//split by ',' or reach the end of line;
        else if((line[i] == ',' || i == strlen(line) - 1) && quote != TRUE){
            //if there is no character; (eg: ,,)
            if(!temp){
                temp[0] = '\0';
			}
			if(i == strlen(line) - 1 && line[i] != '\n'){
				temp[j] = line[i];
				j++;
			}
            //store value to result;
			output[k] = (char*)malloc((j+1) * sizeof(char));
			temp = str_strip(temp);			
			strcpy(output[k], temp);
			memset(&temp[0], 0, strlen(temp));			
            j = 0;
			k++;
			//if the last character is ',';
			if(line[i] == ',' && i == strlen(line) - 2){
				temp[0] = '\0';
				output[k] = (char*)malloc((j+1) * sizeof(char));
				strcpy(output[k], temp);
				memset(&temp[0], 0, strlen(temp));								
			}

        }else{
			//copy character from line to temp;
			if(j == 0){
				if(line[i] == ' '){
					i++;
					continue;
				}				
			}
            temp[j] = line[i];
			j++;
		}
        i++;
	}
	i = 0;
	//printf("the num of col is %d", num_col);
	/*while(i < num_col){
		
		printf("the %dth token is:--%s--\n", i, result[i]);
		i++;
	}
	//printf("\n");*///debug
	free(temp);
    return output;
}




int parse(FILE* input, record* body)
{
	record temp;
	temp.line = (char*)malloc(sizeof(char) * 1000);

	while((fgets(temp.line, 1000, input)))
	{
		
		temp.length = strlen(temp.line);
		temp.content = (char**)malloc(sizeof(char*) * num_cols+1);
		temp.content = get_token(temp.line);
		body[num_rows++] = temp;
	}
	
	free(temp.line);
	free(temp.content);
	return num_rows;
}



char* str_strip(char* s)
{
    if(s) { /* Don't forget to check for NULL! */
        while(*s && isspace(*s))
            ++s;
        if(*s) {
            register char *p = s;
            while(*p)
                ++p;
            do {
                --p;
            } while((p != s) && isspace(*p));
            *(p + 1) = '\0';
        }
    }
    return(s);

}
int get_target_col(record head)
{	int counter;
	for(counter = 0; counter < num_cols; counter++)
	{
		if(strcmp(head.content[counter], target) == 0){
			return counter;
		}
	}
	return -1;
}



int main(int argc, char* argv[])
{

	/* MAKE SURE ARGS ARE CORRECT */
	if(argc != 3)
	{
		fprintf(stderr, "Error: You Need Three Arguments\n");
	}
	if(strcmp(argv[1], "-h") == 0)
	{
		printf("Usage: ./sorter -c <Value Type to be Sorted>\n");
	}
	if(strcmp(argv[1], "-c") == 1)
	{
		fprintf(stderr, "Error: Must use the -c flag to indicate data to be sorted is a column");
	}

	if(strcmp(argv[1], "-c") == 0)
	{
		target = argv[2];  //Value Type contains string of type to be sorted by
		target = strcat(target, "\0");
	}
	
	/* VARIABLES */
	fp = stdin; //correct
	num_cols = 1;
	char* token;

	/* GET HEADER */
	record headers;
	headers.line = (char*)malloc(sizeof(char) * 1000);
	fgets(headers.line, 1000,fp);
	headers.length = strlen(headers.line);
	headers.content = (char**)malloc(sizeof(char*)* headers.length);
	token = strtok(headers.line, delim);
	headers.content[0] = token;

	while((token = strtok(NULL, delim)))
	{
		headers.content[num_cols] = token;
		num_cols++;

	}
	headers.cols = num_cols;
	
	int length = strlen(headers.content[num_cols-1]);

	if(strcmp(&headers.content[num_cols-1][length-1], "\0") != 0){
		headers.content[num_cols-1][length-1] = '\0';
	}

	for(int i = 0; i < num_cols; i++)
	{
		headers.content[i] = str_strip(headers.content[i]);

	}

	/* GET TARGET COLUMN */
	target_col = get_target_col(headers);


	/*.GET REMAINING DATA */
	record* body;
	body = (record*)malloc(sizeof(record) * 10000);
	num_rows = parse(fp, body);

	print_col(body);
	
	free(body);
	free(headers.content);
	free(headers.line);
	return 0;
}