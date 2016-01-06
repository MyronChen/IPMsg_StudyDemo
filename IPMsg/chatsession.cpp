#include "chatsession.h"
#include "util.h"
#include "chatmessage.h"
#include "Tools/cbinaryprotocol.h"

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

    CBinaryProtocol zProt(_socket);
    zMsg.send(&zProt, (sockaddr*)&_peerAddr, _peerAddrLen);
}
