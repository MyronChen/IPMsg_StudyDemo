#include "userlist.h"

UserList* UserList::_instance = NULL;

UserList *UserList::instance()
{
    if (_instance == NULL)
        _instance = new UserList();

    return _instance;
}

UserList::~UserList()
{

}

void UserList::insertUser(const std::string &name, const std::string &addr)
{
    _users[name] = User(name, addr);
}

UserList::UserList()
{

}


User::User(const std::string &name, const std::string &addr) : _name(name), _addr(addr)
{

}
