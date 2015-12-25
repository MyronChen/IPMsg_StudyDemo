#include "cbinaryprotocol.h"

ENTER_PROTOCOL{

    template<class Transport_, class ByteOrder_>
    uint32_t CBinaryProtocolT<Transport_, ByteOrder_>::readMessageBegin(std::string &name, protocol::MessageType &type, int32_t &seqid)
    {
        uint32_t result(0);
        int32_t version(0);
        result += readInt32(version);

        return result;
    }

    template<class Transport_, class ByteOrder_>
    uint32_t CBinaryProtocolT::readInt32(int32_t &val)
    {
        union bytes
        {
            uint8_t b[4];
            int32_t all;
        } theBytes;

        _trans->readall(theBytes.b, 4);

        val = ByteOrder_::fromwire32(theBytes.all);

        return 4;
    }



}LEAVE_PROTOCOL
