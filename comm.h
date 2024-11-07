#ifndef COMM_H
#define COMM_H

void send_message(int sensor_id, const char* measure_type, float value);
void receive_message(); // il retourne rien pour le moment

#endif
