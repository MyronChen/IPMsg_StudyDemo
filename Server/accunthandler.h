#ifndef ACCUNTHANDLER_H
#define ACCUNTHANDLER_H

#include "../AccountService/accountservice.h"
#include "tools.h"

class AccountHandler : public AccountIf
{
public:
    virtual void login(const std::string &name, const std::string &pwd);
    virtual void reg(const std::string &name, const std::string &pwd);
};

#endif // ACCUNTHANDLER_H
