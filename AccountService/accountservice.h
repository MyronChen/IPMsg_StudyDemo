#ifndef ACCOUNTSERVICE_H
#define ACCOUNTSERVICE_H


#include "../Tools/cprotocol.h"
#include "../Tools/cprocessor.h"

USING_PROTOCOL
USING_NET

class AccountIf
{
public:
    virtual void login(const std::string &name, const std::string &pwd) = 0;
    virtual void reg(const std::string &name, const std::string &pwd) = 0;

};

class AccountClient : virtual public AccountIf
{
public:
    AccountClient(boost::shared_ptr<CProtocol> prot)
        : _prot(prot)
    {}
    virtual void login(const std::string &name, const std::string &pwd);
    virtual void reg(const std::string &name, const std::string &pwd);

    void loginSend(const std::string &name, const std::string &pwd);
    void loginRecv();

    void registerSend(const std::string &name, const std::string &pwd);

protected:
    boost::shared_ptr<CProtocol> _prot;
};

class AccountProcessor : public CProcessor
{
private:
    typedef void (AccountProcessor::*FUNC)(int32_t, CProtocol *, void*);
    typedef std::map<std::string, FUNC> ProcessorMap;

    void loginDispatch(int32_t seqid, CProtocol *proc, void *data);
    void registerDispatch(int32_t seqid, CProtocol *proc, void *data);

protected:
    virtual bool dispatchProcess(CProtocol*,
                                  const std::string &name,
                                  int32_t seqid);


public:
    AccountProcessor(boost::shared_ptr<AccountIf> iface)
        : _iface(iface)
    {
        _funcMap["login"] = &AccountProcessor::loginDispatch;
        _funcMap["register"] = &AccountProcessor::registerDispatch;
    }


private:
    boost::shared_ptr<AccountIf> _iface;
    ProcessorMap _funcMap;

};

#endif // ACCOUNTSERVICE_H
