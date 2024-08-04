#ifndef RECORDS_H
#define RECORDS_H

#include <QVector>
#include <QtAlgorithms>

class Records
{
private:
    typedef struct aRec
    {
        int priority ;
        QString thing ;
        QString deadline ;
        QString expand ;
    } aRecord ;

    void initRecs() ;
    static bool comp(const aRecord &a, const aRecord &b) ;

public:
    QVector<aRecord> recs ;
    int effect_choose ;

    void init() ;
    void add(QString &thing, int order, QString &deadline, QString &expand) ;
    void remove(int order) ;
    void listAll() ;
    void renewF() ;
    int size() ;
} ;

extern Records g_records ;
#endif // RECORDS_H
