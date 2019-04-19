#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

int main()
{
    PROCESS_INFORMATION pi[10];
    char names[10][10];
    char status[10][10];
    double start[10];
    double end[10];
    int index = 0;
    //removing garbage values from end time array
    for(index = 0; index<10; index++){
        end[index] = 0;
    }
    index = 0;
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
            printf("Enter at least two numbers\n");
        }
        else{
            double sum = 0;
            while(strcmp(splitarr[i], "@")!=0){
                char *ptr;
                double num = strtod(splitarr[i++], &ptr);
                sum += num;
            }
            printf("The sum is: %f\n", sum);
        }
    }
    else if(strcmp(splitarr[0],"SUB")==0 || strcmp(splitarr[0],"sub")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter at least two numbers\n");
        }
        else{
            char *ptr;
            double result = strtod(splitarr[i++], &ptr);
            while(strcmp(splitarr[i], "@")!=0){
                double num = strtod(splitarr[i++], &ptr);
                result -= num;
            }
            printf("The result is: %f\n", result);
        }
    }
    else if(strcmp(splitarr[0],"MUL")==0 || strcmp(splitarr[0],"mul")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter at least two numbers\n");
        }
        else{
            char *ptr;
            double result = strtod(splitarr[i++], &ptr);
            while(strcmp(splitarr[i], "@")!=0){
                double num = strtod(splitarr[i++], &ptr);
                result *= num;
            }
            printf("The result is: %f\n", result);
        }
    }
    else if(strcmp(splitarr[0],"DIV")==0 || strcmp(splitarr[0],"div")==0){
        if(strcmp(splitarr[2],"@")==0){
            printf("Enter at least two numbers\n");
        }
        else{
            char *ptr;
            double result = strtod(splitarr[i++], &ptr);
            while(strcmp(splitarr[i], "@")!=0){
                double num = strtod(splitarr[i++], &ptr);
                result /= num;
            }
            printf("The result is: %f\n", result);
        }
    }
    else if(strcmp(splitarr[0],"RUN")==0 || strcmp(splitarr[0],"run")==0){
        if(strcmp(splitarr[2],"@")==0){
            /*//char *cmd = malloc(5+strlen(splitarr[1]+4)); giving errors when running two processes at once, removed.
            char cmd[5+strlen(splitarr[1])+4];
            strcpy(cmd, "start ");
            strcat(cmd, splitarr[1]);
            strcat(cmd, ".exe");
            system(cmd);*/
            STARTUPINFO structSTART;
            PROCESS_INFORMATION structINFO;
            ZeroMemory(&structSTART, sizeof(structSTART));
            char cmd[strlen(splitarr[1])+4];
            strcpy(cmd, splitarr[1]);
            strcat(cmd, ".exe");
            structSTART.cb = sizeof(STARTUPINFO);
            if(CreateProcess(NULL,cmd,NULL,NULL,TRUE,0,NULL,NULL,&structSTART,&structINFO)){
                pi[index] = structINFO;
                strcpy(names[index], splitarr[1]);
                strcpy(status[index], "ACTIVE");
                start[index] = (double) clock()/CLOCKS_PER_SEC;
                index++;
                printf("New process created with PID %u\n", structINFO.dwProcessId);
            }
            else{
                printf("Error\n");
            }
        }
        else{
            printf("Only one parameter allowed\n");
        }
    }
    else if(strcmp(splitarr[0],"LIST")==0 || strcmp(splitarr[0],"list")==0){
            if(strcmp(splitarr[1],"@")!=0){
                printf("Invalid command. Check help for syntax\n");
                continue;
            }
            int j = 0;
            printf("Name\t,\tPID\t,\tPStatus\t,\tStart-Time\t,\tEnd-time\n");
            for(j = 0; j<index; j++){
                printf("%s\t,\t", names[j]);
                printf("%u\t,\t", pi[j].dwProcessId);
                printf("%s\t,\t", status[j]);
                printf("%f\t,\t", start[j]);
                printf("%f\t\n", end[j]);
            }
        }
    else if(strcmp(splitarr[0],"KILL")==0 || strcmp(splitarr[0],"kill")==0){
        if(strcmp(splitarr[2],"@")==0){
            int j = 0; int result = -1; char *ptr;
            if(atoi(splitarr[1])!=0){
                for(j=0; j<index; j++){
                    if(strtol(splitarr[1], &ptr, 10)==(int)pi[j].dwProcessId){
                        if(strcmp(status[j], "INACTIVE")!=0){
                            result = j;
                            break;
                        }
                        else{
                            result = -2;
                        }
                    }
                }
            }
            else{
                for(j=0; j<index; j++){
                    if(strcmp(splitarr[1],names[j])==0){
                        if(strcmp(status[j], "INACTIVE")!=0){
                            result = j;
                            break;
                        }
                        else{
                            result = -2;
                        }
                    }
                }
            }
            if(result == -1){
                printf("Error, type help to see syntax\n");
                continue;
            }
            if(result==-2){
                printf("Process already inactive\n");
                continue;
            }
            TerminateProcess(pi[result].hProcess, 0);
            strcpy(status[result], "INACTIVE");
            end[result] = (double)clock()/CLOCKS_PER_SEC;
        }
        else{
            printf("Only one parameter allowed\n");
        }
    }
    else if(strcmp(splitarr[0],"HELP")==0 || strcmp(splitarr[0],"help")==0){
        printf("RUN PROCESS\nSyntax: 'run filename'\nExamples: 'run calc', 'run mspaint', 'run notepad'\nFull path is possible like C:\\Windows\\system32\\notepad (double slashes and only system32 folder and dont write .exe)\n");
        printf("ADDITION\nSyntax: 'add num1 num2 num3...'\nExamples: 'add 10 20 30', 'add 50 23 34 50'\n");
        printf("SUBTRACTION\nSyntax: 'sub num1 num2 num3...'\nExamples: 'sub 10 20 30', 'sub 50 23 34 50'\n");
        printf("MULTIPLICATION\nSyntax: 'mul num1 num2 num3...'\nExamples: 'mul 10 20 30', 'mul 50 23 34 50'\n");
        printf("DIVISION\nSyntax: 'div num1 num2 num3...'\nExamples: 'div 10 20 30', 'div 50 23 34 50'\n");
        printf("KILL PROCESS\nSyntax: 'kill pid' or 'kill processname'\nExamples: 'kill 224', 'kill notepad'\nKilling using process name kills the one at the top if duplicates exist\n");
        printf("LIST\nLists all processes created\nSyntax: 'list'\n");
        printf("EXIT\nSyntax: 'exit'\n");
    }
    else if(strcmp(splitarr[0],"EXIT")==0 || strcmp(splitarr[0],"exit")==0){
        if(strcmp(splitarr[1],"@")!=0){
                printf("Invalid command. Check help for syntax\n");
                continue;
        }
        exit(0);
    }
    else{
        printf("Invalid command, type 'HELP' to check command usage\n");
    }
}
    return 0;
}
