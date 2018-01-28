#include "server.h"
#include "mergesort.c"

int sockfd;

// LEFT OFF HERE
void print_Data(record *Data, FILE *out, char *sortColumn, int size) {


    if (strcmp(sortColumn, "color") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].color);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "director_name") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].director_name);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "num_critic_for_reviews") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].num_critic_for_reviews);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "duration") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].duration);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "director_facebook_likes") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].director_facebook_likes);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "actor_3_facebook_likes") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].actor_3_facebook_likes);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "actor_2_name") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].actor_2_name);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "actor_1_facebook_likes") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].actor_1_facebook_likes);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "gross") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].gross);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "genres") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].genres);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "actor_1_name") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].actor_1_name);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "movie_title") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].movie_title);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "num_voted_users") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].num_voted_users);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "cast_total_facebook_likes") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].cast_total_facebook_likes);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "actor_3_name") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].actor_3_name);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "facenumber_in_poster") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].facenumber_in_poster);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "plot_keywords") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].plot_keywords);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "movie_imdb_link") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].movie_imdb_link);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "num_user_for_reviews") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].num_user_for_reviews);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "language") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].language);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "country") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].country);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "content_rating") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%s,", Data[a].content_rating);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "budget") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].budget);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "title_year") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].title_year);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "actor_2_facebook_likes") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d,", Data[a].actor_2_facebook_likes);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "imdb_score") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%f,", Data[a].imdb_score);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "aspect_ratio") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%f,", Data[a].aspect_ratio);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else if (strcmp(sortColumn, "movie_facebook_likes") == 0) {
        int a = 0;
        while (a < size) {
            fprintf(out, "%d", Data[a].movie_facebook_likes);
            fprintf(out, "\n");
            a++;
        }
        return;
    } else {
        //printf("WRONG INPUT_ABORT\n");
        return;
    }
}

void outputfile(record *input, int rows, char *column, int session_ID) {
    char *output = (char *) malloc(sizeof(char) * 1024);
    sprintf(output, "%d%s.csv", session_ID, column);

    FILE *out = fopen(output, "a+");
    if (out == NULL) {
        //printf("WRONG FILENAME.\n");
        exit(1);
    }
    print_Data(input, out, column, rows);
    fclose(out);
    return;
}

char *trim(char *input) {


    //checking if the input is Null or contains nothing
    //return: Null
    if (input == NULL || strlen(input) < 1) {

        return input;
    }

    //variable i starts with the last letter of the word and proceeds backwards until hit an actual letter
    int i, j = 0;
    i = strlen(input) - 1;

    //executes until it hits a valid letter
    while ((input[i] == ' ' || input[i] == '\n') && i >= 0) {

        i--;
    }
    // no spaces found
    //return : input
    if (i == strlen(input) - 1) {
//input[strlen(input)+1] = '\0';
        return input;
    }
    input[i + 1] = '\0';
    /** got rid of all the trailing zero at this time**/



    /** starting from the start of string and removing all the leading zero**/
    while (input[j] == ' ') {


        j++;
    }

    if (!(j > 0)) {

        return input;
    }

    int index = 0;

    while (j <= i) {

        input[index] = input[j];
        j++;
        index++;
    }
    input[index] = '\0';


    return input;


}

int split(char first[], char second[], int index) {
    int i = 0;

    if (first[index] == '"') {


        second[i] = '"'; //putting " for the first character
        i++;
        index++; // getting after "

        while (first[index] != '"' && first[index] != '\0' && first[index] != '\n') { //until the next one comes

            second[i] = first[index];
            index++;
            i++;
        }
        second[i] = '"'; // putting " in the last character
        second[i + 1] = '\0';

        index = index + 2;
        return index;
    } else {

        while (first[index] != ',' && first[index] != '\0' && first[index] != '\n') {

            second[i] = first[index];
            index++;
            i++;

        }
        second[i] = '\0';
        index = index + 1;
        return index;
    }
}

