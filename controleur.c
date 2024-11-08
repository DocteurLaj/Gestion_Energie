 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "comm.h"
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "comm.h"
#include "comm.c"



int main() {
    // Appel de la fonction pour recevoir un message
    while(1){
    printf("Messgae reçu est le suivant");
    receive_message();
    }
    return 0;
}




