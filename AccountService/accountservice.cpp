#include "accountservice.h"

struct LoginArgs
{
    uint32_t write(boost::shared_ptr<CProtocol> prot);

    std::string name;
    std::string pwd;
};

uint32_t LoginArgs::write(boost::shared_ptr<CProtocol> prot)
{
    COutRecursionTraker tracker(*prot);
    uint32_t ifer = prot->writeStructBegin("LoginArgs");

    ifer += prot->writeFieldBegin("name", C_STRING, 1);
    ifer += prot->writeString(name);
    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldBegin("pwd", C_STRING, 2);
    ifer += prot->writeString(pwd);
    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldStop();
    ifer += prot->writeStructEnd();

    return ifer;
}

void AccountClient::login(const std::string &name, const std::string &pwd)
{
    loginSend(name, pwd);
    loginRecv();
}

void AccountClient::loginSend(const std::string &name, const std::string &pwd)
{
    _prot->writeMessageBegin("login", C_Call, 0);
    LoginArgs arg;
    arg.name = name;
    arg.pwd = pwd;
    arg.write(_prot);
    _prot->writeMessageEnd();
    _prot->getTransport()->writeEnd();
    _prot->getTransport()->flush();
}

void AccountClient::loginRecv()
{

}


