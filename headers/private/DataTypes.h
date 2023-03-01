#pragma once

struct Socket
{
    unsigned int Address[4];
    unsigned int Port;
};

struct DataPacket
{
    char* data = nullptr;
    unsigned int size = 0;
};