void get_records(int sock, char file[]) {

    int client_socket = sock;
    int cli_ID;

    pthread_mutex_lock(&master_mutex);
    write(client_socket, &ID, 4);
    cli_ID = ID;
    ID++;
    pthread_mutex_unlock(&master_mutex);

//    fflush(stdout);
    char message[SMALL];
    record data;
    int x = 0;

    char token[EXTRASMALL];
    token[0] = '\0';

    record *tmp_arr;
    int tmp_max_size = LARGE;
    int tmp_current_size = 0;

    tmp_arr = (record *) calloc(LARGE, sizeof(record));
    int pc = 0;

    int msgSize = SMALL;

    while (read(client_socket, message, SMALL) > 0) {
//        //printf("here");
        if (strncmp("done", message, 4) == 0) {
            //printf("\nEnd of Transmission\n");
//            fflush(stdout);
            bzero(message, msgSize);
            break;
        }

        if (tmp_current_size == tmp_max_size) {
            tmp_max_size *= 3;
            tmp_arr = (record *) realloc(tmp_arr, (tmp_max_size) * (sizeof(record)));
        }

        pc = split(message, token, pc);
        data.color[0] = '\0';
        trim(token);
        strcpy(data.color, token);

        pc = split(message, token, pc);
        data.director_name[0] = '\0';
        trim(token);
        strcpy(data.director_name, token);
        //printf("%s\n", token);

        pc = split(message, token, pc);
        trim(token);
        data.num_critic_for_reviews = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.duration = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.director_facebook_likes = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.actor_3_facebook_likes = atoi(token);

        pc = split(message, token, pc);
        data.actor_2_name[0] = '\0';
        trim(token);
        strcpy(data.actor_2_name, token);

        pc = split(message, token, pc);
        trim(token);
        data.actor_1_facebook_likes = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.gross = atoi(token);

        pc = split(message, token, pc);
        data.genres[0] = '\0';
        trim(token);
        strcpy(data.genres, token);

        pc = split(message, token, pc);
        data.actor_1_name[0] = '\0';
        trim(token);
        strcpy(data.actor_1_name, token);

        pc = split(message, token, pc);
        data.movie_title[0] = '\0';
        trim(token);
        strcpy(data.movie_title, token);

        pc = split(message, token, pc);
        trim(token);
        data.num_voted_users = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.cast_total_facebook_likes = atoi(token);

        pc = split(message, token, pc);
        data.actor_3_name[0] = '\0';
        trim(token);
        strcpy(data.actor_3_name, token);

        pc = split(message, token, pc);
        data.facenumber_in_poster = atoi(token);
        trim(token);

        pc = split(message, token, pc);
        data.plot_keywords[0] = '\0';
        trim(token);
        strcpy(data.plot_keywords, token);

        pc = split(message, token, pc);
        data.movie_imdb_link[0] = '\0';
        trim(token);
        strcpy(data.movie_imdb_link, token);

        pc = split(message, token, pc);
        trim(token);
        data.num_user_for_reviews = atoi(token);

        pc = split(message, token, pc);
        data.language[0] = '\0';
        trim(token);
        strcpy(data.language, token);

        pc = split(message, token, pc);
        data.country[0] = '\0';
        trim(token);
        strcpy(data.country, token);

        pc = split(message, token, pc);
        data.content_rating[0] = '\0';
        trim(token);
        strcpy(data.content_rating, token);

        pc = split(message, token, pc);
        trim(token);
        data.budget = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.title_year = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.actor_2_facebook_likes = atoi(token);

        pc = split(message, token, pc);
        trim(token);
        data.imdb_score = atof(token);

        pc = split(message, token, pc);
        trim(token);
        data.aspect_ratio = atof(token);

        pc = split(message, token, pc);
        trim(token);
        data.movie_facebook_likes = atoi(token);

        pc = 0;

        tmp_arr[tmp_current_size] = data;
        tmp_current_size += 1;

        bzero(message, SMALL);

        write(client_socket, "ok", 2);
    }
    bzero(message, msgSize);
    write(client_socket, "ok", 2);

    read(client_socket, message, msgSize);

    //printf("\ndump request on column: %s\n", message);
//    fflush(stdout);
    write(client_socket, "ok", 2);

    MergeSort(tmp_arr, tmp_current_size, message);

//    print_col(tmp_arr,t_col_index,tmp_current_size);
    outputfile(tmp_arr, tmp_current_size, message, cli_ID);

//    printf("\nfile created and outputted\n");
//    fflush(stdout);

    char filename[500];

    sprintf(filename, "%d%s.csv", cli_ID, message);
    bzero(message, SMALL);

    sendcsv(filename,client_socket);

    close(client_socket);
    free(tmp_arr);
    return;
}

