#ifndef ACCOUNTSERVICE_H
#define ACCOUNTSERVICE_H


#include "../Tools/cprotocol.h"
#include "../Tools/cprocessor.h"
#include <map>

USING_PROTOCOL
USING_NET

class AccountIf
{
public:
    virtual void login(const std::string &name, const std::string &pwd, int32_t port) = 0;
    virtual void reg(const std::string &name, const std::string &pwd, int32_t port) = 0;
    virtual void getOnlineUsers(std::map<std::string, std::string> &onlineMap) = 0;

};

class AccountClient : virtual public AccountIf
{
public:
    AccountClient(boost::shared_ptr<CProtocol> prot)
        : _prot(prot)
    {}
    virtual void login(const std::string &name, const std::string &pwd, int32_t port);
    virtual void reg(const std::string &name, const std::string &pwd, int32_t port);
    virtual void getOnlineUsers(std::map<std::string, std::string> &onlineMap);

    void loginSend(const std::string &name, const std::string &pwd, int32_t port);
    void loginRecv();

    void registerSend(const std::string &name, const std::string &pwd, int32_t port);

    void voidSend(const std::string &name);
    void recv_Map_string_string(std::map<std::string, std::string> &output);

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
    void getOnlineUsersDispatch(int32_t seqid, CProtocol *proc, void *data);

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
        _funcMap["getOnlineUsers"] = &AccountProcessor::getOnlineUsersDispatch;
    }


private:
    boost::shared_ptr<AccountIf> _iface;
    ProcessorMap _funcMap;

};

#endif // ACCOUNTSERVICE_H
