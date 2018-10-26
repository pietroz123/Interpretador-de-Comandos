#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
 
#define MAX 256
 
int main() {
 
    char comando[MAX];
    int pid;
   
    int i = 0;
    char *arg;
    char *args[MAX];
 
    while (1) {
 
        printf("> ");
        gets(comando);
 
        //comando inicial é separado
        arg = strtok(comando, " \n ");
        args[0] = arg;
   
        //caso seja exit...
        if (!strcmp(comando, "exit")) {
          exit(EXIT_SUCCESS);
        }
 
        //separa os argumentos remanescentes caso eles existam
        for (i = 1; (arg = strtok(NULL, " \n")) != NULL; i++){
 
            args[i] = arg;
               
        }
 
        //e coloca o delimitador final caso ele só possua um argumento, caso ele possua mais seu delimitador vai ser separado mais a frente
        args[i] = NULL;    
 
        pid = fork();

        if (pid) {  //processo pai
 
            //caso o último argumento seja "&" devemos executar o processo concorrentemente, portanto não devemos esperar pelo PID do próximo processo
            if (strcmp(args[i - 1], "&"))
 
                waitpid(pid, NULL, 0);
 

        } else {
 
            //caso o penúltimo argumentoo não seja NULL, ou seja caso exista mais de de 2 argumentos
            if(args[i - 2] != NULL){
           
                //se ele for ">" redirecionamos a saída para o arquivo referenciado no último argumento (args [i - 1])
                if (!strcmp(args[i - 2], ">")){
 
                    freopen (args[i - 1], "w" , stdout);
                    args[i - 2] = NULL;
 
                }  
 
                //se ele for "<" redirecionamos a entrada do arquivo referenciado no último argumento (args [i - 1])
                else if (!strcmp(args[i - 2], "<")){
 
                    freopen (args[i - 1], "r" , stdin);
                    args[i - 2] = NULL;
 
                }

                //ao mesmo tempo, mudamos o delimitador final do vetor de argumentos (args[i - 2] = NULL)
            }
 
            //caso o último argumento seja "&", mudamos o delimitador final do vetor de argumentos 
            if (!strcmp(args[i - 1], "&"))
       
                args[i - 1] = NULL;
 
            execvp(args[0], args);
            printf("Erro ao executar comando!\n");
            exit(EXIT_FAILURE);
           
        }
   
    }
 
}
