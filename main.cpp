#include "mymemo.h"
#include <QApplication>
#include "readlist.h"
#include "Records.h"
#include <QFontDatabase>
#include "alert.h"
#include <QTextCodec>
#include <QFile>
#include <QTextStream>
#include "timeremainder.h"
#include <QSettings>
#include <QDir>
#include <QSharedMemory>

#define AUTO_RUN_NATI "HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"

void readSettings(int &eff_choose, int &alerm_choose) ;
int setEfficacy(int choose) ;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv) ;

    // get current work dir
    QString curDir = QDir::currentPath() ;
    // auto run
    QString application_name = QApplication::applicationName() ;
    QSettings settings_nati(AUTO_RUN_NATI, QSettings::NativeFormat) ;

    QString application_path = QApplication::applicationFilePath() ;
    settings_nati.setValue(application_name, application_path.replace("/", "\\")) ;
    // add this program to the windows registrar

    // define encode method
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);
    QString application_dir_path = QApplication::applicationDirPath() ;

    QDir::setCurrent(application_dir_path) ;

    QString fontA = QStringLiteral("./fonts/mainFont.ttf") ;
    QString fontB = QStringLiteral("./fonts/setofont.ttf") ;
    QString fontC = QStringLiteral("./fonts/timemachine-wa.ttf") ;

    int fontA_check = QFontDatabase::addApplicationFont(fontA) ;
    int fontB_check = QFontDatabase::addApplicationFont(fontB) ;
    int fontC_check = QFontDatabase::addApplicationFont(fontC) ;

    int alerm_choose = 0 ;
    readSettings(g_records.effect_choose, alerm_choose) ; // read settings file

    MyMemo w(setEfficacy(g_records.effect_choose)) ;

    QSharedMemory shared("MyMemo");
    if(shared.attach())
    {
        w.showMultipleExec_alert(true) ;
        return 0 ;
    }

    shared.create(1);

    w.resize(820, 510) ;

    if (curDir != application_dir_path)
    {
        w.hide();
    }
    else
    {
        w.show() ;
    }

    timeRemainder.alermChoose(alerm_choose) ;

    if (fontA_check == -1 ||
        fontB_check == -1 ||
        fontC_check == -1)
    {
        Alert errMsg ;
        errMsg.setWindowTitle("Error!") ;
        errMsg.setModal(true) ;
        QString msg = "Error:(0x03) Fonts missing, this may cause incomplete display." ;
        errMsg.setErrMsg(msg, 0) ;
        errMsg.exec() ;
    }

    ReadList myThing ;
    myThing.readF() ;

    g_records.init() ;

    return a.exec();
}

void readSettings(int &eff_choose, int &alerm_choose)
{
    QFile *file = new QFile ;
    file->setFileName("./notes/settings.bin") ;
    bool ok = file->open(QIODevice::ReadOnly) ;

    if (ok)
    {
        QString temp ;
        QTextStream in(file) ;
        temp = in.readAll() ;

        QList<QString> data = temp.split(",") ;
        eff_choose = data[0].toUInt() ;
        alerm_choose = data[1].toUInt() ;

        file->close() ;
        delete file ;
    }
    else
    {
        Alert errMsg ;
        errMsg.setWindowTitle("Error!") ;
        errMsg.setModal(true) ;
        QString msg = "Error:(0x00) missing settings.bin, can not load file." ;
        errMsg.setErrMsg(msg, 0) ;
        errMsg.exec() ;
    }

}

int setEfficacy(int choose)
{
    if (choose == 0) // high (default)
        return 2000 ;
    else if (choose == 1) // mid
        return 6000 ;
    else if (choose == 2) // low
        return 15000 ;
    else // input not in the range
        return 6000 ;
}
