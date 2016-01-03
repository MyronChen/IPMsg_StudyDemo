#include "serverstub.h"
#include "util.h"
#include <boost/noncopyable.hpp>
#include "Tools/csocket.h"
#include "Tools/cbinaryprotocol.h"
#include "../AccountService/accountservice.h"
#include "binaryprotocol.h"
#include "chatmanager.h"

#define FROM_UTF8(str) (QString::fromUtf8(str.c_str()))
#define TO_UTF8(str) (str.toUtf8().constData())

USING_NET;
USING_PROTOCOL;


class ServerStubImpl : boost::noncopyable
{
public:
    ServerStubImpl(const QString &sAddr, const QString &sUser = QString());
    void connect(const QString &sAddr);
    void login(const QString &sName, const QString &sPwd, int port);
    void reg(const QString &sName, const QString &sPwd, int port);
    void getOnlineUsers(QMap<QString, QString> &onlineUsers);

public:
    boost::shared_ptr<CSocket> _trans;
    boost::shared_ptr<BinaryProtocol> _prot;
    boost::shared_ptr<AccountClient> _service;
};

ServerStub* ServerStub::_pInstance = NULL;

ServerStub *ServerStub::instance()
{
    if (_pInstance == NULL)
    {
        QMutexLocker zLocker(&gsMutex);
        if (_pInstance == NULL)
            _pInstance = new ServerStub();
    }

    return _pInstance;
}

bool ServerStub::registerUser(const QString &sName, const QString &sPwd, const QString &sAddr)
{
    try
    {
        int port = ChatManagerInstance()->getPort();
        if (port == 0)
            return false;

        ServerStubImpl impl(sAddr);
        impl.reg(sName, sPwd, port);
        _addr = sAddr;
        _user = sName;
        return true;
    }
    catch (CException)
    {
        return false;
    }

}

bool ServerStub::loginUser(const QString &sName, const QString &sPwd, const QString &sAddr)
{
    try
    {
        int port = ChatManagerInstance()->getPort();
        if (port == 0)
            return false;

        ServerStubImpl impl(sAddr);
        impl.login(sName, sPwd, port);
        _addr = sAddr;
        _user = sName;
        return true;
    }
    catch (CException)
    {
        return false;
    }
}

int ServerStub::getOnlineUsers(QMap<QString, QString> &onlineUsers)
{
    try
    {
        ServerStubImpl impl(_addr, _user);
        impl.getOnlineUsers(onlineUsers);
        return 0;
    }
    catch (CException)
    {
        return 1;
    }
}

ServerStub::ServerStub()
{

}

ServerStub::~ServerStub()
{

}


ServerStubImpl::ServerStubImpl(const QString &sAddr, const QString &sUser)
{
    try
    {
        connect(sAddr);
        _prot->setUserName(TO_UTF8(sUser));
    }
    catch (...)
    {
    }
}

void ServerStubImpl::connect(const QString &sAddr)
{
    if (_trans.get() == NULL)
    {
        _trans = boost::make_shared<CSocket>(sAddr);
        _prot = boost::make_shared<BinaryProtocol>(_trans);
        _service = boost::make_shared<AccountClient>(_prot);
        _trans->open();
    }
}

void ServerStubImpl::login(const QString &sName, const QString &sPwd, int port)
{
    _service->login(sName.toUtf8().constData(), sPwd.toUtf8().constData(), port);
    _prot->setUserName(sName.toUtf8().constData());
}

void ServerStubImpl::reg(const QString &sName, const QString &sPwd, int port)
{
    _service->reg(sName.toUtf8().constData(), sPwd.toUtf8().constData(), port);
    _prot->setUserName(sName.toUtf8().constData());
}

void ServerStubImpl::getOnlineUsers(QMap<QString, QString> &onlineUsers)
{
    std::map<std::string, std::string> onlineMap;
    _service->getOnlineUsers(onlineMap);
    for (auto iter = onlineMap.begin(); iter != onlineMap.end(); iter++)
    {
        onlineUsers.insert(FROM_UTF8(iter->first), FROM_UTF8(iter->second));
    }
}
