#include <QCoreApplication>
#include "tools.h"
#include "cbinaryprotocol.h"

USING_NET

int main(int argc, char *argv[])
{
    CServer server(boost::make_shared<AccountProcessor>(boost::make_shared<AccountHandler>()),
                                               boost::make_shared<CServerSocket>(),
                   boost::make_shared<CBinaryProtocolFactory>() );

    server.serve();

    QCoreApplication a(argc, argv);

    return a.exec();
}

