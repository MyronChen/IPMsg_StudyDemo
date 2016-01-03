#ifndef ACCUNTHANDLER_H
#define ACCUNTHANDLER_H

#include "../AccountService/accountservice.h"
#include "tools.h"

class AccountHandler : public AccountIf
{
public:
    virtual void login(const std::string &name, const std::string &pwd, int32_t port);
    virtual void reg(const std::string &name, const std::string &pwd, int32_t port);
    virtual void getOnlineUsers(std::map<std::string, std::string> &onlineMap);
};

#endif // ACCUNTHANDLER_H
