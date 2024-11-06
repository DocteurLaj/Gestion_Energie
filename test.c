#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    // Première création d'un processus enfant
    pid_t pid1 = fork();
    
    if(pid1 == -1){
        printf("Erreur dans le processus");
    }

    if (pid1 == 0) {
        // Code pour le premier enfant
        printf("Premier enfant, PID = %d\n", getpid());
    } else {
        // Deuxième création d'un processus enfant
        pid_t pid2 = fork();
        
        if(pid2 == -1){
        printf("Erreur dans le processus");}

        if (pid2 == 0) {
            // Code pour le deuxième enfant
            printf("Deuxième enfant, PID = %d\n", getpid());
        } else {
            // Troisième création d'un processus enfant
            pid_t pid3 = fork();

            if(pid3 == -1){
            printf("Erreur dans le processus");}

            if (pid3 == 0) {
                // Code pour le troisième enfant
                printf("Troisième enfant, PID = %d\n", getpid());
            } else {
                // Code pour le processus parent
                printf("Processus parent, PID = %d\n", getpid());
            }
        }
    }

    return 0;
}
