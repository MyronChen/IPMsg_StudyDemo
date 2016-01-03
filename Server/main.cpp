#include <QCoreApplication>
#include "tools.h"
#include "cbinaryprotocol.h"
#include "cserversocket.h"
#include "cserver.h"
#include "../AccountService/accountservice.h"
#include "accunthandler.h"
#include "serverpri.h"
#include "binaryprotocol.h"


USING_NET
USING_PROTOCOL



int main(int argc, char *argv[])
{
    MySQLGuard zMySQLGuard;
    CServer server(boost::make_shared<AccountProcessor>(boost::make_shared<AccountHandler>()),
                                               boost::make_shared<CServerSocket>(),
                   boost::make_shared<BinaryProtocolFactory>() );

    server.serve();

    QCoreApplication a(argc, argv);

    return a.exec();
}

