#include "accunthandler.h"


void AccountHandler::login(const std::string &name, const std::string &pwd)
{
    if (name != "admin")
        throw CException();
}
