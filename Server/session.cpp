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

void Session::setCurrentUser(const std::string &user)
{
    _user = user;
}

std::string Session::getCurUser() const
{
    return _user;
}

Session::Session()
{

}
