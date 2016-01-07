#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QString>
#include <boost/shared_ptr.hpp>
#include <QStringList>
#include "udpsocket.h"
#include <QThread>
#include "Tools/cbinaryprotocol.h"
#include "chatsession.h"

USING_PROTOCOL;
#define ChatManagerInstance()     ChatManager::instance()

class ChatManager : public QThread
{
    Q_OBJECT

public:
    static ChatManager* instance();
    int getPort() const;
    boost::shared_ptr<ChatSession> getChatSession(const QString &peer);

signals:
    void recvMsg(QString);

protected:
    ChatManager();
    ~ChatManager();
    static ChatManager *_pInstance;

    virtual void run();

private:
    boost::shared_ptr<UdpSocket> _socket;
    boost::shared_ptr<CBinaryProtocol> _prot;
    std::map<QString, boost::shared_ptr<ChatSession>> _sessions;
    QMutex _mutex;
};



#endif // CHATMANAGER_H