void sendcsv(char *filename, int client_socket) {
    FILE *csv = fopen(filename, "r");

    if (csv == NULL) {
        perror("Couldn't open file\n");
        fclose(csv);
        exit(0);
    }

    char line[SMALL]; // Read buffer

    fgets(line, SMALL, csv);
    while(strlen(line) >= 1){
        write(client_socket, line, strlen(line));
        read(client_socket, line, 5);
        bzero(line, SMALL);
        fgets(line,SMALL, csv);
    }

    if (remove(filename) == 0) {
//        printf("Deleted successfully");
    } else
        printf("Unable to delete the file");

//    pthread_mutex_unlock(&lock);
    bzero(line, SMALL);
    fclose(csv);
    return;
}

void *client_thread(void *info) {

    struct socket_struct *na = (struct socket_struct *) info;

    char file[15];
    sprintf(file, "%d", na->id);

    int cli_fd = na->client_socket;

//    printf("\nThread Started\n");
//    fflush(stdout);

    get_records(cli_fd, file);

    pthread_exit(NULL);
}

void signal_callback_handler(int signum) {
    printf("Caught signal %d\n", signum);
// Cleanup and close up stuff here
    printf("Initial PID: %d\n", threads[0]);
    printf("TIDS of all child threads:");
    int i;
    for (i = 0; i < cli_index; i++) {
        printf("%d, ", threads[i]);
        pthread_join(threads[i], NULL);
    }
    printf("\nTOTAL # of threads: %d, ", i);

    free(threads);
    free(sockets);
    close(sockfd);
    printf("Server Closed\n");
    exit(signum);
}

int main(int argc, char **argv) {

    if (argc < 3) {
        printf("Usage Formula: ./server -p <Port Number>");
        exit(0);
    }
    if (argc >= 3) {
        int i;
        for (i = 0; i < argc; i++) {
            if ((strcmp(argv[i], "-p") == 1) && (i == (argc - 1))) {
                fprintf(stderr, "Error: Must use the -p flag to indicate port");
                return 0;
            }
            if (strcmp(argv[i], "-p") == 0) {
                port = argv[i + 1];
                port = strcat(port, "\0");
                printf("port is: %s\n", port);
            }
        }
        if (port == NULL) {
            port = PORT;
            printf("port is: %s\n", port);
        }

    }

    threads = (pthread_t *) calloc(thread_limit, sizeof(pthread_t));
    sockets = (struct socket_struct *) calloc(thread_limit, sizeof(struct socket_struct));

    char buf[255];

    struct addrinfo hints, *servinfo, *p, cli;
    socklen_t cli_len;

    int yes = 1;
    int iMode = 0;
    char s[INET6_ADDRSTRLEN];
    int rv;
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
    if ((rv = getaddrinfo(NULL, port, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
        return 1;
    }
    // loop through all the results and bind to the first we can
    for (p = servinfo; p != NULL; p = p->ai_next) {
        if ((sockfd = socket(p->ai_family, p->ai_socktype,
                             p->ai_protocol)) == -1) {
            perror("server: socket");
            continue;
        }
        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes,
                       sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }
        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            close(sockfd);
            perror("server: bind");
            continue;
        }
        break;
    }
    freeaddrinfo(servinfo); // all done with this structure
    if (p == NULL) {
        fprintf(stderr, "server: failed to bind\n");
        exit(1);
    }
    if (listen(sockfd, 5) == -1) {
        perror("listen");
        exit(1);
    }

    cli_lens[cli_index] = sizeof(client[cli_index]);
    printf("Waiting for connection\n");
    printf("recieved connections from: ");
    fflush(stdout);
    signal(SIGINT, signal_callback_handler);

    while (1) {
        cli_sock[cli_index] = accept(sockfd, (struct sockaddr *) &client[cli_index], &cli_lens[cli_index]);
        if (cli_sock[cli_index] < 0) {
            perror("Error making the client socket\n");
            exit(0);
        }
        printf("<%s>, ", inet_ntoa(client[cli_index].sin_addr));
        fflush(stdout);

        struct socket_struct my_sock;
        my_sock.client_socket = cli_sock[cli_index];
        my_sock.id = cli_index;
        sockets[cli_index] = my_sock;
        pthread_create(&threads[cli_index], NULL, client_thread, &sockets[cli_index]);
        cli_index++;
    }
}
