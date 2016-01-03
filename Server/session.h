#ifndef SESSION_H
#define SESSION_H

#include <string>

class Session
{
public:
    static Session* instance();
    ~Session();

    void setCurrentUser(const std::string &user);
    std::string getCurUser() const;

private:
    Session();

private:
    static Session *_instance;
    std::string _user;

};

#endif // SESSION_H
