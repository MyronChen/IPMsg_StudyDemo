#include "accountservice.h"
#include "cappexception.h"
#include "../AccountService/accountservicetype.h"

struct LoginArgs
{
    uint32_t write(boost::shared_ptr<CProtocol> prot);
    uint32_t read(CProtocol * prot);

    std::string name;
    std::string pwd;
    int32_t port;
};

uint32_t LoginArgs::write(boost::shared_ptr<CProtocol> prot)
{
    COutRecursionTraker tracker(*prot);
    uint32_t ifer = prot->writeStructBegin("LoginArgs");

    ifer += prot->writeFieldBegin("name", C_STRING, 1);
    ifer += prot->writeString(name);
    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldBegin("pwd", C_STRING, 2);
    ifer += prot->writeString(pwd);
    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldBegin("port", C_INT32, 3);
    ifer += prot->writeInt32(port);
    ifer += prot->writeFieldEnd();

    ifer += prot->writeFieldStop();
    ifer += prot->writeStructEnd();

    return ifer;
}

uint32_t LoginArgs::read(CProtocol *prot)
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
            if (fldType != C_STRING)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }
            iBytes += prot->readString(name);
            break;
        case 2:
            if (fldType != C_STRING)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }
            iBytes += prot->readString(pwd);
            break;
        case 3:
            if (fldType != C_INT32)
            {
                prot->skip(fldType);
                throw CTransportException(CTransportException::Unknow);
            }
            iBytes += prot->readInt32(port);
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

void AccountClient::login(const std::string &name, const std::string &pwd, int32_t port)
{
    loginSend(name, pwd, port);
    loginRecv();
}

void AccountClient::reg(const std::string &name, const std::string &pwd, int32_t port)
{
    registerSend(name, pwd, port);
    loginRecv();
}

void AccountClient::getOnlineUsers(std::map<std::string, std::string> &onlineMap)
{
    voidSend("getOnlineUsers");
    recv_Map_string_string(onlineMap);
}

int32_t AccountClient::getPeerPort(const std::string &peerName)
{
    strSend("getPeerPort", peerName);
    return recv_int32();
}

void AccountClient::loginSend(const std::string &name, const std::string &pwd, int32_t port)
{
    _prot->writeMessageBegin("login", C_Call, 0);
    LoginArgs arg;
    arg.name = name;
    arg.pwd = pwd;
    arg.port = port;
    arg.write(_prot);
    _prot->writeMessageEnd();
    _prot->getTransport()->writeEnd();
    _prot->getTransport()->flush();
}

void AccountClient::loginRecv()
{
    std::string msgName;
    MessageType msgType(C_Call);
    int32_t seqId;

    _prot->readMessageBegin(msgName, msgType, seqId);
    if (msgType == C_EXCEPTION)
    {
        CAppException zAppEx;
        zAppEx.read(_prot.get());
        _prot->readMessageEnd();
        _prot->getTransport()->readEnd();
        throw zAppEx;
    }

    if (msgType != C_REPLY)
    {
        _prot->skip(C_STRUCT);
        _prot->readMessageEnd();
        _prot->getTransport()->readEnd();
        return;
    }

    _prot->readMessageEnd();
    _prot->getTransport()->readEnd();
}

void AccountClient::registerSend(const std::string &name, const std::string &pwd, int32_t port)
{
    _prot->writeMessageBegin("register", C_Call, 0);
    LoginArgs arg;
    arg.name = name;
    arg.pwd = pwd;
    arg.port = port;
    arg.write(_prot);
    _prot->writeMessageEnd();
    _prot->getTransport()->writeEnd();
    _prot->getTransport()->flush();
}

void AccountClient::voidSend(const std::string &name)
{
    _prot->writeMessageBegin(name, C_Call, 0);
    _prot->writeMessageEnd();
    _prot->getTransport()->writeEnd();
    _prot->getTransport()->flush();
}

void AccountClient::recv_Map_string_string(std::map<std::string, std::string> &output)
{
    std::string msgName;
    MessageType msgType(C_Call);
    int32_t seqId;

    _prot->readMessageBegin(msgName, msgType, seqId);
    if (msgType == C_EXCEPTION)
    {
        CAppException zAppEx;
        zAppEx.read(_prot.get());
        _prot->readMessageEnd();
        _prot->getTransport()->readEnd();
        throw zAppEx;
    }

    if (msgType != C_REPLY)
    {
        _prot->skip(C_STRUCT);
        _prot->readMessageEnd();
        _prot->getTransport()->readEnd();
        return;
    }

    MapStrStr result;
    result.read(_prot.get());
    output = result.data;
    _prot->readMessageEnd();
    _prot->getTransport()->readEnd();
}

