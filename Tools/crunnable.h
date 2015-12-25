#ifndef CRUNNABLE_H
#define CRUNNABLE_H

#include "tools.h"

class CRunnable
{
public:
    CRunnable();
    virtual ~CRunnable();

    virtual void run() = 0;
};

#endif // CRUNNABLE_H
