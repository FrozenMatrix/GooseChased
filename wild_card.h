
#ifndef WILDCARD_H
#define WILDCARD_H

/* Header files*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*including the list.h file in order to use its function8*/

#include "list.h"


/* Macros*/

#define ALPHABETS 26
#define MAX 40



/*--------------------------------------------------------------
			      STRUCTURE DEFINITIONS INCLUDIND:
							1.  TRIE
							2.  LINKED LIST
-----------------------------------------------------------------*/


/*Defining the trie node
	->array of 26 pointers
	->integer variable of store number of words
*/

typedef struct trie_node{

	int number;
    struct trie_node* children_array[ALPHABETS];

}node;


/*Defining the trei structure*/

typedef struct trie_structure{

	node *root;
    int count;

}trie;


/* structure of the linked list node
	-> array of characters to store string
	-> poiner to the same structure
*/

typedef struct node_s
{
		char str[MAX];
		struct node_s *next;
}node_ll;


/* Global head pointer to the linked list*/

node_ll* head=NULL;


/* function prototypes to:
	1. create node of trie
	2. intializing trie to NULL
	3. inserting a word into the trie
	4. searching and inserting all related words from trie to linked list
	5. searching a word in trie
	6. inserting string in the linked list
	7. for debugging:to find whether a word exists in the trie
	8. for debugging:to print the strings in linked list
	9. to convert the given character into its ASCII value
	10.to convert an integer into corresponding character
	11.for making the list of words to be called in driver program
*/



node *create_node_initialize();

void initialize_trie(trie *trie_st);

void insert_word(trie *trie_st,char word[]);

void trie_store_ll(trie *trie_st, node *root,int j, char string[]);

void search(trie *trie_st, char string[]);

void insert_into_ll(char str[]);

int find_in_trie(trie *trie_st, char key[]);

void print_ll();

int char_to_index(char ch);

char index_to_char(int j);

void makeList(wList* l, char word[]);




/*----------------------------------------------------------------
							LINKED LIST
------------------------------------------------------------------*/


//function to insert string in the linked list

void insert_into_ll(char str[])
{
	if(head==NULL)
	{
		node_ll *new_node=(node_ll*)malloc(sizeof(node_ll));
		if(new_node)
		{

			strcpy(new_node->str,str);
			new_node->next=NULL;
			head=new_node;
		}
	}
	else
	{
		node_ll *new_node=(node_ll*)malloc(sizeof(node_ll));
		if(new_node)
		{

			strcpy(new_node->str,str);
			new_node->next=head;
			head=new_node;
		}
	}
}




/*function to print the contents of the linked list*/

void print_ll()
{
	node_ll* temp=NULL;
	temp=head;
	while(temp)
	{
		//printf("%s \n",temp->str);
		temp=temp->next;
	}

}




/*----------------------------------------------------------------
			        FUNCTIONS FOR OTHER UTILITIES
------------------------------------------------------------------*/



/*function to convert character into its ASCII value*/

int char_to_index(char ch)
{

	int j=ch-'a';
	return j;
}




/*function to convert index into character*/

char index_to_char(int j)
{

	char ch=(char) j;
	return ch;
}




/*-----------------------------------------------------------------
				FUNCTIONS RELATED TO TRIES
------------------------------------------------------------------*/



/*function to create a trie node and initialize it*/

node *create_node_initialize()
{

	int i=0;
	node* new_node;
	new_node=(node*)malloc(sizeof(node));

	if(new_node)
	{
		for(i=0;i<ALPHABETS;i++)
		{
			new_node->number=0;
			new_node->children_array[i]=NULL;

		}
		return new_node;
	}
	return NULL;
}




/*function to intialize the trie structure*/

void initialize_trie(trie *trie_st)
{

	trie_st->root=create_node_initialize();
	trie_st->count=0;

}




/*function for inserting a word in the trie*/

