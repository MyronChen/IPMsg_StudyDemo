#include "csocket.h"
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/tcp.h>
#include <sys/poll.h>

ENTER_NET{

template<class T>
inline const void* const_cast_opt(const T *v)
{
    return reinterpret_cast<const void*>(v);
}

template<class T>
inline void* cast_opt(T *v)
{
    return reinterpret_cast<void*>(v);
}

CSocket::CSocket(const QString &addr) : _addr(addr),_socket(C_INVALID_SOCKET), _lingerOn(true), _lingerVal(0),
    _noDelay(true)
{

}

CSocket::CSocket(int socket) : _socket(socket), _lingerOn(true), _lingerVal(0),
    _noDelay(true)
{

}

CSocket::~CSocket()
{

}

void CSocket::open()
{
    addrinfo hint, *pRes0(NULL), *pRes(NULL);
    char port[sizeof(65535)] = {0};
    memset(&hint, 0, sizeof(hint));
    hint.ai_family = PF_UNSPEC;
    hint.ai_socktype = SOCK_STREAM;
    hint.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    sprintf(port, "%d", IPMSG_PORT);
    int error = getaddrinfo(_addr.toLocal8Bit().constData(), port, &hint, &pRes0);
    if (error)
    {
        std::string sLogMsg = "CSocket::open() getaddrinfo()" + std::string(gai_strerror(error));
        logMsg(sLogMsg);
        close();
        throw CException();
    }

    for (pRes = pRes0; pRes; pRes = pRes->ai_next)
    {
        try{
            openConnect(pRes);
            break;
        }
        catch(CException)
        {
            if (pRes->ai_next)
                close();
            else
            {
                close();
                freeaddrinfo(pRes0);
                throw;
            }
        }
    }

    freeaddrinfo(pRes0);
}

void CSocket::close()
{
    if (_socket != C_INVALID_SOCKET)
    {
        shutdown(_socket, SHUT_RDWR);
        ::close(_socket);
    }
    _socket = C_INVALID_SOCKET;
}

bool CSocket::isOpened() const
{
    return (_socket != C_INVALID_SOCKET);
}


uint32_t CSocket::read(uint8_t *buf, uint32_t len)
{
    if (_socket == C_INVALID_SOCKET)
        throw CTransportException(CTransportException::NotOpen);
    return ::read(_socket, buf, len);
}

void CSocket::openConnect(addrinfo *res)
{
    if (isOpened())
        return;

    _socket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (_socket == -1)
    {
        int errnocopy = errno;
        std::string errMsg = std::string("CSocket::openConnect() socket") + QByteArray::number(errnocopy).constData();
        logMsg(errMsg);
        throw CException();
    }

    setLinger(_lingerOn, _lingerVal);

    setNoDelay(_noDelay);

    int ret = connect(_socket, res->ai_addr, res->ai_addrlen);
    if (ret == 0)
        return;

    if (errno != EINPROGRESS && errno != EWOULDBLOCK)
    {
        //log msg
        throw CException();
    }

    pollfd fds[1];
    fds[0].fd = _socket;
    fds[0].events = POLLOUT;
    ret = poll(fds, 1, 0);
    if (ret > 0)
    {
        //make sure there is no errors set
        int val(0);
        socklen_t lon = sizeof(val);
        int ret2 = getsockopt(_socket, SOL_SOCKET, SO_ERROR, cast_opt(&val), &lon);
        if (ret2 == -1)
        {
            //log err;
            throw CException();
        }

        if (val != 0)
        {
            //log error;
            throw CException();
        }
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

void CSocket::setLinger(bool lingerOn, int lingerVal)
{
    _lingerOn = lingerOn;
    _lingerVal = lingerVal;
    if (_socket == C_INVALID_SOCKET)
        return;

    linger zLinger = { lingerOn ? 1 : 0, lingerVal };
    int ret = setsockopt(_socket, SOL_SOCKET, SO_LINGER, cast_opt(&zLinger), sizeof(zLinger));
    if (ret == -1)
    {
        //log errno
    }
}

void CSocket::setNoDelay(bool noDelay)
{
    _noDelay = noDelay;
    if (_socket == C_INVALID_SOCKET)
        return;

    int val = noDelay ? 1 : 0;
    int ret = setsockopt(_socket, IPPROTO_TCP, TCP_NODELAY, const_cast_opt(&val), sizeof(val));
    if (ret == -1)
    {
        //log msg
    }
}

}LEAVE_NET
