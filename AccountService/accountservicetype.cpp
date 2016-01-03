#include "accountservicetype.h"
#include <utility>



uint32_t VoidArgs::write(CProtocol *prot)
{
    return 0;
}

uint32_t VoidArgs::read(CProtocol *prot)
{
    return 0;
}


uint32_t MapStrStr::write(CProtocol *prot)
{
    COutRecursionTraker tracker(*prot);
    uint32_t ifer = prot->writeStructBegin("MapStrStr");

    ifer += prot->writeFieldBegin("data", C_MAP, 1);
    ifer += prot->writeMapBegin(C_STRING, C_STRING, data.size());

    for (auto iter = data.begin(); iter != data.end(); iter++)
    {
        prot->writeString(iter->first);
        prot->writeString(iter->second);
    }

    ifer += prot->writeMapEnd();

    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldStop();
    ifer += prot->writeStructEnd();

    return ifer;
}

uint32_t MapStrStr::read(CProtocol *prot)
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
            if (fldType != C_MAP)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }

            int32_t size;
            FieldType mapType1, mapType2;
            iBytes += prot->readMapBegin(mapType1, mapType2, size);
            for (int i = 0; i< size; i++)
            {
                std::string key, val;
                iBytes += prot->readString(key);
                iBytes += prot->readString(val);
                data.insert(std::make_pair(key, val));
            }
            break;
        default:
            prot->skip(fldType);
            throw CTransportException(CTransportException::Unknow);
        }

        iBytes += prot->readFieldEnd();
    }
    iBytes += prot->readStructEnd();

    return iBytes;
}
