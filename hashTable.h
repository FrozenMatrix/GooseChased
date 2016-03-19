/*IFNDEF Condition to avoid multiple insertions of the same header file*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

/*  Details pertaining to this header file:

    This is the header file contains all the structure
    details and functions related to hash table.
    An array of bucket data structure is used in this to handle collision handling.

*/


/*Standard Library Includes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Standard Library Includes End*/

/*Custom headers*/

#include "bucket.h"

/*Custom headers*/

/*-----------Hash Table Structure Definition--------------*/

typedef struct hashTable_t{
    bucket** table;
    int hInd;
} hashTable;

/*---------Hash Table Structure Definition End----------*/

/*--Function used to create the hash table--*/

hashTable* createHashTable(int size){
    hashTable* h = (hashTable*)malloc(sizeof(hashTable));
    h->hInd = size;
    h->table = (bucket**) malloc(sizeof(bucket*)*size);
    int i=0;
    for(i=0;i<size;++i)
        h->table[i] = NULL;
    return h;
}

/*------------------------------------------*/

/*--Function to hash words--*/

int hashWord(char* str, int num){
    unsigned long hash = 5383;
    int c;
    while ((c = *str++))
        {
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        }
    return hash%num;
}

/*--------------------------*/

/*--Function to add word and file id to the hash table--*/

void addToTable(hashTable* hTable,char* word, int fid){
    int ind = hashWord(word, hTable->hInd);
    hTable->table[ind] = addToBucket(hTable->table[ind], word, fid);
}

/*------------------------------------------------------*/

/*--Function to add word list to hash table--*/
void addToTableFromList(hashTable* hTable, wList* list){
    //FILE* lout = fopen("lout.txt", "a");
    while(list != NULL){
        fList* f = list->fileList;
        while(f!=NULL){
            addToTable(hTable, list->word, f->file);
            f = f->next;
        }
        list = list->next;
    }
    //fclose(lout);
}

/*------------------------------------------*/

/*--Print function for hash table for debug purposes--*/

void printHashTable(hashTable* hTable){
    int i=0;
    for(i=0;i<hTable->hInd;++i){
        printBucket(hTable->table[i], NULL);
//         printf("\n");
    }
}

void printHashTableToFile(hashTable* hTable, FILE* out){
    int i=0;
    for(i=0;i<hTable->hInd;++i){
        printBucketToFile(hTable->table[i], out);
    }
}

/*-----------------------------------------------------*/

/*--Function to count number of empty spaces in the given
 hash table for analysis purposes--*/

int countEmpty(hashTable* hTable){
    int i=0;
    int count = 0;
    for(i=0;i<hTable->hInd;++i){
        if(hTable->table[i] == NULL)
            ++count;
    }
    return count;
}

/*-------------------------------------------------------*/

#endif // HASHTABLE_C

/*IFNDEF Condition to avoid multiple insertions of the same header file*/
