#include "fileop.h"
#include <QDebug>

fileOP::fileOP()
{

}

QString fileOP::getTopicName(){
    return fpTopicName;
}

int fileOP::getTopicCount(){
    return fpTopicCount;
}

int fileOP::getSaveFileInformation(){
    QFile file(QCoreApplication::applicationDirPath() + "/../exam/res/save.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            file.close();
            qDebug() << "read infomation failed ha : " << file.errorString();
            return 1;
        }
    QString line = file.readLine();
    QStringList splitInfo = line.split('.');
    file.close();
    qDebug() << "[0] = " << splitInfo[0];
    if (splitInfo[0] == "nothing"){
        return 1;
    }

    bool ok;
    fpTopicName = splitInfo[0];
    fpTopicCount = splitInfo[1].replace(QChar('\n') , QString("")).toInt(&ok);
}


int fileOP::updataSaveFile(QString topicName , QString topicCount){
    QFile writeFile(QCoreApplication::applicationDirPath() + "/../exam/res/save.txt");
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Could not open file for writing";
        return 2;
    }
    QTextStream Out(&writeFile);
    Out << topicName << "." << topicCount;

    writeFile.close();
}

int fileOP::writeTopicFile(QString topicName, QString topicLabel, QString content_A, QString content_B, QString content_C, QString content_D, QString chooese, QString reference){
    QFile Addtion(QCoreApplication::applicationDirPath() + "/../exam/res/Mytopic/" + topicName + ".txt");
    if (!Addtion.open(QIODevice::Append | QIODevice::Text)) {
        qDebug() << "Failed to open file for appending:" << Addtion.errorString();
        return 3;
    }
    QString addContent = topicLabel + ":::" + content_A + ":::" + content_B + ":::" + content_C + ":::" + content_D + ":::" + chooese + ":::" + reference + "\n";
    QTextStream addStream(&Addtion);
    addStream << addContent;
}

int fileOP::deleteFileLine(int removeLine , QString fileName){
    QFile file(QCoreApplication::applicationDirPath() + "/../exam/res/Mytopic/" + fileName + ".txt");
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "无法打开文件: " << file.errorString();
        return 4;
    }

    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.append(line);
    }
    file.close();

    if (removeLine >= 0 && removeLine < lines.size()){
        lines.removeAt(removeLine);
    }
    else{
        qDebug() << "delete out of range";
        return 4;
    }

    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        qDebug() << "无法打开文件以写入: " << file.errorString();
        return 4;
    }

    QTextStream out(&file);
    foreach(const QString &line, lines) {
        out << line << "\n";
    }

    // 关闭文件
    file.close();
}

int fileOP::isFileEmpty(QString fileName){
    QFile file(QCoreApplication::applicationDirPath() + "/../exam/res/" + fileName + ".txt");

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("无法打开文件");
        return -1; // 返回-1表示无法打开文件
    }

    bool isEmpty = file.size() == 0;

    file.close();

    return isEmpty ? 0 : 1;
}

int fileOP::writeContent(QString fileName, QString writeString){
    QFile file(QCoreApplication::applicationDirPath() + "/../exam/res/" + fileName + ".txt");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate)) {
        qWarning("无法打开文件");
        return -1; // 返回false表示无法打开文件
    }

    QTextStream out(&file);
    out << writeString;
    file.close();
}

QString fileOP::readFilePath(){
    QFile file(QCoreApplication::applicationDirPath() + "/../exam/res/filePath.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QString line = file.readLine();
            file.close();
            return line.trimmed();
        }
    file.close();
    qDebug() << "read infomation failed : " << file.errorString();

}

