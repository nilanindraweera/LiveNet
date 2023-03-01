#pragma once
#include <exception>

class NetworkException : public std::exception
{
    public:
        NetworkException(const std::string& msg)
            :m_msg(msg)
        {        
        }
        std::string GetMessage() const{
            return m_msg;
        }
    private:
        std::string m_msg;
};