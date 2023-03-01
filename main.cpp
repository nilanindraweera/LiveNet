#include <iostream>

#include "PacketSender.h"

int main()
{
    std::cout << "initializing LiveNET....." << std::endl;

    Socket socket{{192,168,3,100}, 5555};
    PacketSender pSender{socket};


    std::cin;
    return 0;
}