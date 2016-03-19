/*IFNDEF Condition to avoid multiple insertions of the same header file*/

#ifndef ADDFUNC_H
#define ADDFUNC_H

/*----------GLOBAL-VARS-----------------*/

int NumOftxtFiles;
int TotNoOfFiles;

/*----------GLOBAL-VARS-----------------*/

/*----------ADDITIONAL-FUNCTIONS--------*/

/*------------------Trim Word Function-----------------------*/

/*-Function to remove unnecessary characters from the words in the files-*/

void trimWord(char word[])
{
	int i=0;
	int N = strlen(word);
	for(i=0;i<N;++i){
		if(word[i] >=65 && word[i]<=90){
			word[i] = (char)((int)word[i]+32);
		}
		if(word[i] > 122 || word[i] <97){
			word[i] = '\0';
		}
	}
}

/*------------------Trim Word Function End-------------------*/

/*------------------Search Text Function---------------------*/

/*-The main search functionality of the software-*/

void searchText(char word[], hashTable* hTable, char* files[], int noFiles)
{

	int i=0;
	//int got = 0;
    int ind = hashWord(word, hTable->hInd);
    bucket* temp = hTable->table[ind];
    while(temp != NULL)
    {
        if(strcmp(temp->word, word) == 0)
        {
            printf("\n\t\t\t");printf("Search Results : [ ");
            printFileList(temp->fileList, files);
            printf("]\n");
            break;
        }
        temp = temp->next;
    }
    //printf("TEMP : %p", temp);
    if(temp == NULL){
        printf("\n\t\t\t");
        printf("! Word not found in texts !\n");
    }
    int p = 0;
    for(i=0;i<noFiles;i++){
        //printf("searching in %s : word -> %s\n", files[i], word);
        char* r = NULL;
        if((r=strstr(files[i], word)) != NULL){
            if(p == 0){
                printf("\n\t\t\t");printf("Files Found : ");
                p = 1;
            }
            printf("%s ", files[i]);
        }
        //printf("%s\n", r);
    }
    if(p == 0){
        printf("\n\t\t\t");printf("Word not found in any of the filenames\n");
    }
}

/*------------------Search Text Function End-----------------*/

/*------------------getCWD text Files Function---------------*/

/*The main functionality of this function is to get all the text files in the current working directory*/

char** getCWDtxtFiles()
{
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        printf("SHIT");
        return 0;
    }
    DIR* dir;
    if((dir = opendir(cwd)) == NULL)
        return 0;
    struct dirent* ent;
    int count=0;
    while((ent = readdir(dir)) != NULL){
        if(strstr(ent->d_name, ".txt") != NULL)
            ++count;
    }
    NumOftxtFiles = count;
    closedir(dir);
    dir = opendir(cwd);
    char** files = (char**) malloc(sizeof(char*)*count);
    int i=0;
    while((ent = readdir(dir)) != NULL){
        if(strstr(ent->d_name, ".txt") != NULL){
            files[i] = (char*) malloc(strlen(ent->d_name)+1);
            strcpy(files[i], ent->d_name);
            ++i;
        }
    }
    closedir(dir);
    return files;
}

/*--------------getCWD text Files Function End-----------*/

/*--------------getCWD Files Function -------------------*/

/*This function retrieves all the filenames that are in the current working directory of the software to
assist in the filename search functionality of the software*/
char** getCWDFiles()
{
    char cwd[1024];
    if(getcwd(cwd, sizeof(cwd)) == NULL){
        printf("SHIT");
        return 0;
    }
    DIR* dir;
    if((dir = opendir(cwd)) == NULL)
        return 0;
    struct dirent* ent;
    int count=0;
    while((ent = readdir(dir)) != NULL){
        ++count;
    }
    TotNoOfFiles = count;
    closedir(dir);
    dir = opendir(cwd);
    char** files = (char**) malloc(sizeof(char*)*count);
    int i=0;
    while((ent = readdir(dir)) != NULL){
        files[i] = (char*) malloc(strlen(ent->d_name)+1);
        strcpy(files[i], ent->d_name);
        ++i;
    }
    closedir(dir);
    return files;
}
/*--------------getCWD Files Function End----------------*/

/*--Banner print function--*/

void printBannner(float processTime)
{
    system("cls");
    //char ar[] = (char*) malloc(56);
    //printf("\t");printf("   Boot Time: %f\n\n", processTime);
    printf("\t"); printf("                             _____ _\n");
    printf("\t"); printf("  Boot Time: %f       / ____| |\n", processTime);
    printf("\t"); printf("  __ _  ___   ___  ___  ___| |    | |__   __ _ ___  ___\n");
    printf("\t"); printf(" / _` |/ _ \\ / _ \\/ __|/ _ \\ |    | '_ \\ / _` / __|/ _ \\ \n");
    printf("\t"); printf("| (_| | (_) | (_) \\__\\   __/ |____| | | | (_| \\__ \\  __/\n");
    printf("\t"); printf(" \\__, |\\___/ \\___/|___/\\___|\\_____|_| |_|\\__,_|___/\\___|\n");
    printf("\t"); printf("  __/ |\n");
    printf("\t"); printf(" |___/");
    printf("\n");
//    printf("\t"); printf("__________________________________________________________\n\n");
//    printf("\t"); printf("                        Enter the Query                              \n\n\a");
//    printf("\t\t\t\t"); scanf("%s",ar);
//    printf("\t"); printf("__________________________________________________________\n");
}

/*--Banner print function--*/

/*---------ADDITIONAL-FUNCTIONS-END------*/

#endif // ADDFUNC_H

/*IFNDEF Condition to avoid multiple insertions of the same header file*/
