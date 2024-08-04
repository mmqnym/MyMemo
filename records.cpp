#include "Records.h"
#include <QVector>

#define DEFAULT_SIZE 10

Records g_records ;

void Records::initRecs()
{
    recs.reserve(DEFAULT_SIZE) ;
}

void Records::init()
{
    initRecs() ;
}

int Records::size()
{
    return recs.size() ;
}

bool Records::comp(const aRecord &a, const aRecord &b)
{
    if (a.priority < b.priority)
        return true ;
    else
        return false ;
}

void Records::add(QString &thing, int order, QString &deadline, QString &expand)
{
    aRecord temp ;
    temp.priority = order ;
    temp.thing = thing ;
    temp.deadline = deadline ;
    temp.expand = expand ;
    recs.append(temp) ;
    std::sort(recs.begin(), recs.end(), comp) ;

}

void Records::remove(int order)
{
    recs.erase(recs.begin()+order) ;
    std::sort(recs.begin(), recs.end(), comp) ;
}

