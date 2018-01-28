/*
    Creators: Chris Mathew & Jacek Zarski
    Project: Basic Data Sorter
    School: Rutgers University-New Brunswick
    Course: CS 214 Systems Programming
    Professor: Andrew Tjang
*/


#include "sorter.h"

/* GLOBAL VARIABLES */
pthread_t *threads; //CONTAINS ALL THREADS
pthread_mutex_t lock;
int size_index = 0;
int t_index = 0;
int csv_counter = 0;
int row_counter = 0;

record *Data;

middleware *middleware_array;
int dirCount = 0;

int num_cols = 28;
int target_col = -1;
int max_size = 1024;
int current_size = 0;
int a;
char* target;
char* pdir;
char* odir;
char* delim = ",";
FILE *fp;


/* HELPER METHODS */


/* PRINTS TARGET COLUMN Data */
void print_col(record *Data) {
    int a = 0;
    while (a < size_index - 1) {
        printf("%s,", Data[a].content[target_col]);
        printf("\n");
        a++;
    }
    printf("%s", Data[size_index - 1].content[target_col]);
}


/* FOR DEBUGGING PURPOSES */
void print_Data(record *Data, FILE* out) {
    int a = 0;
    while (a < row_counter ) {
        fprintf(out, "%s,\n", Data[a].content[target_col]);   
        a++;
    }
}


