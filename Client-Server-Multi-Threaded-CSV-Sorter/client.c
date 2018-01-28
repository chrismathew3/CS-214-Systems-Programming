/*
    Creators: Chris Mathew & Jacek Zarski
    Project: Client Mutli-Threaded Data Sorter
    School: Rutgers University-New Brunswick
    Course: CS 214 Systems Programming
    Professor: Andrew Tjang
*/

#include "client.h"


/* GLOBAL VARIABLES */
// Command Line Argument Variables
char *target;
char *hostname;
char *port;
char *pdir;
char *odir;

//Multi-Threading Variables
pthread_t *threads;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t csv_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t t_index_lock = PTHREAD_MUTEX_INITIALIZER;
int size_index = 0;
int t_index = 0;

//Middleware Variables
middleware *middleware_array;

//Record Variables
int num_cols = 28;
long target_col = -1;
char *target;
char *delim = ",";
FILE *fp;

//Socket Variables
int sockfd;

/* HELPER METHODS */

int getTarget(record headers){
    int counter;
    for(counter = 0; counter < headers.num_cols; counter++){
        if(strcmp(headers.content[counter], target) == 0){
            return counter;
        }
    }
    return -1;
}


/* RETURNS THE ADDRESS IN EITHER IPv4 OR IPv6 FORMAT */
void *get_in_addr(struct sockaddr *sa) {
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in *) sa)->sin_addr);
    }
    return &(((struct sockaddr_in6 *) sa)->sin6_addr);
}





/*PARSE FILE CHECK IF VALID CSV IF SO ADD TO MASTER RECORD DATA*/
void sendcsv(char *csvPath) {
//    pthread_mutex_lock(&lock);
    //printf("PATH: %s\n", csvPath);
    FILE *csv = fopen(csvPath, "r");

    if (csv == NULL) {
        perror("Couldn't open file\n");
        fclose(csv);
        exit(0);
    }

    char line[SMALL]; // Read buffer

    fgets(line, SMALL, csv); //Get headers

    bzero(line, SMALL);
    fgets(line, SMALL, csv);
    while(strlen(line) > 1){
        write(sockfd, line, strlen(line));
        read(sockfd, line, 5);
        bzero(line, SMALL);
        fgets(line,SMALL, csv);
    }

//    pthread_mutex_unlock(&lock);
    bzero(line, SMALL);
    fclose(csv);
    return;
}

/*RECURSIVELY TRAVERSE DIRECTORIES CREATING THREADS TO DO SO*/
void traverseDir(char *name) {
    DIR *dir;
    struct dirent *entry;

    int csvSize = 256, csvIndex = 0, dirSize = 256, dirIndex = 0;
    char **csvList = (char **) calloc(csvSize, sizeof(char *));
    char **dirList = (char **) calloc(dirSize, sizeof(char *));

    if ((dir = opendir(name)) == NULL) {
        fprintf(stderr, "Can't open directory: %s\n", name);
        return;
    }
   //printf("About to traverse\n");

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, ".DS_Store") == 0 || strcmp(entry->d_name, ".git") == 0 ||
            strstr(entry->d_name, "AllFile-sorted") != NULL) {
            continue;
        }
