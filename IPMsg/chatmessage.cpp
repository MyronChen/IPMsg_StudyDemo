#include "chatmessage.h"
#include <utility>
#include "../Tools/cprocessor.h"
#include "udpsocket.h"

USING_NET;

bool ChatMessage::send(CProtocol *protocol, sockaddr *zAddr, socklen_t len)
{
    boost::shared_ptr<UdpSocket> pSock = boost::dynamic_pointer_cast<UdpSocket>(protocol->getTransport());
    if (!pSock)
        return false;

    UdpSocketInputLocker locker(pSock.get(), zAddr, len);

    COutRecursionTraker tracker(*protocol);
    uint32_t ifer = protocol->writeStructBegin("ChatMessage");

    ifer += protocol->writeFieldBegin("type", C_INT32, 1);
    ifer += protocol->writeInt32(_type);
    ifer += protocol->writeFieldEnd();

    ifer += protocol->writeFieldBegin("text", C_STRING, 2);
    ifer += protocol->writeString(_text.toUtf8().constData());
    ifer += protocol->writeFieldEnd();

    ifer += protocol->writeFieldBegin("peer", C_STRING, 3);
    ifer += protocol->writeString(_peer.toUtf8().constData());
    ifer += protocol->writeFieldEnd();

    ifer += protocol->writeFieldStop();
    ifer += protocol->writeStructEnd();

    return true;
}

bool ChatMessage::recv(CProtocol *prot, sockaddr_storage &zAddr, socklen_t &len)
{
    CInRecursionTraker tracker(*prot);

    std::string sStructName;
    uint32_t iBytes = prot->readStructBegin(sStructName);

    FieldType fldType;
    while (true)
    {
        int16_t iFldId;
        std::string sFldName;
        iBytes += prot->readFieldBegin(sFldName, fldType, iFldId);
        if (fldType == C_STOP)
            break;
        switch (iFldId)
        {
        case 1:
        {
            if (fldType != C_INT32)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }

            int32_t type;
            iBytes += prot->readInt32(type);
            _type = (Type)type;
            break;
        }
        case 2:
        {
            if (fldType != C_STRING)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }

            std::string text;
            iBytes += prot->readString(text);
            _text = QString::fromUtf8(text.c_str());
            break;
        }
        case 3:
        {
            if (fldType != C_STRING)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }

            std::string text;
            iBytes += prot->readString(text);
            _peer = QString::fromUtf8(text.c_str());
            break;
        }
        default:
            prot->skip(fldType);
            throw CTransportException(CTransportException::Unknow);
        }

        iBytes += prot->readFieldEnd();
    }
    iBytes += prot->readStructEnd();

    return true;
}

