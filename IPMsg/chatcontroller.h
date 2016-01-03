#ifndef CHATCONTROLLER_H
#define CHATCONTROLLER_H

#include <QObject>

class ChatController : public QObject
{
    Q_OBJECT
public:
    explicit ChatController(QObject *parent = 0);

signals:

public slots:
};

#endif // CHATCONTROLLER_H