//       //printf("Temp is: %s\n\n", temp);
        if (entry->d_type == DT_DIR) {
//           //printf("hi1");
           //printf("Found Dir\n");
            char *temp = (char *) malloc(sizeof(char) * SMALL);
            temp[0] = '\0';
            strcpy(temp, name);
            strcat(temp, "/");
            strcat(temp, entry->d_name);
            if(dirIndex == dirSize){
                dirSize *= 2;
                dirList = (char **) realloc(dirList, sizeof(char *) * (dirSize));
            }
            dirList[dirIndex] = (char *) malloc(sizeof(char) * SMALL);
            strcpy(dirList[dirIndex++], temp);

            free(temp);

        } else if (entry->d_type == DT_REG) {
            char *temp = (char *) malloc(sizeof(char) * SMALL);
            temp[0] = '\0';
            strcpy(temp, name);
            strcat(temp, "/");
            strcat(temp, entry->d_name);
            int len = strlen(temp);
            const char *last_four = &temp[len-4];
            if(strcmp(last_four, ".csv") == 0)
//            char *dot = strrchr(temp, '.');
//            if (dot && !strcmp(dot, ".csv"))
            {
                //printf("Found csv\n");

                if(csvIndex == csvSize){
                    csvSize *= 2;
                    csvList = (char **) realloc(csvList, sizeof(char *) * (csvSize));
                }
                csvList[csvIndex] = (char *) malloc(sizeof(char) * SMALL);
                strcpy(csvList[csvIndex++], temp);
                free(temp);
            }
        }
    }

    if(csvIndex > 0){
        int i;
        for(i = 0; i < csvIndex; i++){
            char *csvPath = (char *) calloc(sizeof(char), SMALL);
            strcpy(csvPath, csvList[i]);
            pthread_mutex_lock(&t_index_lock);
            t_index += 1;
            pthread_create(&threads[t_index - 1], NULL, csv_thread, csvPath);
            pthread_mutex_unlock(&t_index_lock);
        }
    }

    if(dirIndex > 0){
        int i;
        for(i = 0; i < dirIndex; i++){
            char *dirPath = (char *) calloc(1, SMALL);
            strcpy(dirPath, dirList[i]);
            pthread_mutex_lock(&t_index_lock);
            t_index += 1;
            pthread_create(&threads[t_index - 1], NULL, dir_thread, dirPath);
            pthread_mutex_unlock(&t_index_lock);
        }
    }

    closedir(dir);
    free(csvList);
    free(dirList);
    return;
}


/*THREAD ACTIVITIES FOR DIRECTORIES*/
void *dir_thread(void *dirName) {
    pthread_mutex_lock(&lock);

    //printf("Dir Thread\n");

    char *path = (char *) dirName;

    traverseDir(path);

    free(path);
    pthread_mutex_unlock(&lock);
    pthread_exit(NULL);
}

/* THREAD ACTIVITIES FOR CSV FILES*/
void *csv_thread(void *csvName) {
    pthread_mutex_lock(&csv_lock);

    //printf("CSV Thread started\n");

//    //printf("PATH: %s\n", csvName);

    char *path = (char *) csvName;
    sendcsv(path);
    pthread_mutex_unlock(&csv_lock);
    pthread_exit(NULL);
}

/* PRINT OUT SORTED DATA TO FILE */
void outputfile(char *dir) {
    char *title = "AllFiles-Sorted-";
    char *output = calloc(SMALL, sizeof(char));
    strcpy(output, title);
    strcat(output, target);
    strcat(output, ".csv");
    strcat(output, "\0");

    FILE *out = fopen(output, "a+");
    if (out == NULL) {
        perror("While creating file: ");
        free(output);
        fclose(out);
        return;
    }
    char line[SMALL];
    while(read(sockfd, line, SMALL) > 0){
        if(strncmp("done", line, 4) == 0){
            bzero(line, SMALL);
            break;
        }
        fputs(line,out);
//        fputs("\n",out);
        bzero(line, SMALL);
        write(sockfd, "ok", 2);
    }

    fclose(out);
    free(output);
    return;
}


