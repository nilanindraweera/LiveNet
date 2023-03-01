#include "PacketSender.h"
#include "NetException.h"

#include <sys/socket.h>
#include <netinet/in.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

    struct PacketSender::Impl
    {
        Impl(const Socket& sock)
            :m_socket(sock)
        {            
            int opt = 1;
            int addrlen = sizeof(address);
            char buffer[1024] = { 0 };
            const char* hello = "Hello from server";

            // Creating socket file descriptor
            if ((m_server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
            {
                throw NetworkException("socket initialization failed");                
            }

            // Forcefully attaching socket to the port
            if (setsockopt(m_server_socket, SOL_SOCKET,  SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) 
            {
                throw NetworkException("Port binding failed");  
            }

            address.sin_family = AF_INET;
            address.sin_addr.s_addr = INADDR_ANY;
            address.sin_port = htons(m_socket.Port);

            // Forcefully attaching socket to the port 8080
            if (bind(m_server_socket, (struct sockaddr*)&address, sizeof(address))  < 0) 
            {
                throw NetworkException("Binding phrase failed");  
            }
        }

        Socket m_socket;
        struct sockaddr_in address;
        int m_server_socket;
    };
    
    PacketSender::PacketSender(const Socket& socket) 
    :m_impl(std::make_unique<Impl>(socket))
    {
    }

    PacketSender::~PacketSender()
    {
    }
