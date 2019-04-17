#include <stdio.h>
#include <stdlib.h>

int main()
{
printf("Type 'HELP' to view all commands\n");
while(1){
    printf("Enter a command:\n");
    char str[64];
    scanf("%[^\n]%*c", str);

    char *pointer = strtok(str, " ");
    char *splitarr[64];

    int i = 0;
    while(pointer != NULL){
        splitarr[i++] = pointer;
        pointer = strtok(NULL, " ");
    }
    splitarr[i] = "@"; //to mark the end of the command after split
    i = 1; //arr[0] has function, we are only concerned with the parameters i.e arr[1] onwards
    if(strcmp(splitarr[0],"ADD")==0 || strcmp(splitarr[0],"add")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter atleast two numbers\n");
        }
        else{
            int sum = 0;
            while(strcmp(splitarr[i], "@")!=0){
                char *ptr;
                int num = strtol(splitarr[i++], &ptr, 10);
                sum += num;
            }
            printf("The sum is: %d\n", sum);
        }
    }
    else if(strcmp(splitarr[0],"SUB")==0 || strcmp(splitarr[0],"sub")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter atleast two numbers\n");
        }
        else{
            char *ptr;
            int result = strtol(splitarr[i++], &ptr, 10);
            while(strcmp(splitarr[i], "@")!=0){
                int num = strtol(splitarr[i++], &ptr, 10);
                result -= num;
            }
            printf("The result is: %d\n", result);
        }
    }
    else if(strcmp(splitarr[0],"MUL")==0 || strcmp(splitarr[0],"mul")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter atleast two numbers\n");
        }
        else{
            char *ptr;
            int result = strtol(splitarr[i++], &ptr, 10);
            while(strcmp(splitarr[i], "@")!=0){
                int num = strtol(splitarr[i++], &ptr, 10);
                result *= num;
            }
            printf("The result is: %d\n", result);
        }
    }
    else if(strcmp(splitarr[0],"DIV")==0 || strcmp(splitarr[0],"div")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter atleast two numbers\n");
        }
        else{
            char *ptr;
            int result = strtol(splitarr[i++], &ptr, 10);
            while(strcmp(splitarr[i], "@")!=0){
                int num = strtol(splitarr[i++], &ptr, 10);
                result /= num;
            }
            printf("The result is: %d\n", result);
        }
    }
    else if(strcmp(splitarr[0],"RUN")==0 || strcmp(splitarr[0],"run")==0){
        if(strcmp(splitarr[2],"@")==0){
            //char *cmd = malloc(5+strlen(splitarr[1]+4)); giving errors when running two processes at once, removed.
            char cmd[5+strlen(splitarr[1])+4];
            strcpy(cmd, "start ");
            strcat(cmd, splitarr[1]);
            strcat(cmd, ".exe");
            system(cmd);
        }
        else{
            printf("Only one parameter allowed\n");
        }
    }
    else if(strcmp(splitarr[0],"HELP")==0 || strcmp(splitarr[0],"help")==0){
        printf("RUN PROCESS\nSyntax: 'run filename'\nExamples: 'run chrome', 'run winword', 'run mspaint', 'run notepad'\n");
        printf("ADDITION\nSyntax: 'add num1 num2 num3...'\nExamples: 'add 10 20 30', 'add 50 23 34 50'\n");
        printf("SUBTRACTION\nSyntax: 'sub num1 num2 num3...'\nExamples: 'sub 10 20 30', 'sub 50 23 34 50'\n");
        printf("MULTIPLICATION\nSyntax: 'mul num1 num2 num3...'\nExamples: 'mul 10 20 30', 'mul 50 23 34 50'\n");
        printf("DIVISION\nSyntax: 'div num1 num2 num3...'\nExamples: 'div 10 20 30', 'div 50 23 34 50'\n");
        printf("EXIT\nSyntax: 'exit'\n");
    }
    else if(strcmp(splitarr[0],"EXIT")==0 || strcmp(splitarr[0],"exit")==0){
        exit(0);
    }
    else{
        printf("Invalid command, type 'HELP' to check command usage\n");
    }
}
    return 0;
}
