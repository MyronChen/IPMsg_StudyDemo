#ifndef CTRANSPORT_H
#define CTRANSPORT_H
#include <exception>
#include "tools.h"

ENTER_NET{

class CTransport;

template<class Transport_>
uint32_t readallImpl(Transport_ &trans, uint8_t *buf, uint32_t len)
{
    uint32_t result(0);
    while(result < len)
    {
        result += trans.read(buf, len);
        if (result < 0)
            throw CException();
    }

    return result;
}

class CTransport
{
public:
    virtual ~CTransport() {};

    virtual void open() { throw std::exception(); };
    virtual void close() { throw std::exception(); }
    virtual bool isOpened() const {throw std::exception();}
    virtual bool writeEnd() { throw CException(); }
    virtual bool flush() { throw CException(); }

    uint32_t readall(uint8_t *buf, uint32_t len) { return readall_virt(buf, len);}
    virtual uint32_t readall_virt(uint8_t *buf, uint32_t len)
    {
        return readallImpl(*this, buf, len);
    }

    uint32_t read(uint8_t *buf, uint32_t len) { return readall_virt(buf, len);}
    virtual uint32_t read_virt(uint8_t *buf, uint32_t len)
    {
        throw CException();
    }


protected:
    CTransport() {};
};


class CDefaultTransport : public CTransport
{
protected:
    CDefaultTransport() {}

    uint32_t readall(uint8_t *buf, uint32_t len) { return CTransport::readall_virt(buf, len);}
    uint32_t read(uint8_t *buf, uint32_t len) { return CTransport::read_virt(buf, len);}

};

template <class Transport_, class Super_ = CDefaultTransport>
class CVirtualTransport : public Super_
{
protected:
    CVirtualTransport() {}

    virtual uint32_t readall_virt(uint8_t *buf, uint32_t len)
    {
        return static_cast<Transport_*>(this)->readall(buf, len);
    }
    virtual uint32_t read_virt(uint8_t *buf, uint32_t len)
    {
        throw static_cast<Transport_*>(this)->read(buf, len);
    }

};

}LEAVE_NET
#endif // CTRANSPORT_H
