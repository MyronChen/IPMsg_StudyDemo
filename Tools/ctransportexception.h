#ifndef CTRANSPORTEXCEPTION_H
#define CTRANSPORTEXCEPTION_H
#include <string>

class CTransportException : public std::exception
{
public:
    enum CTransportExceptionType { Unknow, Timeout, NotOpen, BadVer, OverLimit };

    CTransportException();
    CTransportException(CTransportExceptionType type)
        : _type(type){}

    CTransportExceptionType getType() const { return _type; }

private:
    CTransportExceptionType _type;

};

#endif // CTRANSPORTEXCEPTION_H
