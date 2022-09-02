#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

const char* server_ip = "192.168.76.128";
const int server_port = 12345;
const int max_buffer = 256;