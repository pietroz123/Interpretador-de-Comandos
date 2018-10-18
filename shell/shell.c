#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX 256

int main()
{
    char comando[MAX];
    int pid;
    char *argumentos[MAX];

    while (1) {
        printf("> ");
        fgets(comando, MAX, stdin);
        
        char *arg;

        // strcpy(argumentos[0], comando);
        arg = strtok(comando, " ");
        argumentos[0] = arg;

        //printf("'%s'\n", arg);
        //printf("'%s'\n", argumentos[0]);

        int i = 1;
        while (arg != NULL) {
            arg = strtok(NULL, "' ', '\n'");
            // printf("'%s'\n", arg);
            argumentos[i] = arg;
            //printf("'%s'\n", argumentos[i]);
            i++;

        }



        if (!strcmp(comando, "exit")) {
            exit(EXIT_SUCCESS);
        }

        pid = fork();
        if (pid) {
            waitpid(pid, NULL, 0);
        } else {
            execvp(argumentos[0], argumentos);
            printf("Erro ao executar comando!\n");
            exit(EXIT_FAILURE);
        }
    }
}
