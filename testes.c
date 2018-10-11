#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 256

int main() {

    char *comando = (char*) malloc (sizeof(char) * MAX);
    char *argumentos;

    scanf("%[^\n]s", comando);
    printf("comando: %s\n", comando);

    int i = 0;
    argumentos = strtok(comando, " ");
    while (argumentos != NULL) {
        printf("argumento %d: %s\n", i+1, argumentos);
        // strcpy(ARGUMENTOS[i], argumentos);
        argumentos = strtok(NULL, " ");
        i++;
    }

    char *ARGUMENTOS[3];
    ARGUMENTOS[0] = "file1";
    ARGUMENTOS[1] = "file2";
    ARGUMENTOS[2] = NULL;

    // Não há como estipular um número de máximo de argumentos, colocar 256 por exemplo e ler até o NULL


    int j = 0;
    while (ARGUMENTOS[j] != NULL) {
        printf("%s ", ARGUMENTOS[j]);
        j++;
    }


    // printf("saida"); ==== fprintf("saida", stdout);
    // char *str = fgets("entrada", stdin);


}