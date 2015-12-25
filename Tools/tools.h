#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <map>
#include <QString>
#include <boost/shared_ptr.hpp>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/tcp.h>
#include <boost/make_shared.hpp>


#include "ctransportexception.h"

#define IPMSG_PORT  20001

#define ENTER_NET namespace CNetFramework
#define LEAVE_NET
#define USING_NET using namespace CNetFramework;

#define ENTER_PROTOCOL namespace CNetFramework { namespace protocol
#define LEAVE_PROTOCOL }
#define USING_PROTOCOL using namespace CNetFramework::protocol;


#define CException std::exception

#define C_INVALID_SOCKET -1

extern void logMsg(const std::string &);
extern void logMsg(const QString &);

#endif // TOOLS_H
