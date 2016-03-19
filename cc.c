//Standard Library headers included

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
//Standard Library headers included

//Custom Headers

#include "hashTable.h"
#include "wild_card.h"
#include "autoCorrect.h"
#include "addFunctions.h"

//Custom Headers


#define max_char 30

/*--Structure for linked list..*/
	typedef struct list_t
	{
		char* sword;
		struct list_t * next;
	}list;
	
	list * headlist=NULL;


/*-----Linked List functions for Stop word elimination---*/

	//Function to add stop words into a linked list
	void insert(char * name)
	{
		list * new_node;
		new_node=malloc(sizeof(list));
		new_node->sword=malloc(sizeof(char)*30);
		new_node->sword=strcpy(new_node->sword,name);
		new_node->next=headlist;
		headlist=new_node;
		return;
	}

	//Function to generate read words from stopwords text file

	void compile_list()
		{
		int num;char sword[max];
		FILE* fp=fopen("stopwords.txt","r");
		while(!feof(fp))
			{
			 fscanf(fp,"%s",sword);
			 insert(sword);
			}
		fclose(fp);
		}
	
/*-----Main function to integrate all the modules-----*/

int main()
{
    //Performance Calculation Variables
    clock_t begin, end;
    double processTime;
    /////////////////////////

    hashTable* hTable = NULL;
    wList* wordList = NULL;

	int i=0;
    char** fileNames = getCWDtxtFiles();
    FILE* file[NumOftxtFiles];

	for(i=0;i<NumOftxtFiles;++i)
    {
        file[i] = fopen(fileNames[i], "r");
    }

	FILE* out = fopen("output.txt", "a");
    char lol[50] = {'\0'};
    int status=0;
    begin = clock();

	for(i=0;i<NumOftxtFiles;++i)
    {
        while(!feof(file[i]))
        {
            fscanf(file[i], "%s", lol);
            trimWord(lol);
	    status=0;
 //Search for a stop word before adding to list
  	     if(lol[0] != '\0')
	         { 
		tempor=headlist;      
	        while(tempor!=NULL)
			{ 
		 	if(strcmp(lol,tempor->sword)==0)
		 		{
		 		stat=1;
				break;}
		 	else
		 		{
		 		tempor=tempor->next;
		 		}
			}
//No stop word, so adding to list		
		if(stat==0)
		{	
	wordList = addWordToList(wordList, lol, i+1);}
	}}
    }
	storeBST();
	//Performance Calculation--
    end  = clock();
    processTime = (double)(end-begin)/CLOCKS_PER_SEC;
    //Performance Calculation--

	int numWords = countWords(wordList);
    hTable = createHashTable(numWords);
    addToTableFromList(hTable, wordList);

    //printHashTable(hTable);
    //printHashTableToFile(hTable, out);
    fclose(out);
	fclose(out);

	for(i=0;i<2;++i)
    {
        fclose(file[i]);
    }

	FILE* record = fopen("record.txt", "a");
    int emptyCount = countEmpty(hTable);
	//fprintf(record, "WordCount : %d Empty : %d ProcessTime : %f s\n", numWords, emptyCount, processTime);

	fclose(record);

    printf("\nNo in list = %d %d", countWords(wordList), numWords);
    int c = 0;
    for(i=0;i<numWords;i++){
        bucket* b = hTable->table[i];
        while(b != NULL){
            ++c;
            b = b->next;
        }
    }
    printf("\nNo of words in htable = %d\n", c);

	//Driver Loop
	char ans = 'y';
    while(ans == 'y'){
        printf("Enter the search phrase : ");
        scanf("%s", lol);
        printf("LOL : %d %c", strlen(lol)-1, lol[strlen(lol)-1]);
        printBannner();
        printf("\n\t"); printf("__________________________________________________________\n\n");
        printf("\t"); printf("                        Enter the Query                              \n\n");
        printf("\t\t\t\t"); scanf("%s",lol);
        printf("\t"); printf("__________________________________________________________\n");
        if(lol[strlen(lol)-1] == '*'){
            makeList(wordList, lol);
            char* word = NULL;
            while((word = getNextWord())!= NULL){
                printf("%s : \n", word);
                searchText(word, hTable, fileNames, NumOftxtFiles);
            }
        }
        else{
            trimWord(lol);
        	char* word = getCorrectWord(lol);
        	if(strcmp(word, lol) != 0)
        	{
				printf("\t\t\t\t");printf("Corrected Word : %s\n", word);
            	searchText(word, hTable, fileNames, NumOftxtFiles);
            	printf("\t\t\t\t");printf("Do you want to search for original word? y/n : ");
				char a = 'y';
				while(getchar() != '\n');
				scanf("%c", &a);
				if(a == 'y')
					searchText(lol, hTable, fileNames, NumOftxtFiles);
        	}
        	else
        		searchText(lol, hTable, fileNames, NumOftxtFiles);
        }
        printf("\n\n\t\t\t");printf("Search Again? y/n : ");
        while(getchar() != '\n');
        scanf("%c", &ans);
    }

    return 0;
}

/*-----End of Main function-----*/
