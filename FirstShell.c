//
//  MyShell.c
//  
//
//  Created by Dave on 14/11/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 500


char *read_line (char *buf, size_t sz) {
  
    if (fgets(buf, sz, stdin) == NULL){
        return NULL;
    }
    
    //clear any extra characters that remain after the buf is filled
    if (strlen(buf) >= sz - 1){
    while (getchar()!= '\n' ){
        getchar();
    }}
    
    if(buf[strlen(buf)-1] == '\n') {
        buf[strlen(buf)-1] = '\0';
    }

    return buf;
}



void splitt(char* buf, char* split[], size_t max) {
    
    char * p;
    int i = 0;
    p = strtok (buf, " ");
    
    while (p != NULL)
    {
        split[i] = p;
        i++;
        p = strtok (NULL, " ");
    }
    
    //clear remining pointers in split buffer by setting them to null
    for (int k = i; k < max; k++ ) {
    split[k] = NULL;
    }
}


int execution(char** split)
{

    pid_t pid = fork();
  
   if (pid == 0) {
       
        execvp(split[0], split);
       perror("ERROR!!");
        exit(0);
    }

    else {
        wait(NULL);
        return 1;
    }
}

int main()
{
    char buf[500];
    char* split[MAX+1];
    //get corrrect size of buffer buf
    size_t sz = sizeof(buf)/sizeof(buf[0]);
   
    printf("press ctrl + D to exit \n");
    
    while(1) {
        
        printf(">> ");
        
        if (read_line(buf, sz) != NULL){
            
             splitt(buf, split, MAX);
            execution(split);
        } else {printf("exiting shell...\n"); break;}
        
    }
    return 0;
}





