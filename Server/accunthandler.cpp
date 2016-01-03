#include "accunthandler.h"
#include "serverpri.h"
#include "userlist.h"
#include "session.h"

void AccountHandler::login(const std::string &name, const std::string &pwd, int32_t port)
{
    if (!CDataBase::isPasswordOK(name, pwd))
        throw CException();

    UserListIns()->insertUser(name, pwd, port);
}

void AccountHandler::reg(const std::string &name, const std::string &pwd, int32_t port)
{
    if (CDataBase::isAccountExist(name))
        throw CException();

    CDataBase::createAccount(name, pwd);

    login(name, pwd, port);

    return;
}

void AccountHandler::getOnlineUsers(std::map<std::string, std::string> &onlineMap)
{
    UserListIns()->getUsers(onlineMap);
    onlineMap.erase(Session::instance()->getCurUser());
}
