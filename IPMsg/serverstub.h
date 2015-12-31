#ifndef SERVERSTUB_H
#define SERVERSTUB_H

#include "Tools/tools.h"
#include <QString>
#include <boost/shared_ptr.hpp>

#define StubInstance()     ServerStub::instance()

class ServerStubImpl;

class ServerStub
{
public:
    static ServerStub* instance();

    bool registerUser(const QString &sName, const QString &sPwd, const QString &sAddr);
    bool loginUser(const QString &sName, const QString &sPwd, const QString &sAddr);

protected:
    ServerStub();
    ~ServerStub();
    static ServerStub *_pInstance;

private:
    boost::shared_ptr<ServerStubImpl> _impl;
};




#endif // SERVERSTUB_H