void insert_word(trie *trie_st,char word[])
{


	int len_str=strlen(word); //calculating the string length

	int i=0;
	trie_st->count++;
	int index;

	node* temp=NULL; //putting temp variable as NULL

	/*putting temp variable to the root of trie structure*/

	temp=trie_st->root;


	for(i=0;i<len_str;i++)
	{
		// getting index out of the characters in the string
		index=char_to_index(word[i]);

		if(!temp->children_array[index] )
        {
        	//treversing through the trie while creating new nodes for every character
            temp->children_array[index] = create_node_initialize();
        }


        temp = temp->children_array[index];
	}

	//just keeping the number of word entered in the trie
	temp->number = trie_st->count;
}




/*function to obtain the word from a trie and filling into linked list*/

void trie_store_ll(trie *trie_st, node *root,int j, char string[])
{
	int i;
	int len=strlen(string);

	//allocating in such a manner to get the character array of size+1
	char *value = (char*)malloc(len+1+1);

	strcpy(value,string);

	value[len]=index_to_char(j+97);

	value[len+1]='\0';

	// defining variables and intializing them
	int got=0;

    for(i=0;i<26;i++)

        if( root->children_array[i] != NULL)
		{
			// recursively calling the fuction
            trie_store_ll(trie_st,root->children_array[i],i,value);
            got =1;
//            temp = i;
        }

		if(!got)
		{
			//insering into the linked list
//			printf("%s\n",value);
			insert_into_ll(value);
		}
}





/*function to search all the words starting from the given string by the user*/

void search(trie *trie_st, char string[])
{

    int i=0;
    int index;

    //Creating temp variable
	node*temp=NULL;
	temp=trie_st->root;

	int len = strlen(string);  //getting the lenthg of the string entered


	//dynamically allocation
	char *value=(char*)malloc(len);


	// initializing the character array
	for(i=0;i<len;i++)
	{

		value[i]='\0';
	}

	///filling the entered words in newly allocated array
	for(i=0;i<len-2;i++)
	{
		value[i]=string[i];
	}

	value[len-2]='\0';

	//treversing the trie upto the string-2 length untili.e. one less than the * character
    for(i= 0;i<len-1;i++ )
    {
        index=char_to_index(string[i]);
        temp = temp->children_array[index];
    }

	// calling funtion called  trie_store_ll
	trie_store_ll(trie_st, temp,index, value);
}




/*To find whether the word is in trie*/

int find_in_trie(trie *trie_st, char key[])
{
    int level;
    int length = strlen(key);
    int index;

    //creating a temporary variable and intializing to NULL
    node *temp=NULL;

	//putting temp as root of the trie structure
    temp = trie_st->root;

	//treversing through the trie by getting index out of the character
    for( level = 0; level < length; level++ )
    {
        index = char_to_index(key[level]);

		//stop if whole of the pointer array points to NULL
        if( !temp->children_array[index] )
        {
            return 0;
        }

        temp=temp->children_array[index];
    }

    return (0!=temp && temp->number);
}




/*to copy the words from original linked list to the globally defined linked
list meant for the project*/

char* getNextWord()
{

	if(head == NULL)

    return NULL;

    // allocating memory and copying in the allocated memory

    char* word = (char*) malloc(strlen(head->str)+1);

    strcpy(word, head->str);

    node_ll* temp =  head;
    head = head->next;

    //free the temporary variable
    free(temp);

    //returning the word filled
    return word;
}


/*function to fill the words obtained from the search*/

void makeList(wList* l, char word[])
{
	trie trie_st;

	//intializing the trie

    initialize_trie(&trie_st);

    while(l != NULL)
    {

	    insert_word(&trie_st,l->word);
        l = l->next;
    }

    //search in the trie for the given query

    search(&trie_st, word);

    //creating temp varialble and pointing it to head

    node_ll* temp = head;

    //printf("HEAD : %p\n", head);

    // printing the words stored

    while(temp != NULL)
	{

	    //printf("word : %s\n", temp->str);

		temp = temp->next;
    }
}

#endif
