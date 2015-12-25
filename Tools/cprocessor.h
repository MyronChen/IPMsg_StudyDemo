#ifndef CPROCESSOR_H
#define CPROCESSOR_H

#include "tools.h"
#include "cprotocol.h"

USING_PROTOCOL

ENTER_NET{


class CProcessor
{
public:
    CProcessor();
    virtual ~CProcessor() {}

    virtual bool process(boost::shared_ptr<CProtocol>);

protected:
    virtual bool dispatchProcess(CProtocol*,
                                  const std::string &name,
                                  int32_t seqid) = 0;

};


}LEAVE_NET

#endif // CPROCESSOR_H
