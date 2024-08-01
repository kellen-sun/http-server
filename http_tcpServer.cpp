#include "http_tcpServer.h"
#include <iostream>
#include <sstream>
#include <unistd.h>

void log(const std::string &messgae) {
    std::cout << message << std::endl;
}

void exitError(const std::string &message) {
    log("ERROR: " + message);
    std::cout << WSAGetLastError() << std::endl;
    exit(1);
}

namespace http {
    TcpServer::TcpServer(std::string ipAddress, int port) : 
        m_ip_address(ip_address), m_port(port), m_socket(), m_new_socket(),
        m_incomingMessage(), m_socketAddress(), 
        m_socketAddress_len(sizeof(m_socketAddress)), 
        m_serverMessage(buildResponse())
    {
        startServer();
    }

    TcpServer::~TcpServer() {
        closeServer();
    }

    int TcpServer::startServer() {
        if (WSAStartup(MAKEWORD(2, 0), &m_wsaData) != 0) {
            exitError("WSAStartup failed!");
        }

        m_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (m_socket < 0) {
            exitError("Cannot create socket!");
            return 1;
        }
        return 0;
    }

    void TcpServer::closeServer() {
        closesocket(m_socket);
        closesocket(m_new_socket);
        exit(0);
    }
}