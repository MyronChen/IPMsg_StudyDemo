#include "udpsocket.h"
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/poll.h>
#include <string.h>

UdpSocket::UdpSocket()
{
//    sockaddr_in zAddr;
//    memset(&zAddr, 0, sizeof(zAddr));
//    zAddr.sin_family = AF_INET;
//    zAddr.sin_addr.s_addr = htonl(INADDR_ANY);
//    zAddr.sin_port = htons(0);
//    _socket = ::socket(AF_INET)

    sockaddr_in6 zAddr;
    memset(&zAddr, 0, sizeof(zAddr));
    zAddr.sin6_family = AF_INET6;
    zAddr.sin6_addr = in6addr_any;
    zAddr.sin6_port = 0;
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

int UdpSocket::getPort() const
{
    if (!isOpen())
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

void UdpSocket::close()
{
    ::close(_socket);
    _socket = -1;
}

