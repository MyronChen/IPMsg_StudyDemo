#include "chatsession.h"
#include "util.h"
#include "chatmessage.h"
#include "Tools/cbinaryprotocol.h"
#include "ipmessage.h"

USING_PROTOCOL;

ChatSession::ChatSession(const QString &peer, boost::shared_ptr<UdpSocket> socket, const sockaddr_storage &zPeerAddr, socklen_t &len)
    :_peer(peer), _socket(socket), _peerAddr(zPeerAddr), _peerAddrLen(len)
{

}

void ChatSession::sendText(const QString &text)
{
    ChatMessage zMsg;
    zMsg._type = ChatMessage::Text;
    zMsg._text = text;
    zMsg._peer = IPMsgInstance()->getCurUser();

    CBinaryProtocol zProt(_socket);
    zMsg.send(&zProt, (sockaddr*)&_peerAddr, _peerAddrLen);
}

void ChatSession::recvMsg(const ChatMessage &msg)
{
    QMutexLocker locker(&_mutex);
    _unreadMsg.enqueue(msg);
}

bool ChatSession::deQueueUnreadMsg(QString &peer, QString &msg)
{
    QMutexLocker locker(&_mutex);
    if (_unreadMsg.size() == 0)
        return false;
    ChatMessage zMsg =_unreadMsg.dequeue();
    peer = zMsg._peer;
    msg = zMsg._text;
    return true;
}
