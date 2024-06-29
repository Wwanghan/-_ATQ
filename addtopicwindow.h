#ifndef ADDTOPICWINDOW_H
#define ADDTOPICWINDOW_H


#include <QMainWindow>
#include <QLineEdit>
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include "fileop.h"
#include <QKeyEvent>
#include <QVector>
#include <QMessageBox>

class addTopicWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit addTopicWindow(QWidget *parent = nullptr);
    fileOP * fp = new fileOP;
//    QLineEdit * inputTopic = nullptr;
//    QLineEdit * inputChooese_A = nullptr;
//    QLineEdit * inputChooese_B = nullptr;
//    QLineEdit * inputChooese_C = nullptr;
//    QLineEdit * inputChooese_D = nullptr;
    void keyPressEvent(QKeyEvent *event);
    QLineEdit * inputTopic = new QLineEdit;
//    QPushButton * submitButton = new QPushButton;

    QLineEdit * referenceAnswerBox = new QLineEdit;
    QLineEdit * inputChooese_A = new QLineEdit;
    QLineEdit * inputChooese_B = new QLineEdit;
    QLineEdit * inputChooese_C = new QLineEdit;
    QLineEdit * inputChooese_D = new QLineEdit;
    QLineEdit * chooeseBox = new QLineEdit;

    void clickSubmit();
    void exitBtn();

    QVector<QLineEdit*> lineEidts;
    int focusNumber = 0;
    int addCount = 0;

signals:
    void exitWindow(int);
};


#endif // ADDTOPICWINDOW_H
