#ifndef READLIST_H
#define READLIST_H

#include <QList>

class ReadList
{

public:
    ReadList();
    ~ReadList();
    void readF();

private:
    void importData(QList<QString> &data) ;
    void setExpand(QList<QString> &data) ;
    void setTimer(QList<QString> &data) ;
};

#endif // READLIST_H
