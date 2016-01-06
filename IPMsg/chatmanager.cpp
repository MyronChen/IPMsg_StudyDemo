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
    if (_sessions.find(peer) != _sessions.end())
        return _sessions[peer];

    QString peerAddr;
    int port(0);
    if (IPMsgInstance()->getPeerAddr(peer, peerAddr, port) == false)
        return boost::shared_ptr<ChatSession>(nullptr);

    addrinfo hint, *pRes0(NULL), *pRes(NULL);
    char sPort[sizeof("65535")] = {0};
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = PF_UNSPEC;
    hint.ai_socktype = SOCK_DGRAM;
    hint.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    sprintf(sPort, "%d", port);
    int error = getaddrinfo(peerAddr.toLocal8Bit().constData(), sPort, &hint, &pRes0);
    if (error)
    {
        throw CException();
    }

    if (pRes0)
    {
        sockaddr_storage zPeerAddr;
        memcpy((void*)&zPeerAddr, (void*)(pRes0->ai_addr), pRes0->ai_addrlen);
        socklen_t len = pRes0->ai_addrlen;

        auto pSession = boost::make_shared<ChatSession>(peer, _socket, zPeerAddr, len);
        _sessions[peer] = pSession;
        freeaddrinfo(pRes0);
        return pSession;
    }
    freeaddrinfo(pRes0);
    return boost::shared_ptr<ChatSession>(nullptr);
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
            ChatMessage pMsg;
            sockaddr_storage zAddr;
            socklen_t len = sizeof(zAddr);
            pMsg.recv(_prot.get(), zAddr, len);



        }
    }
    catch (const CException &cex)
    {
    }
}
