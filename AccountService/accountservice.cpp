#include "accountservice.h"

struct LoginArgs
{
    uint32_t write(boost::shared_ptr<CProtocol> prot);

    std::string name;
    std::string pwd;
};

uint32_t LoginArgs::write(boost::shared_ptr<CProtocol> prot)
{
    uint32_t ifer(0);
    COutRecursionTraker tracker(*prot);
    ifer = prot->write


    prot->writeString(name);
    prot->writeString(pwd);
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


