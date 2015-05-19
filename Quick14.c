#include <stdio.h>
#include <stdlib.h>
#include <string.h>  /* for strlen() */
#include "Stack.h"
#include <limits.h>
#include "getLine.h"
// Print message to stderr and exit.
#define DIE(msg)    exit (fprintf (stderr, "%s\n", msg))
//The split function uses the first element of stack2 as a splitter 
//It puts all lines less than the splitter in stack 1
//All lines greater go in stack3
//the function sorts the number of lines equal to depth in stack2
//The stack1_pos variable keeps track of where the the solved stack is
// if stack1_pos = 1 i push the splitters to stack 1
//if the stack1_pos = -1 i push the splitters to stack 2
Stack split(Stack * stack1,Stack * stack2,Stack * stack3,
            int depth,int pos,int len,int stack1_pos,int flipped){
    char * splitter;
    char * line;
    int nless = 0;
    int ngreater = 0;
    int compare;
    if(depth == 0){
        return NULL;
    }
    if(!popS(stack2, &splitter)){
        DIE("PopS failed to execute");
    }
    if(depth == 1){
        if(stack1_pos == 1){
            if(!pushS(stack1, splitter)){
                DIE("pushS failed to execute");
            }
        }
        else{
            if(!pushS(stack2, splitter)){
                DIE("pushS failed to execute");
            }
        }
        return NULL;
    }
    for (int i = 1; i < depth; i++){
        
        if(!popS(stack2, &line)){
            DIE("popS failed to execute");
        }
        //If the pos is greater than the length of both lines they are equal
        if (pos >= strlen(line) && pos >= strlen(splitter)){
            
            compare = 0;
        }
        //If the pos is greater than only strlen(line) then the splitter is greater
        else if (pos >= strlen(line)){
            compare = -1;
        }
        //If the pos is greater than only strlen(splitter) the line is greater
        else if (pos >= strlen(splitter)){
            compare = 1;
        }
        else {
            compare = (strncmp(&line[pos],&splitter[pos], len));
        }
        if (compare == 0){
            printf("repeates\n\n\n\n\n\n\n\n");
            if (flipped == -1){
                ngreater += 1;
                if(!pushS(stack3,line)){
                    DIE("pushS failed to execute");
                }
            }
            else{
                nless += 1;
                if(!pushS(stack1,line)){
                    DIE("pushS failed to execue");
                }
            }
        }
        else if (compare < 0){
            ngreater += 1;
            pushS(stack3,line);
        }
        else{
            pushS(stack1,line);
            nless += 1;
        }
    }
    split( stack2, stack1, stack3, nless, pos, len, stack1_pos * -1, flipped * -1);
    if(stack1_pos == 1){
        pushS(stack1, splitter);
    }
    else{
        pushS(stack2, splitter);
    }
    
    
    if (stack1_pos == 1){
        split(stack1, stack3, stack2, ngreater, 
              pos, len, stack1_pos, flipped * -1);
    }
    else {
        split(stack2, stack3, stack1, ngreater,
              pos, len, stack1_pos * -1, flipped * -1);
    }
    return NULL;      
} 

void remove_break(char ** s){
    if ((*s)[strlen(*s) - 1] == '\n'){
        (*s)[strlen(*s) - 1] = '\0';
    }
}
    
int main(int argc, char * argv[]){
    Stack stack1;
    Stack stack2;
    Stack stack3;
    createS(&stack1);
    createS(&stack2);
    createS(&stack3);
    int flipped = 1; //equals 1 if lines are in same relative order as in files, -1 if flipped
    int pos = 0;
    int len = INT_MAX;
    int filestart = 1; //variable is incremented if there is a len/pos key
    int nlines = 0; //Number of lines beeing sorted
    char * end;
    if( argc == 1 ){
        exit(1);
    }
    if(argv[1][0] == '-'){
        filestart +=1;
        pos = strtol(&argv[1][1],&end,10);
        
        if(end[0] != ',' && strlen(end) != 0){
            DIE("Invalid input");
        }
        else if (strlen(end) != 0 ){
            len = strtol(&end[1],&end,10);
            printf("%d", len);
        }
        if (strlen(end) != 0){
            DIE("Invalid input");
        }
    }
    char * line;
    FILE * fp;
    for(int m=filestart; m < argc; m++) {
        if(argv[m][0] == '-'){
            fp = stdin;
        }
        else if ((fp = fopen(argv[m],"r")) == NULL){
                DIE("Cannot read file"); 
        }
        while((line = getLine(fp)) != NULL){
            remove_break(&line);
            if(!pushS(&stack1, line)){
                DIE("pushS failed to execute");
            }
            nlines += 1;
        }
        fclose(fp);
    }
    split(&stack2, &stack1, &stack3, nlines, pos, len, -1, flipped * -1);
    while(!isEmptyS(&stack2)){    
        popS(&stack2, &line);
        printf("%s", line);
        free(line); 
        printf("\n");
    }
    while(!isEmptyS(&stack1)){
        popS(&stack1, &line);
        printf("%s", line);
        free(line);
        printf("\n");
    }
    destroyS(&stack1);
    destroyS(&stack2);
    destroyS(&stack3);
    return 1;
}
