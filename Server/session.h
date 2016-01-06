#ifndef SESSION_H
#define SESSION_H

#include <string>

class Session
{
public:
    static Session* instance();
    ~Session();

    void setCurrentUser(const std::string &user, const std::string &addr);
    std::string getCurUser() const;
    std::string getAddr() const;

private:
    Session();

private:
    static Session *_instance;
    std::string _user;
    std::string _addr;

};

#endif // SESSION_H
