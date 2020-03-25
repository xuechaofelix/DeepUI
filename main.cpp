#include "uimain.h"

#include <QApplication>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QResource>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir tmpPath = QDir::tempPath();


    if(!tmpPath.cd("Qt")){
        tmpPath.mkdir("Qt");
        tmpPath.cd("Qt");
    }
    if(!tmpPath.cd("lib")){
        tmpPath.mkdir("lib");
        tmpPath.cd("lib");
    }
     QFileInfo info(tmpPath.absoluteFilePath("deepsymbol"));
     if(!info.isFile()){
        if(! QFile::copy(":/resources/deepsymbol",info.absoluteFilePath()))
        {
            //QMessageBox::warning(this, "Worning", "Failed to access TemporaryFile!");
            qDebug() << "Failed to access TemporaryFile!";
            return -7;
        }
     }
    /*
    QDir dir(qApp->applicationDirPath());
    if(!dir.cd("lib")){
        QMessageBox::warning(&w, "Worning", "does not have \".\\lib\" directory!");
        return -7;
    }
    QFileInfo info(dir.absoluteFilePath("epmc-qmc.jar"));
    if(!info.isFile()){
        QMessageBox::warning(&w, "Worning", "lack of \"epmc-qmc.jar\" in \"\\lib\"!");
        return -7;
    }*/

    UIMain w;
    w.show();
    return a.exec();
}
