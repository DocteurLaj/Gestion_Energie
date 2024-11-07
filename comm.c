#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "comm.h"
#include <time.h>


// Définition des types de message pour chaque sous-système
#define MSG_TYPE_ECLAIRAGE 1   // Type de message pour l'éclairage
#define MSG_TYPE_CHAUFFAGE 2   // Type de message pour le chauffage
#define MSG_TYPE_VENTILATION 3  // Type de message pour la ventilation

// Structure de message pour la communication
struct message {
    long msg_type;
    int sensor_id;
    char measure_type[20];
    float value;
    char timestamp[20];
};


// Identifiant de la file de messages
int msg_id;


// Fonction pour envoyer un message à la file // communication IPC
void send_message(int sensor_id, const char* measure_type, float value) {
    int msg_id;
    struct message msg;
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Format de l'horodatage (année-mois-jour heure:minute)
    strftime(msg.timestamp, sizeof(msg.timestamp), "%Y-%m-%d %H:%M", t);

    // Obtenir ou créer la file de messages
    msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("Erreur de création de la file de messages");
        exit(1);
    }

    // Remplir les champs du message
    msg.msg_type = 1; // Type de message
    msg.sensor_id = sensor_id;
    strncpy(msg.measure_type, measure_type, sizeof(msg.measure_type) - 1);
    msg.value = value;

    // Envoyer le message
    if (msgsnd(msg_id, &msg, sizeof(msg) - sizeof(long), 0) == -1) {
        perror("Erreur d'envoi du message");
        exit(1);
    }

    printf("Message envoyé : Capteur %d | Type : %s | Valeur : %.2f | Horodatage : %s\n",
           msg.sensor_id, msg.measure_type, msg.value, msg.timestamp);
}


// Fonction pour recevoir un message de la file
void receive_message() {
    int msg_id;
    struct message msg;

    // Accéder à la file de messages
    msg_id = msgget(MSG_KEY, 0666 | IPC_CREAT);
    if (msg_id == -1) {
        perror("Erreur d'accès à la file de messages");
        exit(1);
    }

    // Recevoir le message
    if (msgrcv(msg_id, &msg, sizeof(msg) - sizeof(long), 1, 0) == -1) {
        perror("Erreur de réception du message");
        exit(1);
    }

    printf("Message reçu : Capteur %d | Type : %s | Valeur : %.2f | Horodatage : %s\n",
           msg.sensor_id, msg.measure_type, msg.value, msg.timestamp);
}
