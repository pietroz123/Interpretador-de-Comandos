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

        // Pega o primeiro argumento (nome do comando)
        arg = strtok(comando, " \n");
        argumentos[0] = arg;

        int i = 1;
        while (arg != NULL) {
            // Separa os próximos argumentos
            arg = strtok(NULL, " \n");
            argumentos[i] = arg;
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
            // Verifica execucao em segundo plano (&)
            if (Resultado != 0) {
                // Verifica redirecao ('<' e '>')
                if (strcmp(argumentos[i-3], ">") == 0) {
                    freopen(argumentos[i-2], "w", stdout);
                } else if (strcmp(argumentos[i-3], "<") == 0) {
                    freopen(argumentos[i-2], "r", stdin);
                }
                argumentos[i-3] = NULL; // Tira '>' e '<' (execvp lê até NULL)
                execvp(argumentos[0], argumentos);
            } else {
                argumentos[i-2] = NULL; // Tira '&'
                execvp(argumentos[0], argumentos);
            }
            printf("Erro ao executar comando!\n");
            exit(EXIT_FAILURE);
        }
    }
}
