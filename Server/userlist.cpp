#include "userlist.h"
#include "tools.h"

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

void UserList::insertUser(const std::string &name, const std::string &addr, int32_t port)
{
    _users[name] = User(name, addr, port);
}

void UserList::getUsers(std::map<std::string, std::string> &users) const
{
    for (auto iter = _users.begin(); iter != _users.end(); iter++)
    {
        users[iter->first] = iter->second.getAddr();
    }
}

int32_t UserList::getPort(const std::string &name)
{
    auto iter = _users.find(name);
    if (iter == _users.end())
        throw CException();
    else
        return iter->second.getPort();
}

UserList::UserList()
{

}


User::User(const std::string &name, const std::string &addr, int32_t port)
    : _name(name), _addr(addr), _port(port)
{

}
