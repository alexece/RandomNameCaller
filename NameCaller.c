#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

#define MS      1000
#define ROUND   30

int main(int argc, char const *argv[2]){

    if(argc != 2){
        perror("Please enter <file> name");
        exit(1);
    }
    
    FILE *p_SrcFile = fopen(argv[1], "r");
    if(p_SrcFile == NULL){
        perror("fopen failed\n");
        exit(1);
    }

    //memory allocation
    char *p_memory = calloc(100,20);
    if(p_memory == NULL){
        perror("memory allocation failed");
        exit(1);
    }
    bzero(p_memory,2000);
    
    char (*names)[20] = (char (*)[20])p_memory;
    
    //read source file character and remove '\n'
    int num = 0;

    while(1){
        
        if(fgets(names[num], 20, p_SrcFile) != NULL){
            
            //both way can delete the '\n'
            //names[num][strlen(names[num])-2] = '\0';
            strtok(names[num],"\n");
            num++;

        }
        else{
 
            if(feof(p_SrcFile)){ 
                break;
            }
            if(ferror(p_SrcFile)){
                perror("name file read error");
                exit(1);
            }

        }

    }

    //set number of people for each group
    int FastSpeed_Group = ROUND * 0.4;
    int MidFastSpeed_Group = ROUND * 0.3 + FastSpeed_Group;
    int MidSlowSpeed_Group = ROUND * 0.2 + MidFastSpeed_Group;
    int SlowSpeed_Group = ROUND;

    //active a random value
    srand(time(NULL));
    int PreValue = 0;
    int CurrentValue = rand()%num;
    
    //start writing each name
    for(int i = 0; i<=ROUND ; i++){

        //clear the print and move cursor at the beginning
        printf("\r");
        for(int k=0;k<20;k++)
            printf(" ");

        while(PreValue == CurrentValue){
            CurrentValue = rand()%num;
        }
        PreValue = CurrentValue;

        if(i <= FastSpeed_Group){
            printf("\r%s", names[CurrentValue]);
            fflush(stdout);
            usleep(100*MS);
        }

        if(i> FastSpeed_Group && i <= MidFastSpeed_Group){
            printf("\r%s", names[CurrentValue]);
            fflush(stdout);
            usleep(200*MS);
        }

        if(i> MidFastSpeed_Group && i <= MidSlowSpeed_Group){
            printf("\r%s", names[CurrentValue]);
            fflush(stdout);
            usleep(300*MS);
        }
        
        if(i > MidSlowSpeed_Group && i <= SlowSpeed_Group){
            printf("\r%s", names[CurrentValue]);
            fflush(stdout);
            usleep(500*MS);
        }

    } 

    printf("\n");
   

    free(p_memory);
    p_memory = NULL;
    fclose(p_SrcFile);

    return 0;
}

