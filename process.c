#include "process.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif
#include "comm.h"
#include "comm.c"

#define ECLAIRAGE 1000
#define CHAUFFAGE_MIN 10
#define CHAUFFAGE_MAX 39
#define VENTILATION 100

float ValeurEclairage() {
    return (rand() % ECLAIRAGE);
}

float ValeurChauffage() {
    return (rand() % (CHAUFFAGE_MAX - CHAUFFAGE_MIN)) + CHAUFFAGE_MIN;
}

float ValeurVentilation() {
    return (rand() % VENTILATION);
}

void Eclairage() {
    while (1) {
        float lum = ValeurEclairage();
        envoiMessage(lum);
        printf("Luminosité générée: %f\n", lum);
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
    }
}

void Chauffage() {
    while (1) {
        float temperature = ValeurChauffage();
        envoiMessage(temperature);
        printf("Température générée: %f°C\n", temperature);
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
    }
}

void Ventilation() {
    while (1) {
        float air = ValeurVentilation();
        envoiMessage(air);
        printf("Débit d'air généré: %f\n", air);
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
    }
}

int main() {
    pid_t pid_eclairage, pid_chauffage, pid_ventilation;
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires une seule fois

    pid_eclairage = fork();
    if (pid_eclairage < 0) {
        perror("Erreur de fork pour Eclairage");
        exit(1);
    } else if (pid_eclairage == 0) {
        Eclairage();
        exit(0);
    }

    pid_chauffage = fork();
    if (pid_chauffage < 0) {
        perror("Erreur de fork pour Chauffage");
        exit(1);
    } else if (pid_chauffage == 0) {
        Chauffage();
        exit(0);
    }

    pid_ventilation = fork();
    if (pid_ventilation < 0) {
        perror("Erreur de fork pour Ventilation");
        exit(1);
    } else if (pid_ventilation == 0) {
        Ventilation();
        exit(0);
    }

    // Dans le processus parent, attendre que les enfants se terminent
    for (int i = 0; i < 3; i++) {
        wait(NULL); // Attendre tous les processus enfants
    }

    printf("Tous les processus enfants ont terminé.\n");
    return 0;
}
