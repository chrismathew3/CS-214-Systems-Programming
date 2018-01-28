/*
    Creators: Chris Mathew & Jacek Zarski
    Project: Basic Data Sorter
    School: Rutgers University-New Brunswick
    Course: CS 214 Systems Programming
    Professor: Andrew Tjang
*/


#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <libgen.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include "sorter.h"


/* PRINTS TARGET COLUMN DATA */
void print_col(record *data, FILE* fp) {
    int a = 0;
    while (a < num_rows - 1) {
        fprintf(fp, "%s,", data[a].content[target_col]);
        fprintf(fp, "\n");
        a++;
    }
    fprintf(fp, "%s", data[num_rows - 1].content[target_col]);
}


/* FOR DEBUGGING PURPOSES */
void print_data(record *data) {
    int a = 0;
    int b;
    while (a < num_rows) {
        b = 0;
        while (b < num_cols) {
            printf("%s", data[a].content[b]);
            b++;
        }
        a++;
    }
}


/* TOKENIZER */
char **get_token(char *line) {
    int i, j, k;
    i = 0;//current position in line;
    j = 0;//current position in tmp;
    k = 0;//current position in result;

    char **output = (char **) malloc(sizeof(char *) * (num_cols + 1)); //return value;
    char *temp = (char *) malloc(500);//store each word;
    size_t quote = FALSE;//1 quote start, 0 quote end;

    //go through each character;
    while (i < strlen(line)) {

        /*reach the start '"' */
        if (line[i] == '"' && quote == FALSE) {
            quote = TRUE;
        } else if (line[i] == '"' && quote == TRUE) {
            //store value in result
            output[k] = (char *) malloc((j + 1) * sizeof(char));
            temp = str_strip(temp);
            strcpy(output[k], temp);
            memset(&temp[0], 0, strlen(temp));
            quote = FALSE;
            j = 0;
            k++;
            i++;
        }

            //split by ',' or reach the end of line;
        else if ((line[i] == ',' || i == strlen(line) - 1) && quote != TRUE) {
            //if there is no character; (eg: ,,)
            if (!temp) {
                temp[0] = '\0';
            }
            if (i == strlen(line) - 1 && line[i] != '\n') {
                temp[j] = line[i];
                j++;
            }
            //store value to result;
            output[k] = (char *) malloc((j + 1) * sizeof(char));
            temp = str_strip(temp);
            strcpy(output[k], temp);
            memset(&temp[0], 0, strlen(temp));
            j = 0;
            k++;
            //if the last character is ',';
            if (line[i] == ',' && i == strlen(line) - 2) {
                temp[0] = '\0';
                output[k] = (char *) malloc((j + 1) * sizeof(char));
                strcpy(output[k], temp);
                memset(&temp[0], 0, strlen(temp));
            }

        } else {
            //copy character from line to temp;
            if (j == 0) {
                if (line[i] == ' ') {
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
    free(temp);
    return output;
}


/* PARSE FILE AND STORE DATA */
int parse(FILE *input, record *body) {
    num_rows = 0;
    record temp;
    temp.line = (char *) malloc(sizeof(char) * 1000);

    while ((fgets(temp.line, 1000, input))) {

        temp.length = strlen(temp.line);
        temp.content = (char **) malloc(sizeof(char *) * 1000);
        temp.content = get_token(temp.line);
        body[num_rows++] = temp;
    }

    free(temp.line);
    free(temp.content);
    return num_rows;
}


/* STRIP STRINGS OF PRECEDING AND TRAILING WHITESPACE */
char *str_strip(char *s) {
    if (s) { /* Don't forget to check for NULL! */
        while (*s && isspace(*s))
            ++s;
        if (*s) {
            register char *p = s;
            while (*p)
                ++p;
            do {
                --p;
            } while ((p != s) && isspace(*p));
            *(p + 1) = '\0';
        }
    }
    return (s);

}

/* GETS TARGET COLUMN */
int get_target_col(record head) {
    int counter;
    for (counter = 0; counter < head.num_cols; counter++) {
        if (strcmp(head.content[counter], target) == 0) {
            return counter;
        }
    }
    return -1;
}


/* NEW PROCESS FOR CHILD CSV */
void child_csv(FILE* fp, char* out) {
    printf("\nGOT HERE\n"); 

    char* temp;
    int out_len = strlen(out) + strlen(s_text) + strlen(target) + strlen(str_csv) + 5;
    temp = (char*)malloc(out_len * sizeof(char));
    strncpy(temp, out, strlen(out)-4);
    temp = strcat(temp, s_text);
    temp = strcat(temp, target);
    temp = strcat(temp, str_csv);
    temp = strcat(temp, "\0");
    printf("\nGOT HERE1\n"); 
    printf("\n%s\n", temp);

    char serv_name[1000];
    mkdir(odir, S_IRWXU | S_IRWXG | S_IRWXO);
    snprintf(serv_name, sizeof(serv_name), "%s/%s", odir,temp);
    FILE* ofp = fopen(serv_name, "w");
    if (ofp < 0) 
    {
        perror("CLIENT:\n");
        exit(1);
    }   
    
    free(temp);
    
    record headers;
    char *token;
    headers.num_cols = 1;
    headers.line = (char *) malloc(sizeof(char) * 1000);
    fgets(headers.line, 1000, fp);
    headers.length = strlen(headers.line);
    headers.content = (char **) malloc(sizeof(char *) * headers.length);
    token = strtok(headers.line, delim);
    headers.content[0] = token;

    while ((token = strtok(NULL, delim))) 
    {
        headers.content[headers.num_cols] = token;
        headers.num_cols++;
    }

    int length = strlen(headers.content[headers.num_cols - 1]);

    if (strcmp(&headers.content[headers.num_cols - 1][length - 1], "\0") != 0) 
    {
        headers.content[headers.num_cols - 1][length - 1] = '\0';
    }

    for (int i = 0; i < headers.num_cols; i++) 
    {
        headers.content[i] = str_strip(headers.content[i]);
    }
    num_cols = headers.num_cols;

    target_col = get_target_col(headers);
    
    record *body;
    body = (record *) malloc(sizeof(record) * 10000);
    num_rows = parse(fp, body);
    MergeSort(body, num_rows);
    print_col(body, ofp);
    free(body);
    free(headers.content);
    free(headers.line);
    fclose(fp);
    fclose(ofp);
    exit(0);
}


void traverse_dir(const char *name, int p) {
    struct stat statbuf;
    char path[FILENAME_MAX];
    char fname[FILENAME_MAX];
    int status;
    pid_t pID = 1;

    DIR *dir;
    struct dirent *dp = NULL;

    /* ERROR DETECTED */
    if (stat(name, &statbuf) == -1) 
    {
        perror("stat");
        exit(0);
    }


    if ((statbuf.st_mode & S_IFMT) == S_IFDIR) 
    {
        pID = fork();

        /* ERROR DETECTED */
        if (pID < 0) 
        {
            perror("fork");
            abort();
        } 
        /* PARENT */
        else if (pID > 0) 
        {    
            waitpid(pID, &status, WUNTRACED);
        } 
        else if (pID == 0) 
        {
            
            pids[(*pidIndex)++] = getpid();
            

            if ((dir = opendir(name)) == NULL) 
            {
                printf("Cannot open %s\n", name);
                exit(EXIT_FAILURE);
            } 
            else 
            {
                while ((dp = readdir(dir)) != NULL) 
                {

                    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
                        continue;
                    sprintf(fname, "%s/%s", name, dp->d_name); //STORES THE PATH TO FNAME
                    
                    int len = strlen(dp->d_name);
                    if(len > 4)
                    {
                        const char *last_four = &dp->d_name[len-4];
                        if(strcmp(last_four, ".csv") == 0)
                        {
                            

                            pID = fork();
                            if (pID < 0) 
                            {
                                perror("fork");
                                abort();
                            } 
                            /* PARENT */
                            else if (pID > 0) 
                            {    
                                waitpid(pID, &status, WUNTRACED);
                            } 
                            else if (pID == 0) 
                            {

                                
                                
                                

                                char* output = dp->d_name;
                               
                                pids[(*pidIndex)++] = getpid();

                                FILE* csv = fopen(fname, "r");
                                if (csv == NULL)
                                {
                                    printf("Couldn't open file\n");
                                    exit(0);
                                }
                               
                                child_csv(csv, output);
                                

                            }

                        }
                    }
                    traverse_dir(fname,p);
                }
                closedir(dir);
                exit(0);
            }
        }
    }
}


/* MAIN PROGRAM */
int main(int argc, char *argv[]) {

    clock_t begin = clock();
    /* ARGUMENT ERROR CHECKING */
    if (argc < 3) 
    {
        fprintf(stderr, "Error: You need at least three arguments\n");
    }

    if (strcmp(argv[1], "-h") == 0) 
    {
        printf("Usage: ./sorter -c <Field-Name> -d <Parent-Directory> -o <Output-Directory> \n");
    }

    if (strcmp(argv[1], "-c") == 1) {
        fprintf(stderr, "Error: Must use the -c flag to indicate data to be sorted is a column");
    }

    if (strcmp(argv[1], "-c") == 0) 
    {
        target = argv[2];  //Value Type contains string of type to be sorted by
        target = strcat(target, "\0");
    }

    if (argc > 3) 
    {
        if (strcmp(argv[3], "-d") == 0) 
        {
            pdir = argv[4];  //Value Type contains string of type to be sorted by
            pdir = strcat(pdir, "\0");
            
        }
        if (argc > 5) 
        {
            if (strcmp(argv[5], "-o") == 0) 
            {
                odir = argv[6];  //Value Type contains string of type to be sorted by
            }
        }
    }

    /* CHECK IF INPUT DIRECTORY ARG WAS ENTERED */
    if (argc < 4) 
    {
        pdir = ".";
    }

    /* CHECK IF OUTPUT DIRECTORY ARG WAS ENTERED */
    if (argc < 6) 
    {
        odir = ".";
    }

    num_children = 0;
    num_forks = 0;
    s_text = "-sorted-";
    str_csv = ".csv";
    pids = mmap(0, MAX_PIDS*sizeof(pid_t), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (!pids) 
    {
        perror("mmap failed");
        exit(1);
    }

    int pindex = 0;
    memset((void *)pids, 0, MAX_PIDS*sizeof(pid_t));
    pidIndex = mmap(0, sizeof(int), PROT_READ|PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (!pidIndex) 
    {
        perror("mmap failed");
        exit(1);
    }
    memset((int *)pidIndex, 0, sizeof(int));

    printf("Initial PID: %d\n", getpid());

    traverse_dir(pdir, pindex);

    printf("PIDS of all child processes: ");
    int a = 0;
    for(; a < *pidIndex - 1; a++)
    {
        printf("%d, ",pids[a]);
    }
    printf("%d",pids[++a]);
    printf("Total number of processes: %d", *pidIndex);
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\n Running time was: %f", time_spent);

    
    
    return 0;
}
