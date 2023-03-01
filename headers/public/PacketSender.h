#pragma once
#include <memory>
#include "DataTypes.h"

class PacketSender
{   
public:
    explicit PacketSender(const Socket& socket);
    ~PacketSender();

    void sendData(const DataPacket& data);
private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};