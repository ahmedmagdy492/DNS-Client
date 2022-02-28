#pragma once

void init(char* ip, int port);
void send_data(char* packet, int len);
void recv_data(char *buffer, int len);
void clean_up();