/*
    Creators: Chris Mathew & Jacek Zarski
    Project: Basic Data Sorter
    School: Rutgers University-New Brunswick
    Course: CS 214 Systems Programming
    Professor: Andrew Tjang
*/

#include "server.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void Merge(record* L, record* R, record* result, int l, int h, char *sortColumn) {

    if(strcmp(sortColumn, "color") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].color, R[j].color) < 0) {
                strcpy(result[k].color , L[i].color);
                i++;
                k++;
            }
            else {
                strcpy(result[k].color , R[j].color);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].color, L[i].color);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].color, R[j].color);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "director_name")==0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].director_name, R[j].director_name) < 0) {
                strcpy(result[k].director_name , L[i].director_name);
                i++;
                k++;
            }
            else {
                strcpy(result[k].director_name , R[j].director_name);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].director_name , L[i].director_name);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].director_name , R[j].director_name);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "num_critic_for_reviews") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].num_critic_for_reviews < R[j].num_critic_for_reviews) {
                result[k].num_critic_for_reviews = L[i].num_critic_for_reviews;
                i++;
                k++;
            }
            else {
                result[k].num_critic_for_reviews = R[j].num_critic_for_reviews;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].num_critic_for_reviews = L[i].num_critic_for_reviews;
            i++;
            k++;
        }
        while (j < h) {
            result[k].num_critic_for_reviews = R[j].num_critic_for_reviews;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "duration") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].duration < R[j].duration) {
                result[k].duration = L[i].duration;
                i++;
                k++;
            }
            else {
                result[k].duration = R[j].duration;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].duration = L[i].duration;
            i++;
            k++;
        }
        while (j < h) {
            result[k].duration = R[j].duration;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "director_facebook_likes") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].director_facebook_likes < R[j].director_facebook_likes) {
                result[k].director_facebook_likes = L[i].director_facebook_likes;
                i++;
                k++;
            }
            else {
                result[k].director_facebook_likes = R[j].director_facebook_likes;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].director_facebook_likes = L[i].director_facebook_likes;
            i++;
            k++;
        }
        while (j < h) {
            result[k].director_facebook_likes = R[j].director_facebook_likes;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "actor_3_facebook_likes") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].actor_3_facebook_likes < R[j].actor_3_facebook_likes) {
                result[k].actor_3_facebook_likes = L[i].actor_3_facebook_likes;
                i++;
                k++;
            }
            else {
                result[k].actor_3_facebook_likes = R[j].actor_3_facebook_likes;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].actor_3_facebook_likes = L[i].actor_3_facebook_likes;
            i++;
            k++;
        }
        while (j < h) {
            result[k].actor_3_facebook_likes = R[j].actor_3_facebook_likes;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "actor_2_name") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].actor_2_name, R[j].actor_2_name) < 0) {
                strcpy(result[k].actor_2_name , L[i].actor_2_name);
                i++;
                k++;
            }
            else {
                strcpy(result[k].actor_2_name , R[j].actor_2_name);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].actor_2_name , L[i].actor_2_name);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].actor_2_name , R[j].actor_2_name);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "actor_1_facebook_likes") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].actor_1_facebook_likes < R[j].actor_1_facebook_likes) {
                result[k].actor_1_facebook_likes = L[i].actor_1_facebook_likes;
                i++;
                k++;
            }
            else {
                result[k].actor_1_facebook_likes = R[j].actor_1_facebook_likes;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].actor_1_facebook_likes = L[i].actor_1_facebook_likes;
            i++;
            k++;
        }
        while (j < h) {
            result[k].actor_1_facebook_likes = R[j].actor_1_facebook_likes;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "gross") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].gross < R[j].gross) {
                result[k].gross = L[i].gross;
                i++;
                k++;
            }
            else {
                result[k].gross = R[j].gross;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].gross = L[i].gross;
            i++;
            k++;
        }
        while (j < h) {
            result[k].gross = R[j].gross;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "genres") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].genres, R[j].genres) < 0) {
                strcpy(result[k].genres , L[i].genres);
                i++;
                k++;
            }
            else {
                strcpy(result[k].genres , R[j].genres);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].genres , L[i].genres);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].genres , R[j].genres);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "actor_1_name") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].actor_1_name, R[j].actor_1_name) < 0) {
                strcpy(result[k].actor_1_name , L[i].actor_1_name);
                i++;
                k++;
            }
            else {
                strcpy(result[k].actor_1_name , R[j].actor_1_name);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].actor_1_name , L[i].actor_1_name);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].actor_1_name , R[j].actor_1_name);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "movie_title") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].movie_title, R[j].movie_title) < 0) {
                strcpy(result[k].movie_title , L[i].movie_title);
                i++;
                k++;
            }
            else {
                strcpy(result[k].movie_title , R[j].movie_title);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].movie_title , L[i].movie_title);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].movie_title , R[j].movie_title);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "num_voted_users") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].num_voted_users < R[j].num_voted_users) {
                result[k].num_voted_users = L[i].num_voted_users;
                i++;
                k++;
            }
            else {
                result[k].num_voted_users = R[j].num_voted_users;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].num_voted_users = L[i].num_voted_users;
            i++;
            k++;
        }
        while (j < h) {
            result[k].num_voted_users = R[j].num_voted_users;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "cast_total_facebook_likes") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].cast_total_facebook_likes < R[j].cast_total_facebook_likes) {
                result[k].cast_total_facebook_likes = L[i].cast_total_facebook_likes;
                i++;
                k++;
            }
            else {
                result[k].cast_total_facebook_likes = R[j].cast_total_facebook_likes;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].cast_total_facebook_likes = L[i].cast_total_facebook_likes;
            i++;
            k++;
        }
        while (j < h) {
            result[k].cast_total_facebook_likes = R[j].cast_total_facebook_likes;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "actor_3_name") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].actor_3_name, R[j].actor_3_name) < 0) {
                strcpy(result[k].actor_3_name , L[j].actor_3_name);
                i++;
                k++;
            }
            else {
                strcpy(result[k].actor_3_name , R[j].actor_3_name);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].actor_3_name , L[j].actor_3_name);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].actor_3_name , R[j].actor_3_name);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "facenumber_in_poster") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].facenumber_in_poster < R[j].facenumber_in_poster) {
                result[k].facenumber_in_poster = L[i].facenumber_in_poster;
                i++;
                k++;
            }
            else {
                result[k].facenumber_in_poster = R[j].facenumber_in_poster;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].facenumber_in_poster = L[i].facenumber_in_poster;
            i++;
            k++;
        }
        while (j < h) {
            result[k].facenumber_in_poster = R[j].facenumber_in_poster;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "plot_keywords") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].plot_keywords, R[j].plot_keywords) < 0) {
                strcpy(result[k].plot_keywords , L[j].plot_keywords);
                i++;
                k++;
            }
            else {
                strcpy(result[k].plot_keywords , R[j].plot_keywords);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].plot_keywords , L[j].plot_keywords);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].plot_keywords , R[j].plot_keywords);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "movie_imdb_link") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].movie_imdb_link, R[j].movie_imdb_link) < 0) {
                strcpy(result[k].movie_imdb_link , L[i].movie_imdb_link);
                i++;
                k++;
            }
            else {
                strcpy(result[k].movie_imdb_link , R[j].movie_imdb_link);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].movie_imdb_link , L[i].movie_imdb_link);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].movie_imdb_link , R[j].movie_imdb_link);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "num_user_for_reviews") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].num_user_for_reviews < R[j].num_user_for_reviews) {
                result[k].num_user_for_reviews = L[i].num_user_for_reviews;
                i++;
                k++;
            }
            else {
                result[k].num_user_for_reviews = R[j].num_user_for_reviews;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].num_user_for_reviews = L[i].num_user_for_reviews;
            i++;
            k++;
        }
        while (j < h) {
            result[k].num_user_for_reviews = R[j].num_user_for_reviews;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "language") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].language, R[j].language) < 0) {
                strcpy(result[k].language , L[i].language);
                i++;
                k++;
            }
            else {
                strcpy(result[k].language , R[j].language);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].language , L[i].language);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].language , R[j].language);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "country") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].country, R[j].country) < 0) {
                strcpy(result[k].country , L[i].country);
                i++;
                k++;
            }
            else {
                strcpy(result[k].country , R[j].country);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].country , L[i].country);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].country , R[j].country);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "content_rating") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (strcasecmp(L[i].content_rating, R[j].content_rating) < 0) {
                strcpy(result[k].content_rating , L[i].content_rating);
                i++;
                k++;
            }
            else {
                strcpy(result[k].content_rating , R[j].content_rating);
                j++;
                k++;
            }
        }

        while (i < l) {
            strcpy(result[k].content_rating , L[i].content_rating);
            i++;
            k++;
        }
        while (j < h) {
            strcpy(result[k].content_rating , R[j].content_rating);
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "budget") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].budget < R[j].budget) {
                result[k].budget = L[i].budget;
                i++;
                k++;
            }
            else {
                result[k].budget = R[j].budget;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].budget = L[i].budget;
            i++;
            k++;
        }
        while (j < h) {
            result[k].budget = R[j].budget;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "title_year") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].title_year < R[j].title_year) {
                result[k].title_year = L[i].title_year;
                i++;
                k++;
            }
            else {
                result[k].title_year = R[j].title_year;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].title_year = L[i].title_year;
            i++;
            k++;
        }
        while (j < h) {
            result[k].title_year = R[j].title_year;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "actor_2_facebook_likes") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].actor_2_facebook_likes < R[j].actor_2_facebook_likes) {
                result[k].actor_2_facebook_likes = L[i].actor_2_facebook_likes;
                i++;
                k++;
            }
            else {
                result[k].actor_2_facebook_likes = R[j].actor_2_facebook_likes;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].actor_2_facebook_likes = L[i].actor_2_facebook_likes;
            i++;
            k++;
        }
        while (j < h) {
            result[k].actor_2_facebook_likes = R[j].actor_2_facebook_likes;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "imdb_score") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (adjust_num(L[i].imdb_score) < adjust_num(R[j].imdb_score)) {
                result[k].imdb_score = L[i].imdb_score;
                i++;
                k++;
            }
            else {
                result[k].imdb_score = R[j].imdb_score;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].imdb_score = L[i].imdb_score;
            i++;
            k++;
        }
        while (j < h) {
            result[k].imdb_score = R[j].imdb_score;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "aspect_ratio") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (adjust_num(L[i].aspect_ratio) < adjust_num(R[j].aspect_ratio)) {
                result[k].aspect_ratio = L[i].aspect_ratio;
                i++;
                k++;
            }
            else {
                result[k].aspect_ratio = R[j].aspect_ratio;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].aspect_ratio = L[i].aspect_ratio;
            i++;
            k++;
        }
        while (j < h) {
            result[k].aspect_ratio = R[j].aspect_ratio;
            j++;
            k++;
        }
        return;
    }
    else if(strcmp(sortColumn, "movie_facebook_likes") == 0) {
        int  i = 0, j = 0, k = 0;

        while (i < l && j < h) {
            if (L[i].movie_facebook_likes < R[j].movie_facebook_likes) {
                result[k].movie_facebook_likes = L[i].movie_facebook_likes;
                i++;
                k++;
            }
            else {
                result[k].movie_facebook_likes = R[j].movie_facebook_likes;
                j++;
                k++;
            }
        }

        while (i < l) {
            result[k].movie_facebook_likes = L[i].movie_facebook_likes;
            i++;
            k++;
        }
        while (j < h) {
            result[k].movie_facebook_likes = R[j].movie_facebook_likes;
            j++;
            k++;
        }
        return;
    }
    else{
        printf("WRONG INPUT_ABORT\n");
        return;
    }
}

void MergeSort(record* arr, int h, char *t_col) {

    if (h < 2) return;
    int m = h/2;

    record* L = (record*)malloc(m * sizeof(record));
    record* R = (record*)malloc((h-m) * sizeof(record));

    int a;
    for(a = 0; a < m; a++){
        L[a] = arr[a];
    }
    int i;
    for(i = m; i < h; i++){
        R[i - m] = arr[i];
    }


    MergeSort(L, m, t_col);

    MergeSort(R, h-m, t_col);

    Merge(L, R, arr, m, h - m,t_col);

    free(L);
    free(R);

    return;
}

int adjust_num(double num) {
    double low_bound = 1e7;
    double high_bound = low_bound*10;
    double adjusted = num;
    int is_negative = (num < 0);
    if(num == 0) {
        return 0;
    }
    if(is_negative) {
        adjusted *= -1;
    }
    while(adjusted < low_bound) {
        adjusted *= 10;
    }
    while(adjusted >= high_bound) {
        adjusted /= 10;
    }
    if(is_negative) {
        adjusted *= -1;
    }
    //define int round(double) to be a function which rounds
    //correctly for your domain application.
    //Round function did not work on the iLab skipped function.
    return adjusted;
}
