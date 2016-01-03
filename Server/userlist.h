#ifndef USERLIST_H
#define USERLIST_H
#include <map>
#include <string>

#define UserListIns()     UserList::instance()

class User{
public:
    User() : _port(0) {}
    User(const std::string &name, const std::string &addr, int32_t port);
    std::string getName() const { return _name; }
    std::string getAddr() const { return _addr; }

private:
    std::string _name;
    std::string _addr;
    int32_t _port;
};

class UserList
{
public:
    static UserList* instance();
    ~UserList();

    void insertUser(const std::string &name, const std::string &addr, int32_t port);
    void getUsers(std::map<std::string, std::string> &users) const;

private:
    UserList();

private:
    static UserList *_instance;
    std::map<std::string, User> _users;

};

#endif // USERLIST_H
