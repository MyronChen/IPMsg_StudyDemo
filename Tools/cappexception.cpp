#include "cappexception.h"

ENTER_NET
{


CAppException::CAppException() : _type(C_Unknow)
{

}

uint32_t CAppException::write(CProtocol *prot)
{
    COutRecursionTraker tracker(*prot);
    uint32_t ifer = prot->writeStructBegin("CAppException");

    ifer += prot->writeFieldBegin("type", C_INT32, 1);
    ifer += prot->writeInt32(_type);
    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldStop();
    ifer += prot->writeStructEnd();

    return ifer;
}

uint32_t CAppException::read(CProtocol *prot)
{
    CInRecursionTraker tracker(*prot);
    std::string structName;
    uint32_t ifer = prot->readStructBegin(structName);

    std::string fieldName;
    FieldType fldType(C_STOP);
    int16_t fldId;
    while (true)
    {
        ifer += prot->readFieldBegin(fieldName, fldType, fldId);
        if (fldType == C_STOP)
            break;

        switch (fldId)
        {
        case 1:
            if (fldType == C_INT32)
            {
                int32_t iType;
                ifer += prot->readInt32(iType);
                _type = (_ExceptionType)iType;
            }
            else
                ifer += prot->skip(fldType);
            break;
        default:
            ifer += prot->skip(fldType);
        }

        ifer += prot->readFieldEnd();
    }

    ifer += prot->readStructEnd();

    return ifer;
}

}LEAVE_NET
