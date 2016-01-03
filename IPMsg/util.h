#ifndef UTIL_H
#define UTIL_H

#include <QMutex>
#include <boost/make_shared.hpp>
#include <serverstub.h>
#include <QObject>

extern QMutex gsMutex;

class SignalLocker
{
public:
    SignalLocker(QObject *obj) : _obj(obj)
    {
        bBlocked = _obj->blockSignals(true);
    }

    ~SignalLocker()
    {
        if (!bBlocked)
            _obj->blockSignals(false);
    }

private:
    QObject *_obj;
    bool bBlocked;
};

#endif // UTIL_H
