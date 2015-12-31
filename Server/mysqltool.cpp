#include "serverpri.h"
#include <QString>

using namespace CDataBase;

MYSQL gsMysql;

MySQLGuard::MySQLGuard()
{
    mysql_init(&gsMysql);

    MYSQL *pConnDB = mysql_real_connect(&gsMysql, "localhost", "root", "a", "IPMsg", 3306, NULL, 0);
    assert(pConnDB);

    const char *pQuery = "CREATE TABLE IF NOT EXISTS Account (name VARCHAR(255), password VARCHAR(255))";
    if (mysql_real_query(&gsMysql, pQuery, strlen(pQuery)))
    {
        throw std::exception();
    }
}

MySQLGuard::~MySQLGuard()
{
    mysql_close(&gsMysql);
}


bool CDataBase::isAccountExist(const std::string &name)
{
    QString selQuery = QString("SELECT * FROM Account WHERE name='%1'").arg(name.c_str());
    if (mysql_real_query(&gsMysql, selQuery.toLatin1().constData(), selQuery.toLatin1().size()) )
    {
        throw std::exception();
    }

    bool bExist(false);
    MYSQL_RES *pRes = mysql_store_result(&gsMysql);
    if (pRes)
    {
        if (pRes->row_count > 0)
            bExist = true;

        mysql_free_result(pRes);
    }

    return bExist;
}

bool CDataBase::isPasswordOK(const std::string &name, const std::string &pwd)
{
    QString selQuery = QString("SELECT * FROM Account WHERE name='%1' AND password='%2'")
                               .arg(name.c_str(), pwd.c_str());
    if (mysql_real_query(&gsMysql, selQuery.toLatin1().constData(), selQuery.toLatin1().size()) )
    {
        throw std::exception();
    }

    bool bExist(false);
    MYSQL_RES *pRes = mysql_store_result(&gsMysql);
    if (pRes)
    {
        if (pRes->row_count > 0)
            bExist = true;

        mysql_free_result(pRes);
    }

    return bExist;
}

void CDataBase::createAccount(const std::string &name, const std::string &pwd)
{
    QString sInsertQuery = QString("insert into Account values('%1', '%2')").arg(name.c_str(), pwd.c_str());
    if (mysql_real_query(&gsMysql, sInsertQuery.toLatin1().constData(), sInsertQuery.toLatin1().size()))
    {
        throw std::exception();
    }
}
