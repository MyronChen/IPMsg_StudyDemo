#include "cserversocket.h"
#include "fcntl.h"
#include <sys/poll.h>
#include "csocket.h"

ENTER_NET{

    template<class T>
    inline const void* const_cast_opt(const T *v)
    {
        return reinterpret_cast<const void*>(v);
    }

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

    freeaddrinfo(pRes0);

    setReuseAddr(true);
    setLinger(false, 0);
    setNoDelay(true);
    setNonblock(true);

    if (::bind(_socket, pRes->ai_addr, pRes->ai_addrlen))
    {
        //log error
        close();
        throw CException();
    }

    if (::listen(_socket, DEFAULT_BACKLOG))
    {
        //log error
        close();
        throw CException();
    }

}

void CServerSocket::close()
{
    if (_socket != C_INVALID_SOCKET)
        ::close(_socket);

    _socket = C_INVALID_SOCKET;
}

boost::shared_ptr<CTransport> CServerSocket::acceptImpl()
{
    if (_socket == C_INVALID_SOCKET)
        throw CException();

    pollfd fd[2];
    while (true)
    {
        memset(fd, 0, sizeof(fd));
        fd[0].fd = _socket;
        fd[0].events = POLLIN;
        if (_interruptSocketReader != C_INVALID_SOCKET)
        {
            fd[1].fd = _interruptSocketReader;
            fd[1].events = POLLIN;
        }

        int ret = poll(fd, 2, -1);
        if (ret > 0)
        {
            if (_interruptSocketReader != C_INVALID_SOCKET && fd[1].revents & POLLIN)
                throw CException();

            if (fd[0].revents & POLLIN)
                break;
        }
        else if (ret == 0)
        {
            //timeout
            throw CException();
        }
        else
        {
            //poll error
            throw CException();
        }
    }

    sockaddr_storage clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
    int clientSocket = ::accept(_socket, (sockaddr*)&clientAddr, &addrLen);
    if (clientSocket == -1)
        throw CException();

    /* block */
    int flags = fcntl(clientSocket, F_GETFL, 0);
    if (flags == -1)
    {
        //log msg
        ::close(clientSocket);
        throw CException();
    }
    flags &= ~O_NONBLOCK;
    if (-1 == fcntl(clientSocket, F_SETFL, flags))
    {
        //log msg
        ::close(clientSocket);
        throw CException();
    }

    boost::shared_ptr<CSocket> pClientSocket = boost::shared_ptr<CSocket>(new CSocket(clientSocket));
    return pClientSocket;
}

void CServerSocket::setReuseAddr(bool bReuse)
{
    int opt = bReuse ? 1 : 0;
    if (-1 == setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, const_cast_opt(&opt), sizeof(opt)))
    {
        //log error
        close();
        throw CException();
    }
}

void CServerSocket::setLinger(bool lingerOn, int lingerVal)
{
    if (_socket == C_INVALID_SOCKET)
        return;

    linger zLinger = { lingerOn ? 1 : 0, lingerVal };
    int ret = setsockopt(_socket, SOL_SOCKET, SO_LINGER, const_cast_opt(&zLinger), sizeof(zLinger));
    if (ret == -1)
    {
        //log errno
        close();
        throw CException();
    }
}

void CServerSocket::setNoDelay(bool noDelay)
{
    if (_socket == C_INVALID_SOCKET)
        return;

    int val = noDelay ? 1 : 0;
    int ret = setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, const_cast_opt(&val), sizeof(val));
    if (ret == -1)
    {
        //log msg
        close();
        throw CException();
    }
}

void CServerSocket::setNonblock(bool nonblock)
{
    if (_socket == C_INVALID_SOCKET)
        return;

    int flags = fcntl(_socket, F_GETFL, 0);
    if (flags == -1)
    {
        //log msg
        close();
        throw CException();
    }

    if (nonblock)
        flags |= O_NONBLOCK;
    else
        flags &= ~O_NONBLOCK;

    if (-1 == fcntl(_socket, F_SETFL, flags))
    {
        //log msg
        close();
        throw CException();
    }
}


} LEAVE_NET
