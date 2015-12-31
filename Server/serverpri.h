#ifndef SERVERPRI
#define SERVERPRI

#include <mysql/mysql.h>
#include <assert.h>
#include <exception>
#include <string>
#include <iostream>
#include <string.h>

extern MYSQL gsMysql;

class MySQLGuard
{
public:
    MySQLGuard();
    ~MySQLGuard();
};

namespace CDataBase {

extern bool isAccountExist(const std::string &name);
extern bool isPasswordOK(const std::string &name, const std::string &pwd);
extern void createAccount(const std::string &name, const std::string &pwd);

}


#endif // SERVERPRI

