#ifndef FILEOP_H
#define FILEOP_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>


class fileOP
{
public:
    fileOP();
    int getSaveFileInformation();
    QString getTopicName();
    int getTopicCount();
    int updataSaveFile(QString , QString);
    int writeTopicFile(QString , QString , QString , QString , QString , QString , QString , QString);
    int deleteFileLine(int , QString);
    int isFileEmpty(QString filePath);
    int writeContent(QString fileName , QString writeString);
    QString readFilePath();

    QString fpTopicName;
    int fpTopicCount;

};

#endif // FILEOP_H
