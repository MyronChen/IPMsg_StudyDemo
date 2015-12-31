#ifndef CAPPEXCEPTION_H
#define CAPPEXCEPTION_H

#include "cprotocol.h"

USING_PROTOCOL

ENTER_NET
{

class CAppException : public CException
{
public:
    enum _ExceptionType {C_Unknow};
    CAppException();
    uint32_t write(CProtocol *prot);
    uint32_t read(CProtocol *prot);

private:
    _ExceptionType _type;
};


}LEAVE_NET
#endif // CAPPEXCEPTION_H