/* TOKENIZER */
char **get_token(char *line) {
    int i, j, k;
    i = 0;//LINE;
    j = 0;//TEMP;
    k = 0;//RESULT;
    char **output = (char **) calloc(2048, sizeof(char *)); //return value;
    char *temp = (char *) calloc(1024, sizeof(char));//store each word;
    temp[i] = '\0';
    size_t quote = FALSE;//1 quote start, 0 quote end;
    //go through each character;
    while (line[i] != '\n') {
        if (line[i] == '"' && quote == FALSE) {
            quote = TRUE;
        } else if (line[i] == '"' && quote == TRUE) {
            //store value in result
            output[k] = (char *) malloc(sizeof(char) * 1000);
            output[k][0] = '\0';
            temp = str_strip(temp);
            strcpy(output[k], temp);
            memset(temp, 0, sizeof(char) * 1000);
            temp[0] = '\0';

            quote = FALSE;
            j = 0;
            k++;
            i++;
        } else if (line[i] == ',' && quote != TRUE) {
            //split by ',' or reach the end of line;
            output[k] = (char *) malloc(sizeof(char) * 1000);
            output[k][0] = '\0';
            temp = str_strip(temp);
            strcpy(output[k], temp);
            memset(temp, 0, sizeof(char) * 1000);
            temp[0] = '\0';

            j = 0;
            k++;
        } else {
            //copy character from line to temp;
            if (j == 0 && line[i] == ' ') {
                i++;
                continue;
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
int get_target_col(record head, char *column) {
    int counter;
    for (counter = 0; counter < 28; counter++) {
        if (strcmp(head.content[counter], column) == 0) {
            return counter;
        }
    }
    return -1;
}

/*PARSE FILE CHECK IF VALID CSV IF SO ADD TO MASTER RECORD DATA*/
void parser(char *csvPath) {

    pthread_mutex_lock(&lock);
    FILE *csv = fopen(csvPath, "r");
    printf("In Parser: Opened file\n");

    if (csv == NULL) {
        printf("Couldn't open file\n");
        fclose(csv);
        pthread_mutex_unlock(&lock);
        pthread_exit(NULL);
    }

    char* token;
    //bzero(&token, 1024);
    record headers;
    headers.line = (char*) calloc(1024, sizeof(char));
    headers.num_cols = 0;
    size_t size = 0;
    //printf("In Parser \n");
    fgets(headers.line, 1024, csv);
    //printf("Headers line is: %s\n", headers.line);
    headers.length = strlen(headers.line);
    headers.content = (char **) calloc(1024, sizeof(char *));

    printf("In Parser: Begun Getting Headers\n");

    while ((token = strtok_r(headers.line, delim, &headers.line))) {
        //strcpy(headers.content[headers.num_cols], token);
        headers.content[headers.num_cols] = token;
        headers.num_cols++;
        //bzero(&token, 1024);

    }
    printf("In Parser: Got Headers\n");
    if(headers.num_cols < 27 || headers.num_cols > 28 ){
        printf("CSV is not valid");
        pthread_mutex_unlock(&lock);
        pthread_exit(NULL);
    } else {
        csv_counter += 1;
    }
    printf("In Parser: CSV counter += 1\n");
    //printf("Headers at 0 is: %s", headers.content[0]);
    if(target_col == -1){
        target_col = get_target_col(headers, target);
        //printf("Target col is: %d\n", target_col);
    }
    free(headers.content);
    free(headers.line);
    printf("In Parser: freed headers\n");

    

    char* line = (char*) calloc(1024, sizeof(char));

    if(row_counter == 0){
        Data = (struct record *) calloc(1024, sizeof(record));
        printf("In Parser: malloc'd data\n");


    }
    
    while ((fgets(line, 1024, csv)) != NULL) {
        
        //printf("Line is: %s\n", line);
        int line_len = strlen(line);
        Data[row_counter].content = (char **) calloc(1024, sizeof(char *));
        Data[row_counter].content = get_token(line);
        int i;
        //printf("Got token\n");
        for(i = 0; i < 28; i++){
            Data[row_counter].content[i] = str_strip(Data[row_counter].content[i]);
        }
        //printf("Stripped content\n");
        
        if(row_counter == max_size-2) {
            max_size = max_size * 2;
            Data = (struct record*)realloc(Data, (max_size * sizeof(record)));
            printf("REALLOC'D\n");
        }
        row_counter += 1;
        //memset(&line,'\0',1024);
    }
    printf("FINISHED CSV\n");
    free(line);
    fclose(csv);
    pthread_mutex_unlock(&lock);
    return;
}

/*RECURSIVELY TRAVERSE DIRECTORIES CREATING THREADS TO DO SO*/
void traverseDir(char* name)
{
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(name)) == NULL)
    {
        fprintf(stderr, "Can't open directory: %s\n", name);
        return;
    }
    printf("In Traverse: Opened DIR\n");


    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 || strcmp(entry->d_name, ".DS_Store") == 0 || strcmp(entry->d_name, ".git") == 0 || strstr(entry->d_name, "AllFile-sorted") != NULL)
        {
                continue;
        }

        char* temp = (char*)malloc(strlen(name) + strlen(entry->d_name));
        strcpy(temp, name);
        strcat(temp, "/");
        strcat(temp, entry->d_name);
        //printf("Temp is: %s\n\n", temp);

        
        if (entry->d_type == DT_DIR)
        {
            printf("In Traverse: Found DIR\n");
            //printf("hi1");
            
            middleware dir_tmp;
            dir_tmp.file_path = (char *)malloc(sizeof(char)*strlen(temp)+3);
            strcpy(dir_tmp.file_path,temp);
            

            middleware_array[t_index] = dir_tmp;
            pthread_create(&threads[t_index],NULL,dir_thread,&middleware_array[t_index]);
            t_index += 1;

            
            free(temp);
            
        } else if(entry->d_type == DT_REG)
        {
            //printf("before\n");
            char *dot = strrchr(temp, '.');
            if (dot && !strcmp(dot, ".csv"))
            {
            
                printf("In Traverse: Found CSV\n");
                middleware csv_tmp;
                csv_tmp.file_path = (char *)malloc(sizeof(char)*strlen(temp)+3);
                strcpy(csv_tmp.file_path,temp);
                //printf("middle\n");

                middleware_array[t_index] = csv_tmp;
                pthread_create(&threads[t_index],NULL,csv_thread,&middleware_array[t_index]);
                t_index += 1;
                

                free(temp);
            }
        }
        //free(temp);        
    }
    closedir(dir);
}


/*THREAD ACTIVITIES FOR DIRECTORIES*/
void *dir_thread(void *t) 
{
    //printf("DIR thread method reached\n");

    pthread_mutex_lock(&lock);
    printf("Created DIR Thread\n");

    middleware *dirInfo = (middleware *) t;

    char *path = (char *) malloc( sizeof(char) * 1000);

    strcpy(path, dirInfo->file_path);
    traverseDir(path);

    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);

}

