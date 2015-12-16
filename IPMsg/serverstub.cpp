#include "serverstub.h"
#include "util.h"
#include <boost/noncopyable.hpp>
#include "Tools/csocket.h"
#include "Tools/cbinaryprotocol.h"
#include "../AccountService/accountservice.h"

USING_NET;
USING_PROTOCOL;

class ServerStubImpl : boost::noncopyable
{
public:
    ServerStubImpl();
    void connect(const QString &sAddr);
    void login(const QString &sName, const QString &sPwd);

public:
    QString _userName;
    QString _addr;
    QMutex _mutex;
    boost::shared_ptr<CSocket> _trans;
    boost::shared_ptr<CBinaryProtocol> _prot;
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
        _impl->connect(sAddr);
        _impl->login(sName, sPwd);

        return true;
    }
    catch (CException)
    {
        return false;
    }

}

ServerStub::ServerStub() : _impl(new ServerStubImpl())
{

}

ServerStub::~ServerStub()
{

}


ServerStubImpl::ServerStubImpl()
{

}

void ServerStubImpl::connect(const QString &sAddr)
{
    QMutexLocker locker(&_mutex);
    _trans = boost::make_shared<CSocket>(sAddr);
    _prot = boost::make_shared<CBinaryProtocol>(_trans);
    _service = boost::make_shared<AccountClient>(_prot);
    _trans->open();
}

void ServerStubImpl::login(const QString &sName, const QString &sPwd)
{
    QMutexLocker locker(&_mutex);
    _service->login(sName.toUtf8().constData(), sPwd.toUtf8().constData());
}
