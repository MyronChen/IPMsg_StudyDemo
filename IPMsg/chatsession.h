#ifndef CHATSESSION_H
#define CHATSESSION_H

#include <QString>
#include "udpsocket.h"

USING_NET;

class ChatSession
{
public:
    ChatSession(const QString &peer, boost::shared_ptr<UdpSocket> socket, const sockaddr_storage &zPeerAddr, socklen_t &len);
    void sendText(const QString &text);

private:
    QString _peer;
    boost::shared_ptr<UdpSocket> _socket;
    sockaddr_storage _peerAddr;
    socklen_t _peerAddrLen;
};

#endif // CHATSESSION_H
