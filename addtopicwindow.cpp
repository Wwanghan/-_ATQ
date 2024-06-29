#include "addtopicwindow.h"

addTopicWindow::addTopicWindow(QWidget *parent) : QMainWindow(parent)
{
    setFixedSize(750 , 650);
    setWindowFlags(windowFlags() & ~Qt::WindowCloseButtonHint);
    fp -> getSaveFileInformation();
    QLabel * inputTopicLabel = new QLabel("请输入题目 :" , this);
    QLabel * inputChoose_A_Label = new QLabel("请输入选项A的内容 :" , this);
    QLabel * inputChoose_B_Label = new QLabel("请输入选项B的内容 :" , this);
    QLabel * inputChoose_C_Label = new QLabel("请输入选项C的内容 :" , this);
    QLabel * inputChoose_D_Label = new QLabel("请输入选项D的内容 :" , this);
    QLabel * answerLabel = new QLabel("请输入正确选项 :" , this);
    QLabel * referenceAnswerLabel = new QLabel("请输入参考答案 :" , this);
    QPushButton * exitBtn = new QPushButton("退出" , this);

    inputTopicLabel -> setGeometry(50 , 70 , 90 , 30);
    inputChoose_A_Label -> setGeometry(50 , 130 , 140 , 30);
    inputChoose_B_Label -> setGeometry(50 , 190 , 140 , 30);
    inputChoose_C_Label -> setGeometry(50 , 250 , 140 , 30);
    inputChoose_D_Label -> setGeometry(50 , 310 , 140 , 30);
    answerLabel -> setGeometry(50 , 370 , 140 , 30);
    referenceAnswerLabel -> setGeometry(50 , 430 , 140 , 30);

    inputTopic -> setParent(this);
    inputChooese_A -> setParent(this);
    inputChooese_B -> setParent(this);
    inputChooese_C -> setParent(this);
    inputChooese_D -> setParent(this);
    chooeseBox -> setParent(this);
    referenceAnswerBox -> setParent(this);
//    submitButton -> setParent(this);
//    submitButton -> setText("提交");
//    submitButton -> setFixedSize(100 , 30);

    inputTopic -> setGeometry(200 , 70 , 250 , 35);
    inputChooese_A -> setGeometry(200 , 130 , 250 , 35);
    inputChooese_B -> setGeometry(200 , 190 , 250 , 35);
    inputChooese_C -> setGeometry(200 , 250 , 250 , 35);
    inputChooese_D -> setGeometry(200 , 310 , 250 , 35);
    chooeseBox -> setGeometry(200 , 370 , 250 , 35);
    referenceAnswerBox -> setGeometry(200 , 430 , 350 , 35);
    exitBtn -> move(10 , 600);
//    submitButton -> move(540 , 590);


    lineEidts.append(inputTopic);
    lineEidts.append(inputChooese_A);
    lineEidts.append(inputChooese_B);
    lineEidts.append(inputChooese_C);
    lineEidts.append(inputChooese_D);
    lineEidts.append(chooeseBox);
    lineEidts.append(referenceAnswerBox);

    lineEidts[focusNumber]->setFocus();
//    connect(submitButton , &QPushButton::clicked , this , &addTopicWindow::clickSubmit);
    connect(exitBtn , &QPushButton::clicked , this , &addTopicWindow::exitBtn);


}

void addTopicWindow::clickSubmit(){
    fp -> writeTopicFile(fp -> fpTopicName , inputTopic -> text() , inputChooese_A -> text() , inputChooese_B -> text() , inputChooese_C -> text() , inputChooese_D -> text() , chooeseBox -> text() , referenceAnswerBox -> text());
    inputTopic -> clear();
    inputChooese_A -> clear();
    inputChooese_B -> clear();
    inputChooese_C -> clear();
    inputChooese_D -> clear();
    chooeseBox -> clear();
    referenceAnswerBox -> clear();
}

void addTopicWindow::exitBtn(){
    emit exitWindow(addCount);
    addCount = 0;
}

void addTopicWindow::keyPressEvent(QKeyEvent *event){
    if (event -> key() == Qt::Key_Return){
        lineEidts[focusNumber] -> clearFocus();
        focusNumber += 1;
        if (focusNumber == 7){
            clickSubmit();
            focusNumber = 0;
            addCount += 1;
            lineEidts[focusNumber] -> setFocus();
            QMessageBox::information(this , "info" , "添加成功!");
            return;
        }
        lineEidts[focusNumber] -> setFocus();
    }
}
