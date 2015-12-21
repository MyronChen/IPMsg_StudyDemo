#include "cserversocket.h"

ENTER_NET{

    void destoryer_of_socket(int *pSocket)
    {
        ::close(*pSocket);
        delete pSocket;
    }

CServerSocket::CServerSocket()
    : _socket(C_INVALID_SOCKET), _interruptSocketReader(C_INVALID_SOCKET), _interruptSocketWriter(C_INVALID_SOCKET),
      _childInterruptWriter(C_INVALID_SOCKET)
{

}

void CServerSocket::listen()
{
    int sv[2] = {0};
    if (-1 == socketpair(AF_LOCAL, SOCK_STREAM, 0, sv))
    {
        QString errorMsg = QString("CServerSocket::listen() ") + QString::number(errno);
        logMsg(errorMsg);
        _interruptSocketReader = C_INVALID_SOCKET;
        _interruptSocketWriter = C_INVALID_SOCKET;
    }
    else
    {
        _interruptSocketReader = sv[0];
        _interruptSocketWriter = sv[1];
    }

    if (-1 == socketpair(AF_LOCAL, SOCK_STREAM, 0, sv))
    {
        QString errorMsg = QString("CServerSocket::listen() socketpair") + QString::number(errno);
        logMsg(errorMsg);
        _childInterruptReader.reset();
        _childInterruptWriter = C_INVALID_SOCKET;
    }
    else
    {
        _childInterruptWriter = sv[1];
        _childInterruptReader = boost::shared_ptr<int>(new int(sv[0]), destoryer_of_socket);
    }

    addrinfo hint, *pRes0, *pRes;
    char port[sizeof("65535")] = {0};
    memset(&hint, 0, sizeof(hint));
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_family = PF_UNSPEC;
    hint.ai_flags = AI_ADDRCONFIG | AI_PASSIVE;
    sprintf(port, "%d", IPMSG_PORT);
    int error = getaddrinfo(NULL, port, &hint, &pRes0);
    if (error)
    {
        QString errMsg = QString("CServerSocket::listen() getaddrinfo") + gai_strerror(error);
        logMsg(errMsg);
        throw CException();
    }

    for (pRes = pRes0; pRes; pRes = pRes0->ai_next)
    {
        if (pRes->ai_family == AF_INET6 || !pRes->ai_next)
            break;
    }

    _socket = socket(pRes->ai_family, pRes->ai_socktype, pRes->ai_protocol);
    if (_socket == C_INVALID_SOCKET)
    {
        int errcopy = errno;
        QString errMsg = QString("CServerSocket::listen() socket") + QString::number(errcopy);
        logMsg(errMsg);
        close();
        throw CException();
    }

}



} LEAVE_NET
