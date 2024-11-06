#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "comm.h"

// Définition des types de message pour chaque sous-système
#define MSG_TYPE_ECLAIRAGE 1   // Type de message pour l'éclairage
#define MSG_TYPE_CHAUFFAGE 2   // Type de message pour le chauffage
#define MSG_TYPE_VENTILATION 3  // Type de message pour la ventilation

// Structure de message pour la communication
struct message {
    long mtype; // Type de message (utilisé pour identifier le type de données)
    float data; // Donnée à envoyer (valeur flottante)
};

// Identifiant de la file de messages
int msgid;

// Fonction d'initialisation de la communication IPC
void initIPC() {
    // Générer une clé unique pour la file de messages
    key_t key = ftok("progfile", 65);
    // Créer ou obtenir l'identifiant de la file de messages
    msgid = msgget(key, 0666 | IPC_CREAT);
}

// Fonction pour envoyer un message à la file
void envoiMessage(float val) {
    struct message msg; // Créer une instance de la structure de message
    msg.mtype = MSG_TYPE_ECLAIRAGE; // Assigner le type de message (éclairage ici)
    msg.data = val; // Assigner la donnée à envoyer
    // Envoyer le message à la file de messages
    msgsnd(msgid, &msg, sizeof(msg.data), 0);
}

// Fonction pour recevoir un message de la file
float receptionMessage(int type) {
    struct message msg; // Créer une instance de la structure de message
    // Essayer de recevoir un message du type spécifié
    if (msgrcv(msgid, &msg, sizeof(msg.data), type, IPC_NOWAIT) != -1) {
        return msg.data; // Retourner la donnée reçue si un message a été reçu
    }
    return -1; // Retourner -1 si aucun message n'a été reçu
}
