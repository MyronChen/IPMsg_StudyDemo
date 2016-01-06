#include "session.h"

Session* Session::_instance = NULL;

Session *Session::instance()
{
    if (_instance == NULL)
        _instance = new Session();

    return _instance;
}

Session::~Session()
{

}

void Session::setCurrentUser(const std::string &user, const std::string &addr)
{
    _user = user;
    _addr = addr;
}

std::string Session::getCurUser() const
{
    return _user;
}

std::string Session::getAddr() const
{
    return _addr;
}

Session::Session()
{

}
