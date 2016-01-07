#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Tools/ctransport.h"
#include <QString>
#include <QMutex>
#include "Tools/tools.h"
#include <netdb.h>
#include <arpa/inet.h>

ENTER_NET{                

class UdpSocket : public CVirtualTransport<UdpSocket>
{
public:
    UdpSocket();
    virtual ~UdpSocket();

    int getPort() const;
    virtual void open();
    virtual void close();
    virtual bool isOpened() const { return _socket != -1; }
    virtual bool peek();

    void enterWrite(sockaddr *addr, socklen_t len);
    void leaveWrite();
    uint32_t write(const uint8_t *buf, uint32_t len);
    uint32_t read(uint8_t *buf, uint32_t len);

private:



private:
    int _socket;
    QMutex _mutex;

    sockaddr_storage _addr;
    socklen_t _len;
};

class UdpSocketInputLocker
{
public:
    UdpSocketInputLocker(UdpSocket*, sockaddr *, socklen_t );
    ~UdpSocketInputLocker();

private:
    UdpSocket *_pSocket;
};

}LEAVE_NET

#endif // UDPSOCKET_H
