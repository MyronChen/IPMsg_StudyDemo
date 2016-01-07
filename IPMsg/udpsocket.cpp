#include "udpsocket.h"
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <string.h>
#include <arpa/inet.h>

static int test = 1;

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

UdpSocket::UdpSocket() : _socket(-1)
{

}

UdpSocket::~UdpSocket()
{

}

int UdpSocket::getPort() const
{
    if (!isOpened())
        return 0;

    sockaddr_storage zAddr;
    socklen_t len = sizeof(zAddr);
    if (::getsockname(_socket, reinterpret_cast<sockaddr*>(&zAddr), &len))
        return 0;
    if (zAddr.ss_family == AF_INET)
        return ntohs(((sockaddr_in*)(&zAddr))->sin_port);
    else if (zAddr.ss_family == AF_INET6)
        return ntohs(((sockaddr_in6*)(&zAddr))->sin6_port);
    else
        return 0;
}

void UdpSocket::open()
{
//    sockaddr_in zAddr;
//    memset(&zAddr, 0, sizeof(zAddr));
//    zAddr.sin_family = AF_INET;
//    zAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    zAddr.sin_port = htons(0);
//    _socket = ::socket(AF_INET, SOCK_DGRAM, 0);
//    if (_socket == -1)
//        return;

//    if (::bind(_socket, (sockaddr*)&zAddr, sizeof(zAddr)))
//    {
//        int errnoCopy = errno;
//        //log error
//        close();
//        return;
//    }
//return;

//////////////////////////////////////////////////////////////////////////////

    sockaddr_in6 zAddr;
    memset(&zAddr, 0, sizeof(zAddr));
    zAddr.sin6_family = AF_INET6;
    zAddr.sin6_addr = in6addr_any;
    zAddr.sin6_port = htons(0);
    _socket = ::socket(AF_INET6, SOCK_DGRAM, 0);
    if (_socket == -1)
        return;

    if (::bind(_socket, (sockaddr*)&zAddr, sizeof(zAddr)))
    {
        int errnoCopy = errno;
        //log error
        close();
        return;
    }
}

void UdpSocket::close()
{
    ::close(_socket);
    _socket = -1;
}

bool UdpSocket::peek()
{
    if (!isOpened())
        return false;

    int8_t opt(0);
    int result = static_cast<int>(::recv(_socket, cast_opt(&opt), 1, MSG_PEEK));
    if (result == -1)
        throw CTransportException(CTransportException::Unknow);
    return (result > 0);
}

void UdpSocket::enterWrite(sockaddr *addr, socklen_t len)
{
    _mutex.lock();
    memcpy((void*)&_addr, (void*)addr, len);
    _len = len;
}

void UdpSocket::leaveWrite()
{
    _mutex.unlock();
}

uint32_t UdpSocket::write(const uint8_t *buf, uint32_t len)
{
    return ::sendto(_socket, const_cast_opt(buf), len, 0, (sockaddr*)&_addr, _len);
}

uint32_t UdpSocket::read(uint8_t *buf, uint32_t len)
{
    sockaddr_storage zRecvAddr;
    socklen_t iRecvLen = sizeof(zRecvAddr);
    return ::recvfrom(_socket, cast_opt(buf), len, 0, (sockaddr*)&zRecvAddr, &iRecvLen);
}

UdpSocketInputLocker::UdpSocketInputLocker(UdpSocket *pSocket, sockaddr *addr, socklen_t len) : _pSocket(pSocket)
{
    pSocket->enterWrite(addr, len);
}

UdpSocketInputLocker::~UdpSocketInputLocker()
{
    _pSocket->leaveWrite();
}

}