/* THREAD ACTIVITIES FOR CSV FILES*/
void *csv_thread(void *t) 
{
    printf("Created CSV Thread\n");
    //printf("CSV thread method reached\n");
    middleware *dirInfo = (middleware *) t;

    char *path = (char *) malloc( sizeof(char) * 1000);
    strcpy(path, dirInfo->file_path);

    parser(path);
    
    pthread_exit(NULL);
}

/* PRINT OUT SORTED DATA TO FILE*/
void outputfile(record* input, int rows, char* column, char* dir){
    printf("Outputing FILE\n");
    char* title = "AllFile-Sorted-";
    char* output = (char*)calloc(1024, sizeof(char));
    strcpy(output, dir);
    strcat(output, "/");
    strcat(output, title);
    strcat(output, column);
    strcat(output, ".csv");
    
    FILE* out = fopen(output, "w+");
    if (out == NULL) {
        printf("WRONG FILENAME.\n");
        exit(1);
    }
    print_Data(input, out);

}

/* MAIN PROGRAM */
int main(int argc, char *argv[]) 
{

    /* ARGUMENT ERROR CHECKING */
    clock_t begin = clock();
    pdir = NULL;
    odir = NULL;

    if (argc < 3) 
    {
        fprintf(stderr, "Error: You need at least three arguments\n");
    } 
    else 
    {
        int i;
        for (i = 0; i < argc; ++i) 
        {
            if (strcmp(argv[i], "-h") == 0) 
            {
                printf("Usage: ./sorter -c <Field-Name> -d <Parent-Directory> -o <Output-Directory> \n");
                return 0;
            }
            if ((strcmp(argv[i], "-c") == 1) && (i == (argc - 1))) 
            {
                fprintf(stderr, "Error: Must use the -c flag to indicate Data to be sorted is a column");
                return 0;
            }
            if (strcmp(argv[i], "-c") == 0) 
            {
                target = argv[i + 1];  //Value Type contains column to be sorted by
                target = strcat(target, "\0");
                printf("Target Col is: %s\n", target);
            }
            if (strcmp(argv[i], "-d") == 0) 
            {
                pdir = argv[i + 1];  //Value Type contains parent directory
                pdir = strcat(pdir, "\0");
                printf("Parent Directory is: %s\n", pdir);
            }
            if (strcmp(argv[i], "-o") == 0) 
            {
                odir = argv[i + 1];  //Value Type contains the output directory
                odir = strcat(odir, "\0");
                printf("Output Directory is: %s\n", odir);
            }
        }
        if (pdir == NULL) 
        {
            pdir = ".";
            //printf("Parent Directory is: %s\n", pdir);
        }
        if (odir == NULL) 
        {
            odir = ".";
            //printf("Output Directory is: %s\n", odir);
        }
    }
    
        printf("ARG check was succesful\n");

    /* Initialize mutex objects */
    pthread_mutex_init(&lock, NULL);
   

    threads = (pthread_t *) malloc(sizeof(pthread_t) * 1024);
    middleware_array = (struct middleware *) malloc(sizeof(middleware) * 1024);

    printf("MALLOC'D: Threads & Middleware\n");

    char *dir_ptr;
    dir_ptr = realpath(pdir, NULL);
    //printf("Dir ptr is: %s\n Pdir is: %s\n",dir_ptr, pdir);
    
    if (dir_ptr != NULL) 
    {
        traverseDir(dir_ptr);
    } 

    
    /* Wait for all threads to complete */
    
    printf("Initial TID: %d\n", (int)threads[0]);


    printf("TIDS of all child threads:");
    int i;
    for (i = 0; i < t_index; i++) {
        printf("%d, ", (int)threads[i]);
        pthread_join(threads[i], NULL);
    }
    printf("\nTotal number of threads is: %d\n", t_index);

    MergeSort(Data, row_counter, target_col);
   
    char* dir_out;
    dir_out = realpath(odir,NULL);

    if(dir_out != NULL)
    {
        outputfile(Data, row_counter, target, dir_out);
    }
    
    
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);

    pthread_mutex_destroy(&lock);
    pthread_exit(NULL);

    free(dir_out);
    free(dir_ptr);
    free(Data);
    free(middleware_array);
    free(threads);

    
    return 0;
}
