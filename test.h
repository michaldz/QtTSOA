#ifndef TEST_H
#define TEST_H
#include <QThread>
#include  "libplayerc++/playerc++.h"


class Test : public QThread
{
public:
    Test();
    void run();
    int zmienna;
    void testt();
};

#endif // TEST_H

