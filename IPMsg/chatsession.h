#ifndef CHATSESSION_H
#define CHATSESSION_H
#include <QString>

class ChatSession
{
public:
    ChatSession(const QString &peer);

private:
    QString _peer;
};

#endif // CHATSESSION_H
