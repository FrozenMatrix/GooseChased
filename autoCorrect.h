#ifndef AUTOCORRECT_H
#define AUTOCORRECT_H

//Header files
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

//Macros
#define MAX_A 20
#define MAX_TREE_DEPTH 40



//Node structure
typedef struct node_t{

    //mistyped word
    char incorrect[MAX_A];

    //corrected spelling
    char correct[MAX_A];

    //pointers for children
    struct node_t *left;
    struct node_t *right;
} node_a;

node_a* bstRoot;


//Structure of array
typedef struct array{
	char incorrect[MAX_A];
	char correct[MAX_A];
}array;


array words[5000];


//Allocate space and populate incorrect for new node_a
node_a *createNode(char incorrect[], char correct[]){


    //local variables
    node_a *newNode;
    newNode = (node_a*) malloc(sizeof(node_a));

    //error handling for allocation of space
    if (newNode == NULL)
    {

        fprintf(stderr, "malloc failedn");
        exit(1);

    }


    //copying the incorrect into the variables
    strcpy(newNode->incorrect,incorrect);
    strcpy(newNode->correct,correct);

    //pointers for children
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;

}



//Inserting node_a into the BST
node_a *insertNode(node_a *root, char incorrect[], char correct[]){


    if(root==NULL){

        root=createNode(incorrect,correct);
        return root;

    }


    if(strcmp(root->incorrect,incorrect)>0){

        root->left = insertNode(root->left, incorrect, correct);

    }

    else{

        root->right = insertNode(root->right, incorrect, correct);

    }


    return root;

}



//Printing the BST
void printBST(node_a* root){

    if(root == NULL)
    return;

    printBST(root->left);

		printf("n%s", root->correct);

		printBST(root->right);

}



//Converts passed string to all small characters
void toLowerString(char string[]){


    //local variables
    int i;

    for(i=0; i<strlen(string); i++){

        string[i]=tolower(string[i]);

    }

}


//Return number of lines in any file
int lineCountFile(char filename[MAX_A]){

	int count=0;
	int ret=0;
	char incorrect[MAX_A], correct[MAX_A];

	FILE *fp;
	fp=fopen(filename,"r");

	if(!fp){
		printf("screwed");
		exit(1);
	}
	else{
		//printf("\nFile found.");
	}

	while(!feof(fp)){
		ret=fscanf(fp,"%s %s",incorrect, correct);
		if(ret==2){
			count++;
			printf("%s %s\n",correct,incorrect);
		}

	}
	fclose(fp);
return count;
}



//Store words from dictionary file to array
void populateArray(){

	//local variables
	int i=0;
	int ret=0;


	//opening the file
	FILE *fp;
	fp=fopen("dictionary.txt","r");


	//error handling for the file
	if(!fp){
		printf("screwed");
		exit(1);
	}
	else{
		//printf("\nFile found.");
	}


	//reading the words linearly into the array from the file
	while(!feof(fp)){
		ret=fscanf(fp,"%s %s",words[i].incorrect,words[i].correct);
		if(ret==2){
		//	printf("%d \n",i);
			i++;
		}
	}


	fclose(fp);
}


//Inorder print of the tree
void iterative_inorder(node_a *root)
{
   node_a *stack[MAX_TREE_DEPTH];
   int top=-1;

   node_a *ptr = root;


 if (ptr == NULL)
    return;

 /* Do while loop */
 do
 {
   while (ptr != NULL)
   {
      stack[++top] = ptr;
      ptr = ptr->left;
   }

   /* Pop a pointer */
   if (top == -1)
     break; // we are done

   ptr = stack[top--];
   printf("%s %s", ptr->correct, ptr->incorrect); // print the node

   ptr = ptr->right;
 } while((ptr != NULL) || (top > -1));

}



//Store dictionary as balanced BST
node_a *BST(node_a *root, int start, int end){


    /* Base Case */
    if (start > end)
      return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    toLowerString(words[mid].incorrect);
    toLowerString(words[mid].correct);
    root=insertNode(root, words[mid].incorrect, words[mid].correct);

    /* Recursively construct the left subtree and make it
       left child of root */
    root->left =  BST(root, start, mid-1);

    /* Recursively construct the right subtree and make it
       right child of root */
    root->right = BST(root, mid+1, end);

    return root;
}



//Corrects the spelling of the passed word
char* autoCorrect(node_a *root, char query[]){


    if(root==NULL){

        return query;

    }


    if(strcmp(query, root->incorrect)>0){

        return autoCorrect(root->right, query);

    }

    else if (strcmp(query, root->incorrect)==0){

        return root->correct;

    }

    else{

        return autoCorrect(root->left, query);

    }

}






//Stores dictionary as BST from file to memory
void storeBST(){

    //local variables
//    int i=0;
	int ret=0;
//	int count=0;
//	float begin;
//	float end;
//  double procTime;
    char incorrect[MAX_A];
    char correct[MAX_A];


    //start time
//    begin = clock();


    //opening the dictionary file
    FILE *fp;
    fp=fopen("dictionary.dict","r");


   	//error handling for the file
		if(!fp){
			printf("screwed");
			exit(1);
		}
		else{
			//printf("\nFile found.");
		}



    while (!feof(fp))
    {

        ret=fscanf(fp,"%s %s",incorrect,correct);

        if(ret == 2){


            toLowerString(incorrect);
            toLowerString(correct);
            bstRoot=insertNode(bstRoot, incorrect, correct);

        }

    }


    fclose(fp);


    //ending time
//    end = clock();


    //total processing time
//    procTime = (double)(end - begin)/CLOCKS_PER_SEC;
//    fprintf("out,\nProcessing time for BST creation : %f s",procTime);


}


//final function
char* getCorrectWord(char query[])
{
	char*temp = autoCorrect(bstRoot, query);
	return temp;
}


#endif
