#include "ipmessage.h"
#include "util.h"
#include <boost/noncopyable.hpp>
#include <QMap>

class IPMessageImpl : boost::noncopyable
{
public:
    IPMessageImpl() {}
    void refreshOnlineUsers();


    QString _userName;
    QString _addr;
    QMap<QString, QString> _onlineUsers;
};

IPMessage* IPMessage::_pInstance = NULL;

IPMessage *IPMessage::instance()
{
    if (_pInstance == NULL)
    {
        QMutexLocker zLocker(&gsMutex);
        if (_pInstance == NULL)
            _pInstance = new IPMessage();
    }

    return _pInstance;
}

bool IPMessage::registerUser(const QString &sName, const QString &sPwd, const QString &sAddr)
{
    bool bRslt = StubInstance()->registerUser(sName, sPwd, sAddr);
    if (bRslt)
    {
        _impl->_userName = sName;
        _impl->_addr = sAddr;
    }
    return bRslt;
}

bool IPMessage::loginUser(const QString &sName, const QString &sPwd, const QString &sAddr)
{
    bool bRslt = StubInstance()->loginUser(sName, sPwd, sAddr);
    if (bRslt)
    {
        _impl->_userName = sName;
        _impl->_addr = sAddr;
    }
    return bRslt;
}

QStringList IPMessage::getOnlineUsers()
{
    _impl->refreshOnlineUsers();

    QStringList asUser;
    for (auto iter = _impl->_onlineUsers.begin(); iter != _impl->_onlineUsers.end(); iter++)
    {
        asUser.append(iter.key());
    }

    return asUser;
}

IPMessage::IPMessage() : _impl(new IPMessageImpl())
{
}

IPMessage::~IPMessage()
{

}


void IPMessageImpl::refreshOnlineUsers()
{
    _onlineUsers.clear();
    StubInstance()->getOnlineUsers(_onlineUsers);
}
