#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QCoreApplication>
#include <QMainWindow>
#include <QCloseEvent>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QFont>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QMenuBar>
#include <QLineEdit>
#include <QString>
#include <QSizePolicy>
#include <QListWidget>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QFileDialog>
#include "addtopicwindow.h"
#include "fileop.h"
#include "stylecla.h"
#include "myanimation.h"
#define maxQuestionNumber 1000

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void printMe();

private:
    void closeEvent(QCloseEvent *event) override;
    Ui::MainWindow *ui;
    fileOP * fp = new fileOP;
    myAnimation * m_animation = new myAnimation;

    addTopicWindow * addWindow = new addTopicWindow;

    // Storage question
    struct Question{
        QString question;
        QString optionA;
        QString optionB;
        QString optionC;
        QString optionD;
        QString coorrectAnswer;
        QString parse;
    };
    Question questions[maxQuestionNumber];

    // All QPushButton;
    QPushButton * options_A = new QPushButton;
    QPushButton * options_B = new QPushButton;
    QPushButton * options_C = new QPushButton;
    QPushButton * options_D = new QPushButton;
    QPushButton * deleteFindAreaBtn = new QPushButton;
    QPushButton * nextBtn = new QPushButton;
    QPushButton * chooeseFileBtn = new QPushButton;
    QPushButton * pUpBtn = new QPushButton;


    QVector<int> searchResultArr;

    QWidget *Btns = new QWidget;
    QScrollArea *scrollArea = new QScrollArea;

    QLabel * countLabel;
    QLabel * topicLabel;
    QLabel * totalLabel;
    QLabel * parseLabel = new QLabel;
    QLineEdit * searchBox = new QLineEdit;
    QTimer * timer = new QTimer;


    // All Varb QString And Int;
    QString topicName;
    QString stringHead;
    QString stringTail;
    QString cancleString;
    QString filePath;

    int topicCount;
    int questionCount = 0;
    int displayNum = 0;
    int chooeseStatus = 0;
    bool queryJudgment = false;


    // All Function;
    void keyPressEvent(QKeyEvent *event) override;
    int readInfo();
    void showWidget();
    int readQuestion(QString fileName , Question questions[maxQuestionNumber]);
    int deleteQuestion();
    void next(int);
    void pressBtn_A();
    void pressBtn_B();
    void pressBtn_C();
    void pressBtn_D();
    void displayText();
    void queryString(QString);
    void showAddTopicWindow();
    void findButtonArea();
    void hideButtonArea();
    void cycleChangeColors(QString targetString);
    void loopCancleColors();
    void getChooesedFilePath();
    void switchFile();
    void clearQuestions();
};
#endif // MAINWINDOW_H
