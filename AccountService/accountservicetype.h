#ifndef ACCOUNTSERVICETYPE_H
#define ACCOUNTSERVICETYPE_H

#include "../Tools/cprotocol.h"
#include "../Tools/cprocessor.h"
#include <map>

struct VoidArgs
{
    uint32_t write(CProtocol *prot);
    uint32_t read(CProtocol * prot);
};

struct MapStrStr
{
    uint32_t write(CProtocol *prot);
    uint32_t read(CProtocol * prot);

    std::map<std::string, std::string> data;
};



#endif // ACCOUNTSERVICETYPE_H
