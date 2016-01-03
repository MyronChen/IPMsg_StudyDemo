#ifndef CHATMANAGER_H
#define CHATMANAGER_H

#include <QString>
#include <boost/shared_ptr.hpp>
#include <QStringList>
#include "udpsocket.h"
#include <QThread>

#define ChatManagerInstance()     ChatManager::instance()

class ChatManager : public QThread
{
    Q_OBJECT

public:
    static ChatManager* instance();
    int getPort() const;

protected:
    ChatManager();
    ~ChatManager();
    static ChatManager *_pInstance;

private:
    UdpSocket _socket;
};



#endif // CHATMANAGER_H
