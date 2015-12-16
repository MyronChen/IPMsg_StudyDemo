#ifndef CTRANSPORT_H
#define CTRANSPORT_H
#include <exception>
#include "tools.h"

ENTER_NET{

class CTransport
{
public:
    virtual ~CTransport() {};

    virtual void open() { throw std::exception(); };
    virtual void close() { throw std::exception(); }
    virtual bool isOpened() const {throw std::exception();}

protected:
    CTransport() {};
};


class CDefaultTransport : public CTransport
{
protected:
    CDefaultTransport() {}
};

template <class Transport_, class Super_ = CDefaultTransport>
class CVirtualTransport : public Super_
{
protected:
    CVirtualTransport() {}
};

}LEAVE_NET
#endif // CTRANSPORT_H
