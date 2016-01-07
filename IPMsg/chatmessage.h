#ifndef CHATMESSAGE_H
#define CHATMESSAGE_H

#include "udpsocket.h"
#include "Tools/cprotocol.h"
#include "Tools/tools.h"

USING_PROTOCOL;

class ChatMessage
{
public:
    enum Type {Text};

    bool send(CProtocol *protocol, sockaddr *zAddr, socklen_t len);
    bool recv(CProtocol *protocol, sockaddr_storage &zAddr, socklen_t &len);

    Type _type;
    QString _peer;
    QString _text;
};

#endif // CHATCONTROLLER_H
