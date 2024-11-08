#ifndef COMM_H
#define COMM_H
#define MSG_KEY 1234

void send_message(long sensor_id, const char* measure_type, float value);
void receive_message(); // il retourne rien pour le moment

#endif
