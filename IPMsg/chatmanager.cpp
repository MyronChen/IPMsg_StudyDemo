#include "chatmanager.h"
#include "util.h"
#include <boost/noncopyable.hpp>
#include <QMap>

ChatManager* ChatManager::_pInstance = NULL;

ChatManager::ChatManager()
{

}

ChatManager *ChatManager::instance()
{
    if (_pInstance == NULL)
    {
        QMutexLocker zLocker(&gsMutex);
        if (_pInstance == NULL)
            _pInstance = new ChatManager();
    }

    return _pInstance;
}

int ChatManager::getPort() const
{
    return _socket.getPort();
}

ChatManager::~ChatManager()
{

}
