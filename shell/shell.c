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

        arg = strtok(comando, " \n");
        argumentos[0] = arg;

        //printf("'%s'\n", arg);
        // printf("'%s'\n", argumentos[0]);

        int i = 1;
        while (arg != NULL) {
            arg = strtok(NULL, " \n");
            argumentos[i] = arg;
            //printf("'%s'\n", arg);
            // printf("'%s'\n", argumentos[i]);
            i++;

        }

        if (!strcmp(comando, "exit")) {
            exit(EXIT_SUCCESS);
        }

        // Verifica se o último comando é '&' 
        int Resultado = strcmp(argumentos[i-2], "&");
        

        pid = fork();
        if (pid) {
            // Processo pai
           if (Resultado != 0)
                waitpid(pid, NULL, 0);
        } else {
            if (Resultado != 0){
                execvp(argumentos[0], argumentos);
            } else {
                argumentos[i-2] = NULL; // Tira o '&'
                execvp(argumentos[0], argumentos);
            }
            printf("Erro ao executar comando!\n");
            exit(EXIT_FAILURE);
        }
    }
}
