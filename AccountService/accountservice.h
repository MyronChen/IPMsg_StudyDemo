#ifndef ACCOUNTSERVICE_H
#define ACCOUNTSERVICE_H

#include "Tools/cprotocol.h"

USING_PROTOCOL

class ClientIf
{
public:
    virtual void login(const std::string &name, const std::string &pwd) = 0;
};

class AccountClient : virtual public ClientIf
{
public:
    AccountClient(boost::shared_ptr<CProtocol> prot)
        : _prot(prot)
    {}
    virtual void login(const std::string &name, const std::string &pwd);

    void loginSend(const std::string &name, const std::string &pwd);
    void loginRecv();

protected:
    boost::shared_ptr<CProtocol> _prot;
};

#endif // ACCOUNTSERVICE_H
