#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define INPUT_BUFFER_SIZE 300
#define MAX_PATH_LENGTH 1024
#define MAX_ARGUMENTS 10

int argc = 0;
char *argv[MAX_ARGUMENTS];


void parseInput(char *input_buf){

    const char *delimit = " ";
    char *token;
	argc = 0;
	
	token = strtok(input_buf, delimit);
	
	while (token != NULL){
		//Check for null input		
		if (input_buf[0] == 10) return;
		argv[argc] = token;
		token = strtok(NULL, delimit);
		argc++;
    }
	//replace the final \r with null
	argv[argc-1][strlen(argv[argc-1])-1] = '\0';
}

void changeDir(void) {
	if (argc == 2){
		//chdir returns 0 upon successful completion
		if (chdir(argv[1]) == 0){
			return;
		} else {
			printf("Failed. Try again, please.\n");
		}			
	} else {
		printf("Invalid number of arguments.\n");
	}
}

void runProg(void){
	//todo
	return;
}

void runCommand(void){ 
	// first field of argv holds command
	if (strcmp(argv[0], "cd") == 0){
		changeDir();
	} else if (strcmp(argv[0], "wait") == 0){
		//to do: implement wait
		/*for (int i = 1; i < argc; i++){
			waitpid(atoi(argv[i]));
		}*/
	} else if (strcmp(argv[0], "prog") == 0){
		//to do: implement prog function and call it here		
		runProg();
	} else {		
		printf("Please enter a valid command.\n");
	}
}


int main (void){
    char *input_buf = malloc(INPUT_BUFFER_SIZE);
    char prompt[] = "/>\0";
	char cwd[MAX_PATH_LENGTH];

    while(1){
		if (getcwd(cwd, sizeof(cwd)) != NULL){
			printf("%s", cwd);
		}
        printf("%s", prompt);
        input_buf = fgets(input_buf, 299, stdin);
       
        parseInput(input_buf);
		//exit
		if(strcmp(argv[0], "exit") == 0) return 0;

		runCommand();		
    }
	
}
