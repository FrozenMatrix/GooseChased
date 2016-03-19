/*IFNDEF Condition to avoid multiple insertions of the same header file*/

#ifndef LIST_H
#define LIST_H

/*  Details pertaining to this header file:

    This is the header file contains all the structure
    details and functions related to linked list.
    This header is used in bucket structure used to construct the hash tables

*/

/*--Standard Library Includes--*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*--Standard Library Includes--*/

/*---------Linked list Structure Definition------------------*/
// List made for files ids;
typedef  struct fList_t
{
    int file;
    struct fList_t* next;
} fList;

//List made for words
typedef struct wList_t
{
    char* word;
    fList* fileList;
    struct wList_t* next;
} wList;

/*---------Linked list Structure Definition End--------------*/

/*--Function to add file id to given file id list*/

fList* addToFileList(fList* f, int fid)
{
    //This code segment is executed if file list does not exist.
    if(f == NULL)
    {
        f = (fList*) malloc(sizeof(fList));
        f->file = fid;
        f->next = NULL;
        return f;
    }
    //Storing the head of the linked list
    fList* L = f;

    while(f->next != NULL)
    {
        f = f->next;
    }
    f->next = (fList*) malloc(sizeof(fList));
    f->next->file = fid;
    f->next->next = NULL;
    return L;
}

/*--------------------------------------------------*/

/*--Function to add word and its file id to the word list--*/

wList* addWordToList(wList* first, char word[], int fid)
{
    wList* temp;
    temp = first;

    //This is used when an empty list is sent to the function
    if(first == NULL)
    {
        //Allocating space for the node
        first = (wList*) malloc(sizeof(wList));
        //Allocating space to copy the word.
        //Here space is allocated dynamically so as not to waste space.
        first->word = (char*) malloc(sizeof(strlen(word)+1));
        strcpy(first->word, word);
        first->next = NULL;
        first->fileList = (fList*) malloc(sizeof(fList));
        first->fileList->file = fid;
        first->fileList->next = NULL;
        return first;
    }

    // The is executed when the list already exists

    while(first != NULL)
    {
        // If the word already exists, then add the file id to its corresponding list

        if(strcmp(first->word, word) == 0)
        {
            first->fileList->next = (fList*) malloc(sizeof(fList));
            first->fileList->next->file = fid;
            first->fileList->next->next = NULL;
            return temp;
        }
        first = first->next;
    }

    /*This code segment is executed when the given word does not
        exist in the list and has to be added to it*/

    //Resetting first to point to the start of the list
    first = temp;

    while(first->next != NULL)
    {
        first = first->next;
    }

    //Allocating memory to create a node
    first->next = (wList*) malloc(sizeof(wList));
    //Allocating space to copy the word.
    //Here space is allocated dynamically so as not to waste space.
    first->next->word = (char*) malloc(strlen(word)+1);
    strcpy(first->next->word, word);
    first->next->next = NULL;
    first->next->fileList = (fList*) malloc(sizeof(fList));
    first->next->fileList->file = fid;
    first->next->fileList->next = NULL;
    return temp;
}

/*--------------------------------------------------------*/

/*--Print function for linked lists used for debug purposes--*/

void printFileList(fList* l, char* files[])
{
    if(files != NULL)
        while(l != NULL)
        {
            printf("%s ", files[l->file-1]);
            l = l->next;
        }
    while(l != NULL)
    {
        printf("%d ", l->file);
        l = l->next;
    }
}

void printFileListToFile(fList* l, FILE* out)
{
    while(l != NULL)
    {
        fprintf(out,"%d ", l->file);
        l = l->next;
    }
}

void printWordList(wList* l, char* files[])
{
    while(l != NULL)
    {
        printf("%s[ ", l->word);
        printFileList(l->fileList, files);
        printf("]\n");
        l = l->next;
    }
}

void printWordListToFile(wList* l, FILE* file)
{
    while(l != NULL)
    {
        fprintf(file, "%s\n", l->word);
        l = l->next;
    }
}

/*-----------------------------------------------*/

/*--Function to count number of words in a given list--*/
int countWords(wList* list)
{
    int num =0;
    while(list != NULL)
    {
        list = list->next;
        ++num;
    }
    return num;
}

/*-------------------------------------------------*/

#endif // LIST_H