void AccountClient::strSend(const std::string &funcName, const std::string &param)
{
    _prot->writeMessageBegin(funcName, C_Call, 0);
    _prot->writeString(param);
    _prot->writeMessageEnd();
    _prot->getTransport()->writeEnd();
    _prot->getTransport()->flush();
}

int32_t AccountClient::recv_int32()
{
    std::string msgName;
    MessageType msgType(C_Call);
    int32_t seqId;

    _prot->readMessageBegin(msgName, msgType, seqId);
    if (msgType == C_EXCEPTION)
    {
        CAppException zAppEx;
        zAppEx.read(_prot.get());
        _prot->readMessageEnd();
        _prot->getTransport()->readEnd();
        throw zAppEx;
    }

    if (msgType != C_REPLY)
    {
        _prot->skip(C_STRUCT);
        _prot->readMessageEnd();
        _prot->getTransport()->readEnd();
        throw CTransportException(CTransportException::Unknow);
    }

    int32_t ret(0);
    _prot->readInt32(ret);
    _prot->readMessageEnd();
    _prot->getTransport()->readEnd();
    return ret;
}


void AccountProcessor::loginDispatch(int32_t seqid, CProtocol *prot, void *data)
{
    LoginArgs arg;
    arg.read(prot);
    prot->readMessageEnd();
    prot->getTransport()->readEnd();

    try
    {
        _iface->login(arg.name, arg.pwd, arg.port);
    }
    catch (const CException &cex)
    {
        CAppException zAppEx;

        prot->writeMessageBegin("login", C_EXCEPTION, seqid);
        zAppEx.write(prot);
        prot->writeMessageEnd();
        prot->getTransport()->writeEnd();
        prot->getTransport()->flush();
        return;
    }

    prot->writeMessageBegin("login", C_REPLY, seqid);
    prot->writeMessageEnd();
    prot->getTransport()->writeEnd();
    prot->getTransport()->flush();
}

void AccountProcessor::registerDispatch(int32_t seqid, CProtocol *prot, void *data)
{
    LoginArgs arg;
    arg.read(prot);
    prot->readMessageEnd();
    prot->getTransport()->readEnd();

    try
    {
        _iface->reg(arg.name, arg.pwd, arg.port);
    }
    catch (const CException &cex)
    {
        CAppException zAppEx;

        prot->writeMessageBegin("register", C_EXCEPTION, seqid);
        zAppEx.write(prot);
        prot->writeMessageEnd();
        prot->getTransport()->writeEnd();
        prot->getTransport()->flush();
        return;
    }

    prot->writeMessageBegin("register", C_REPLY, seqid);
    prot->writeMessageEnd();
    prot->getTransport()->writeEnd();
    prot->getTransport()->flush();
}

void AccountProcessor::getOnlineUsersDispatch(int32_t seqid, CProtocol *prot, void *data)
{
    VoidArgs arg;
    arg.read(prot);
    prot->readMessageEnd();
    prot->getTransport()->readEnd();

    MapStrStr result;

    try
    {
        _iface->getOnlineUsers(result.data);
    }
    catch (const CException &cex)
    {
        CAppException zAppEx;

        prot->writeMessageBegin("getOnlineUsers", C_EXCEPTION, seqid);
        zAppEx.write(prot);
        prot->writeMessageEnd();
        prot->getTransport()->writeEnd();
        prot->getTransport()->flush();
        return;
    }

    prot->writeMessageBegin("getOnlineUsers", C_REPLY, seqid);
    result.write(prot);
    prot->writeMessageEnd();
    prot->getTransport()->writeEnd();
    prot->getTransport()->flush();
}

void AccountProcessor::getPeerPortDispatch(int32_t seqid, CProtocol *prot, void *data)
{
    std::string peer;
    prot->readString(peer);
    prot->readMessageEnd();
    prot->getTransport()->readEnd();

    int32_t port(0);

    try
    {
        port = _iface->getPeerPort(peer);
    }
    catch (const CException &cex)
    {
        CAppException zAppEx;

        prot->writeMessageBegin("getPeerPortDispatch", C_EXCEPTION, seqid);
        zAppEx.write(prot);
        prot->writeMessageEnd();
        prot->getTransport()->writeEnd();
        prot->getTransport()->flush();
        return;
    }

    prot->writeMessageBegin("getPeerPortDispatch", C_REPLY, seqid);
    prot->writeInt32(port);
    prot->writeMessageEnd();
    prot->getTransport()->writeEnd();
    prot->getTransport()->flush();
}

bool AccountProcessor::dispatchProcess(CProtocol *proc, const std::string &name, int32_t seqid)
{
    ProcessorMap::iterator iter = _funcMap.find(name);
    if (iter != _funcMap.end())
    {
        (this->*(iter->second))(seqid, proc, NULL);
    }
    else
    {
        //throe exception to client
        assert(false);
        return true;
    }
}


