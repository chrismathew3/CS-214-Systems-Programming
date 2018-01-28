/*
	Creators: Chris Mathew & Jacek Zarski
	Project: Basic Data Sorter
	School: Rutgers University-New Brunswick
	Course: CS 214 Systems Programming
	Professor: Andrew Tjang
*/

#include "sorter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


void Merge(record* L, record* R, record* result, int l, int h, int target_col) {

    int  i = 0, j = 0, k = 0;
    
    while (i < l && j < h) {
        
        if (strcasecmp(L[i].content[target_col], R[j].content[target_col]) < 0) {
            result[k] = L[i];
            i++;
            k++;

        }
        else {
            result[k] = R[j];
            j++;
            k++;
        }
        

    }
    

    while (i < l) {
        result[k] = L[i];
        i++;
        k++;
    }
    while (j < h) {
        result[k] = R[j];
        j++;
        k++;
    }
    
    
}   

void MergeSort(record* arr, int h, int t_col) {
    
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