/* MAIN PROGRAM */
int main(int argc, char **argv) {

///BEGINNING VARIABLE CREATION
    clock_t begin = clock();

    pdir = NULL;
    odir = NULL;

///END OF CREATIONS
///BEGINNING OF ARGUMENT CHECKING
    if (argc < 7) {
       //printf("Usage Formula: ./client -c <Field-Name> -h <Hostname> -p <Port Number> -d <Parent-Directory> -o <Output-Directory>");
        exit(0);
    }
    if (argc >= 7) {
        for (int i = 0; i < argc; i++) {
            if ((strcmp(argv[i], "-c") == 1) && (i == (argc - 1))) {
                fprintf(stderr, "Error: Must use the -c flag to indicate data to be sorted is a column");
                return 0;
            }
            if (strcmp(argv[i], "-c") == 0) {
                target = argv[i + 1];  //Value Type contains column to be sorted by
                target = strcat(target, "\0");
               //printf("Target Col is: %s\n", target);
            }
            if ((strcmp(argv[i], "-h") == 1) && (i == (argc - 1))) {
                fprintf(stderr, "Error: Must use the -h flag to indicate hostname of the server");
                return 0;
            }
            if (strcmp(argv[i], "-h") == 0) {
                hostname = argv[i + 1];  //Value Type contains the Hostname of the Server
                hostname = strcat(hostname, "\0");
               //printf("Hostname is: %s\n", hostname);
            }
            if ((strcmp(argv[i], "-p") == 1) && (i == (argc - 1))) {
                fprintf(stderr, "Error: Must use the -p flag to indicate port of the server");
                return 0;
            }
            if (strcmp(argv[i], "-p") == 0) {
                port = argv[i + 1];  //Value Type contains the Port of the Server
                port = strcat(port, "\0");
               //printf("port is: %s\n", port);
            }
            if (strcmp(argv[i], "-d") == 0) {
                pdir = argv[i + 1];  //Value Type contains parent directory
                pdir = strcat(pdir, "\0");
               //printf("Parent Directory is: %s\n", pdir);
            }
            if (strcmp(argv[i], "-o") == 0) {
                odir = argv[i + 1];  //Value Type contains the output directory
                odir = strcat(odir, "\0");
               //printf("Output Directory is: %s\n", odir);
            }
        }
        if (pdir == NULL) {
            pdir = ".";
           //printf("Parent Directory is: %s\n", pdir);
        }
        if (odir == NULL) {
            odir = ".";
           //printf("Output Directory is: %s\n", odir);
        }
    }

///END OF ARG CHECKING
///BEGINNING OF BASIC INITS & MALLOCS

    threads = (pthread_t *) calloc(SMALL, sizeof(pthread_t));

///END OF BASIC INITS & MALLOCS
///GET FULL PATH FOR PARENT DIRECTORY
    char *relative_dir;
    char *dir_parent;
    char *dir_output;
    dir_parent = realpath(pdir, relative_dir);


///END OF GETTING FULL PATH FOR PARENT DIRECTORY
///BEGINNING OF CONNECTING TO THE SERVER

    struct addrinfo hints, *serv, *p;
    int rv;
    char s[INET6_ADDRSTRLEN];
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    int iMode = 0;

    if((rv = getaddrinfo(hostname, port, &hints, &serv)) != 0){
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        exit(0);
    }

    for(p = serv; p != NULL; p = p->ai_next){
        if((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1){
            perror("Client: Socket");
            continue;
        }
        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == -1){
            perror("Client: connect");
            close(sockfd);
            continue;
        }
        break;
    }

    if(p == NULL){
        fprintf(stderr, "Client: Failure to connect to server\n");
        exit(1);
    }else{
        inet_ntop(p->ai_family, get_in_addr((struct sockaddr *) p->ai_addr), s, sizeof s);
       //printf("\nclient: connecting to %s\n", s);
    }


    char* greeting;
    read(sockfd,&greeting, 5);
   //printf("First Read\n");

///END OF CONNECTING TO THE SERVER
///BEGIN DIRECTORY TRAVERSAL -> SPAWN NEW THREADS -> SENDING FILES OVER 

    if (dir_parent != NULL) {
        traverseDir(dir_parent);
    }
   //printf("Sent ALL CSVs\n");

///FINISHED TRAVERSAL & SENDING CSV DATA
///BEGINNING TO JOIN THREADS 

 /* Wait for all threads to complete */

    freeaddrinfo(serv);


    int i;
    for (i = 0; i < t_index; i++) {
        pthread_join(threads[i], NULL);
    }

///END OF JOINING THREADS
///BEGIN TO REQUEST SERVER FOR DATA

    char line[SMALL];
    bzero(line, SMALL);
    write(sockfd, "done", SMALL);

    read(sockfd, line, 5);
    bzero(line, SMALL);
    write(sockfd, target, strlen(target));
    read(sockfd, line, 5);
    bzero(line, SMALL);
    dir_output = realpath(odir, relative_dir);

    if (dir_output != NULL) {
        outputfile(dir_output);
    }

    close(sockfd);
    clock_t end = clock();
    double time_spent = (double) (end - begin) / CLOCKS_PER_SEC;
    free(threads);
    return 0;
}

