#pragma once

#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

///@brief creates the socket connexion with the server
///
///@return the file descriptor of the socket connexion
int SocketConnexion(int port);

