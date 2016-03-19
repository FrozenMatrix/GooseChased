/*IFNDEF Condition to avoid multiple insertions of the same header file*/

#ifndef BUCKET_H
#define BUCKET_H

/*  Details pertaining to this header file:

    This is the header file containing all the structure
    details and functions related to bucket data structure.
    Every bucket contains a string, a file list and a pointer to the next bucket.
    The next pointer is used in the collision handling in hash tables, where this
    data structure is exclusively used.

*/

/*Standard Library Includes*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Standard Library Includes End*/

/*Custom Headers*/

#include "list.h"

/*Custom Headers End*/



/*--Bucket structure used in the hash tables--*/
typedef struct bucket_t
{
    char* word;
    fList* fileList;
    struct bucket_t* next;
} bucket;

bucket* pointer;
/*--Bucket structure used in the hash tables End--*/

/*------Bucket Structure related functions------------------*/

/*--Function to add word and its related file to the function--*/
/*bucket* addToBucket(bucket* b,char* word, int fid)
{
    if(b == NULL)
    {
        b = (bucket*) malloc(sizeof(bucket));
        b->next = NULL;
        b->word = (char*) malloc(strlen(word)+1);
        strcpy(b->word, word);
        b->fileList= NULL;
        b->fileList = addToFileList(b->fileList, fid);
        return b;
    }
    bucket* t = b;
    if(strcmp(b->word, word) == 0)
    {
            addToFileList(b->fileList, fid);
            return b;
    }
    bucket* p = b;
    while(b!= NULL)
    {
        if(strcmp(b->word, word) == 0){
            addToFileList(b->fileList, fid);
            return b;
        }
        p = b;
        b = b->next;
    }
    p->next = (bucket*) malloc(sizeof(bucket));
    p->next->next = NULL;
    p->next->word = (char*) malloc(strlen(word)+1);
    strcpy(p->next->word, word);
    p->next->fileList = NULL;
    p->next->fileList = addToFileList(p->next->fileList, fid);
    return t;
}*/
bucket* addToBucket(bucket* b,char* word, int fid)
{
    if(b == NULL)
    {
        b = (bucket*) malloc(sizeof(bucket));
        b->next = NULL;
        b->word = (char*) malloc(strlen(word)+1);
        strcpy(b->word, word);
        b->fileList= NULL;
        b->fileList = addToFileList(b->fileList, fid);
        return b;
    }
    bucket* t = b;

    bucket* p = b;
    while(b!= NULL)
    {
        if(strcmp(b->word, word) == 0){
            addToFileList(b->fileList, fid);
            return t;
        }
        p = b;
        b = b->next;
    }
    p->next = (bucket*) malloc(sizeof(bucket));
    p->next->next = NULL;
    p->next->word = (char*) malloc(strlen(word)+1);
    strcpy(p->next->word, word);
    p->next->fileList = NULL;
    p->next->fileList = addToFileList(p->next->fileList, fid);
    return t;
}


/*---------------------------------------------------------*/

/*--Print functions for debug uses--*/

void printBucket(bucket* b, char* files[])
{
    while(b != NULL)
    {
        printf("%s[ ", b->word);
        printFileList(b->fileList, files);
        printf("]\n");
        b = b->next;
    }
}

void printBucketToFile(bucket* b, FILE* out)
{
    while(b != NULL)
    {
        fprintf(out,"%s ", b->word);
        //printFileListToFile(b->fileList, out);
        fprintf(out,"\n");
        b = b->next;
    }
}
/*----------------------------------------------------------*/
/*------Bucket Structure related functions end--------------*/

#endif // BUCKET_H

/*IFNDEF Condition to avoid multiple insertions of the same header file*/
