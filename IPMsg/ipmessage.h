#ifndef IPMESSAGE_H
#define IPMESSAGE_H
#include <QString>
#include <boost/shared_ptr.hpp>
#include <QStringList>

#define IPMsgInstance()     IPMessage::instance()

class IPMessageImpl;

class IPMessage
{
public:
    static IPMessage* instance();

    bool registerUser(const QString &sName, const QString &sPwd, const QString &sAddr);
    bool loginUser(const QString &sName, const QString &sPwd, const QString &sAddr);

    QStringList getOnlineUsers();

protected:
    IPMessage();
    ~IPMessage();
    static IPMessage *_pInstance;

private:
    boost::shared_ptr<IPMessageImpl> _impl;
};

#endif // IPMESSAGE_H
