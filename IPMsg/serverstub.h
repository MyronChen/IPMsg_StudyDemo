#ifndef SERVERSTUB_H
#define SERVERSTUB_H

#include "Tools/tools.h"
#include <QString>
#include <boost/shared_ptr.hpp>
#include <QMap>

#define StubInstance()     ServerStub::instance()

class ServerStubImpl;

class ServerStub
{
public:
    static ServerStub* instance();

    bool registerUser(const QString &sName, const QString &sPwd, const QString &sAddr);
    bool loginUser(const QString &sName, const QString &sPwd, const QString &sAddr);
    int getOnlineUsers(QMap<QString, QString> &onlineUsers);
    bool getPeerAddr(const QString &sPeerName, QString &peerAddr, int &port);

protected:
    ServerStub();
    ~ServerStub();
    static ServerStub *_pInstance;

private:
    QString _addr;
    QString _user;
};




#endif // SERVERSTUB_H
