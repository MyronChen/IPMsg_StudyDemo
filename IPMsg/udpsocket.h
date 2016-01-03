#ifndef UDPSOCKET_H
#define UDPSOCKET_H


class UdpSocket
{
public:
    UdpSocket();

    int getPort() const;
    bool isOpen() const { return _socket != -1; }

private:
    void close();


private:
    int _socket;
};

#endif // UDPSOCKET_H
