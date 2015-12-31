#include "accunthandler.h"
#include "serverpri.h"
#include "userlist.h"


void AccountHandler::login(const std::string &name, const std::string &pwd)
{
    if (!CDataBase::isPasswordOK(name, pwd))
        throw CException();

    UserListIns()->insertUser(name, pwd);
}

void AccountHandler::reg(const std::string &name, const std::string &pwd)
{
    if (CDataBase::isAccountExist(name))
        throw CException();

    CDataBase::createAccount(name, pwd);

    login(name, pwd);

    return;
}
