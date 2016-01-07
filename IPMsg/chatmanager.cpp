#include "chatmanager.h"
#include "util.h"
#include <boost/noncopyable.hpp>
#include <QMap>
#include "chatmessage.h"
#include "ipmessage.h"

ChatManager* ChatManager::_pInstance = NULL;

ChatManager::ChatManager()
{
    _socket = boost::make_shared<UdpSocket>();
    _prot = boost::make_shared<CBinaryProtocol>(_socket);
    _socket->open();
    QThread::start();
}

ChatManager *ChatManager::instance()
{
    if (_pInstance == NULL)
    {
        QMutexLocker zLocker(&gsMutex);
        if (_pInstance == NULL)
            _pInstance = new ChatManager();
    }

    return _pInstance;
}

int ChatManager::getPort() const
{
    return _socket->getPort();
}

boost::shared_ptr<ChatSession> ChatManager::getChatSession(const QString &peer)
{
    QMutexLocker locker(&_mutex);
    if (_sessions.find(peer) != _sessions.end())
        return _sessions[peer];

    QString peerAddr;
    int port(0);
    if (IPMsgInstance()->getPeerAddr(peer, peerAddr, port) == false)
        return boost::shared_ptr<ChatSession>(nullptr);

    sockaddr_in servAddr;
    bzero(&servAddr, sizeof(servAddr));
    servAddr.sin_family = AF_INET;
    servAddr.sin_port = htons(port);
    if (inet_pton(AF_INET, peerAddr.toLocal8Bit().constData(), &servAddr.sin_addr) == 1)
    {
        sockaddr_storage zPeerAddr;
        memcpy((void*)&zPeerAddr, (void*)(&servAddr), sizeof(servAddr));
        socklen_t len = sizeof(servAddr);

        auto pSession = boost::make_shared<ChatSession>(peer, _socket, zPeerAddr, len);
        _sessions[peer] = pSession;
        return pSession;
    }
    else
    {
        sockaddr_in6 servAddrIn6;
        bzero(&servAddrIn6, sizeof(servAddrIn6));
        servAddrIn6.sin6_family = AF_INET6;
        servAddrIn6.sin6_port = htons(port);
        if (inet_pton(AF_INET6, peerAddr.toLocal8Bit().constData(), &servAddrIn6.sin6_addr) == 1)
        {
            sockaddr_storage zPeerAddr;
            memcpy((void*)&zPeerAddr, (void*)(&servAddrIn6), sizeof(servAddrIn6));
            socklen_t len = sizeof(servAddrIn6);

            auto pSession = boost::make_shared<ChatSession>(peer, _socket, zPeerAddr, len);
            _sessions[peer] = pSession;
            return pSession;
        }
        else
            return boost::shared_ptr<ChatSession>(nullptr);
    }
}

ChatManager::~ChatManager()
{

}

void ChatManager::run()
{
    try
    {
        while (true)
        {
            ChatMessage zMsg;
            sockaddr_storage zAddr;
            socklen_t len = sizeof(zAddr);
            zMsg.recv(_prot.get(), zAddr, len);

            boost::shared_ptr<ChatSession> pSession = getChatSession(zMsg._peer);
            if (pSession)
            {
                pSession->recvMsg(zMsg);
                emit recvMsg(zMsg._peer);
            }
        }
    }
    catch (const CException &cex)
    {
    }
}
