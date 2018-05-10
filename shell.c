#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>


int main (void){
    
    char *input_buf = malloc(300);
    char prompt[] = "./>\0";
	char cwd[1024];

    while(1){
	if (getcwd(cwd, sizeof(cwd)) != NULL){
		printf("%s", cwd);
	}
        printf("%s", prompt);
        input_buf = fgets(input_buf, 299, stdin);
        printf("%s\n", input_buf);
    }
}
