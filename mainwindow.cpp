#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug() << "here";
    if (fp->isFileEmpty("filePath") == 0){
        qDebug() << "is Empty = " << fp->isFileEmpty("filePath");
        chooeseFileBtn->setParent(this);
        chooeseFileBtn->setText("打开文件");
        chooeseFileBtn->setGeometry(100 , 200 , 100 , 50);
        connect(chooeseFileBtn , &QPushButton::clicked , this , &MainWindow::getChooesedFilePath);
    }else{
        fp -> getSaveFileInformation();
        topicName = fp -> getTopicName();
        topicCount = fp -> getTopicCount();
        readQuestion(fp->readFilePath() , questions);  // load questions And count question number;
        showWidget();
    }


    this -> setFixedSize(1050 , 420);
    connect(timer , &QTimer::timeout , this , &MainWindow::displayText);
    parseLabel -> setParent(this);
    parseLabel -> setWordWrap(true);
    parseLabel->setStyleSheet(styleCla::getQLabelFont());
    parseLabel -> setGeometry(150 , 340 , 850 , 75);
    QFont parseFont("微软雅黑" , 10);
    parseLabel -> setFont(parseFont);

    QMenuBar * MenuBar = menuBar();
    setMenuBar(MenuBar);
    QMenu * functionMenu = MenuBar -> addMenu("功能");
    QAction * switchFile = functionMenu -> addAction("切换文件");
    QAction * addQuestion = functionMenu -> addAction("录入题目");
    QAction * removeQuestion = functionMenu -> addAction("删除题目");
    QAction * previousQue = functionMenu -> addAction("上一题 k");
    QAction * nextQue = functionMenu -> addAction("下一题 j");

    pUpBtn->setParent(this);
    pUpBtn->setGeometry(1050 , 150 , 150 , 50);


    deleteFindAreaBtn->setParent(this);
    deleteFindAreaBtn->setText("x");
    deleteFindAreaBtn->setGeometry(990 , 155 , 20 , 20);
    deleteFindAreaBtn->hide();

    connect(switchFile , &QAction::triggered , this , &MainWindow::switchFile);
    connect(deleteFindAreaBtn , &QPushButton::clicked , this , &MainWindow::hideButtonArea);
    connect(addQuestion , &QAction::triggered , this , &MainWindow::showAddTopicWindow);
    connect(removeQuestion , &QAction::triggered , this , &MainWindow::deleteQuestion);
    connect(previousQue , &QAction::triggered , std::bind(&MainWindow::next , this , -2));
    connect(nextQue , &QAction::triggered , std::bind(&MainWindow::next , this , -1));
    connect(addWindow , &addTopicWindow::exitWindow, [=](int returnAddNumber){
        addWindow -> hide();
        this -> show();
        hideButtonArea();
        questionCount = 0;
        readQuestion(fp->readFilePath() , questions);
        totalLabel->setText("当前题库共有" +  QString::number(questionCount) + "题");
    });

//    functionMenu -> addAction("录入套题");
//    functionMenu -> addAction("删除当前套题");
//    functionMenu -> addAction("删除当前题目");
//    functionMenu -> addAction("查看错题");
//    functionMenu -> addAction("帮助文档 F12");

//    QLineEdit * searchBox = new QLineEdit(this);
//    inputBox -> setStyleSheet("background-color: transparent;");
//    searchBox -> setGeometry(680 , 35 , 355 , 40);

    searchBox -> setParent(this);
    searchBox -> setGeometry(680 , 35 , 355 , 40);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showWidget(){
    totalLabel = new QLabel("当前题库共有" +  QString::number(questionCount) + "题", this);
    totalLabel -> setGeometry(10 , 20 , 180 , 50);
    totalLabel->setStyleSheet(styleCla::getQLabelFont());

    countLabel = new QLabel("第" + QString::number(topicCount) + "题" , this);
    countLabel -> setGeometry(40 , 50 , 50 , 50);
    countLabel->setStyleSheet(styleCla::getQLabelFont());

    topicLabel = new QLabel(questions[topicCount - 1].question + " ?" , this);
    topicLabel->setWordWrap(true);
    topicLabel -> setGeometry(150 , 80 , 800 , 50);
    topicLabel->setStyleSheet(styleCla::getQLabelFont());

    options_A->setParent(this);
    options_A->setText(questions[topicCount - 1].optionA);
    options_A->setStyleSheet(styleCla::getButtonStyle());
    options_A->adjustSize();
    options_A -> move(150 , 150);
    connect(options_A , &QPushButton::clicked , this , &MainWindow::pressBtn_A);

    options_B->setParent(this);
    options_B->setText(questions[topicCount - 1].optionB);
    options_B->setStyleSheet(styleCla::getButtonStyle());
    options_B->adjustSize();
    options_B -> move(150 , 200);
    connect(options_B , &QPushButton::clicked , this , &MainWindow::pressBtn_B);

    options_C->setParent(this);
    options_C->setText(questions[topicCount - 1].optionC);
    options_C->setStyleSheet(styleCla::getButtonStyle());
    options_C->adjustSize();
    options_C -> move(150 , 250);
    connect(options_C , &QPushButton::clicked , this , &MainWindow::pressBtn_C);

    options_D->setParent(this);
    options_D->setText(questions[topicCount - 1].optionD);
    options_D->setStyleSheet(styleCla::getButtonStyle());
    options_D->adjustSize();
    options_D -> move(150 , 300);
    connect(options_D , &QPushButton::clicked , this , &MainWindow::pressBtn_D);
}

void MainWindow::next(int status){
    m_animation->popUpButton(pUpBtn , "无法使用该功能" , 300);return;
    timer -> stop();
    parseLabel -> hide();
    if (status == -1){
        if (topicCount + 1 > questionCount){
            QMessageBox::information(this , "info" , "这已经是最后一题了");
//            m_animation->popUpButton(pUpBtn , "已经是最后一题了" , 300);
            return;
        }
        topicCount += 1;
    }
    else if (status == -2){
        if (topicCount - 1 == 0){
            QMessageBox::information(this , "info" , "这已经是第一题了");
            return;
        }
        topicCount -= 1;
    }
    else if (status == -3){
        // Nothing
    }
    else{
        topicCount = status;
    }

    totalLabel->setText("当前题库共有" +  QString::number(questionCount) + "题");
    countLabel->setText("第" + QString::number(topicCount) + "题");
    topicLabel->setText(questions[topicCount -1].question + " ?");

    options_A -> setText(questions[topicCount - 1].optionA);
    options_A->adjustSize();

    options_B -> setText(questions[topicCount - 1].optionB);
    options_B->adjustSize();

    options_C -> setText(questions[topicCount - 1].optionC);
    options_C->adjustSize();

    options_D -> setText(questions[topicCount - 1].optionD);
    options_D->adjustSize();

}

int MainWindow::readQuestion(QString filePath , MainWindow::Question questions[maxQuestionNumber]){
    QFile file(filePath);


    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            file.close();
            qDebug() << "无法打开文件：" << file.errorString();
            return -1;
        }

    while (!file.atEnd())
        {
            QString line = file.readLine();

            QStringList splitString = line.split(":::");
            if (splitString.size() == 7){
                questions[questionCount].question = splitString[0];
                questions[questionCount].optionA = splitString[1];
                questions[questionCount].optionB = splitString[2];
                questions[questionCount].optionC = splitString[3];
                questions[questionCount].optionD = splitString[4];
                questions[questionCount].coorrectAnswer = splitString[5];
                questions[questionCount].parse = splitString[6];
                questionCount += 1;
            }
        }
    file.close();
    return 0;
}

void MainWindow::findButtonArea() {
    Btns->setParent(this);
    Btns->setFixedSize(240, 240);
    Btns->move(780 , 170);

    scrollArea->setParent(Btns);
    scrollArea->setGeometry(10, 10, 220, 220);
    scrollArea->setWidgetResizable(true);

    if (scrollArea->widget() != nullptr) {
        QWidget *existingWidget = scrollArea->takeWidget();
        delete existingWidget;
    }

    QWidget *container = new QWidget(scrollArea);
    QVBoxLayout *containerLayout = new QVBoxLayout(container);

    QHBoxLayout *rowLayout = new QHBoxLayout();
    for (int i = 0; i < searchResultArr.size(); ++i) {
        QPushButton *button = new QPushButton(QString::number(searchResultArr.at(i)));
        button->setMinimumSize(33, 20);
        connect(button , &QPushButton::clicked , this , [=](){next(searchResultArr.at(i));});
        rowLayout->addWidget(button);

        if ((i + 1) % 4 == 0 || i == searchResultArr.size() - 1) {
             containerLayout->addLayout(rowLayout);
             rowLayout = new QHBoxLayout();
         }
    }

    int remainingButtons = 4 - containerLayout->count() % 4;
    for (int i = 0; i < remainingButtons; ++i) {
        QWidget *spacer = new QWidget(container);
        spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        rowLayout->addWidget(spacer);
    }
    containerLayout->addLayout(rowLayout);

    scrollArea->setWidget(container);
    scrollArea->setMinimumSize(220, 220);

    QVBoxLayout *layout = new QVBoxLayout(Btns);
    layout->addWidget(scrollArea);

    Btns->setLayout(layout);
    Btns->show();
    scrollArea->show();
    deleteFindAreaBtn->show();
}

void MainWindow::hideButtonArea(){
    scrollArea->hide();
    deleteFindAreaBtn->hide();
    loopCancleColors();
    queryJudgment = false;
}

int MainWindow::deleteQuestion(){
    m_animation->popUpButton(pUpBtn , "无法使用该功能" , 300);return -1;
    hideButtonArea();
    int removeLine = topicCount;
    for (int i = topicCount - 1; i < questionCount - 1; ++i) {
        questions[i] = questions[i + 1];
    }

    if (topicCount == questionCount){
        topicCount -= 1;
    }
    questionCount -= 1;

    totalLabel->setText("当前题库共有" + QString::number(questionCount) + "题");
    next(-3);
    fp -> deleteFileLine(removeLine - 1 , topicName);
}

void MainWindow::pressBtn_A(){
    if (questions[topicCount -1].coorrectAnswer == "A"){
        displayNum = 0;
        chooeseStatus = 1;
        timer -> start(50);
    }else{
        displayNum = 0;
        chooeseStatus = 0;
        timer -> start(50);
    }
}

void MainWindow::pressBtn_B(){
    if (questions[topicCount -1].coorrectAnswer == "B"){
        displayNum = 0;
        chooeseStatus = 1;
        timer -> start(50);
    }else{
        displayNum = 0;
        chooeseStatus = 0;
        timer -> start(50);
    }
}

void MainWindow::pressBtn_C(){
    if (questions[topicCount -1].coorrectAnswer == "C"){
        displayNum = 0;
        chooeseStatus = 1;
        timer -> start(50);
    }else{
        displayNum = 0;
        chooeseStatus = 0;
        timer -> start(50);
    }
}

void MainWindow::pressBtn_D(){
    if (questions[topicCount -1].coorrectAnswer == "D"){
        displayNum = 0;
        chooeseStatus = 1;
        timer -> start(50);
    }else{
        displayNum = 0;
        chooeseStatus = 0;
        timer -> start(50);
    }
}

void MainWindow::displayText(){
    QString string;
    if (chooeseStatus == 1){
        string = questions[topicCount - 1].parse;
    }else{
        string = "回答错误";
    }
    if (displayNum < string.length()){
        parseLabel -> setText(string.left(displayNum += 1));
        parseLabel -> show();
    }else{
        timer -> stop();
    }
}

void MainWindow::queryString(QString queryTag){
    int i = 0;
    if (queryJudgment){
        loopCancleColors();
    }
    searchResultArr.clear();
    for (i; i < questionCount; i++){
        if (questions[i].question.contains(queryTag)){
            searchResultArr.append(i + 1);
        }
    }
    cycleChangeColors(queryTag);
    if (!queryJudgment){queryJudgment = true;}
}

void MainWindow::cycleChangeColors(QString targetStr){
    for (int j = 0; j < searchResultArr.size(); j++){
        QStringList list = questions[searchResultArr[j] - 1].question.split(targetStr);
        stringHead = list[0] + "<font color='red'>" + targetStr;
        stringTail = "</font>" + list[1];
        questions[searchResultArr[j] - 1].question = stringHead + stringTail;
    }
    if (searchResultArr.contains(topicCount)){
        next(-3);
    }
}

void MainWindow::loopCancleColors(){
    for (int j = 0; j < searchResultArr.size(); j++){
        QStringList splitHead = questions[searchResultArr[j] - 1].question.split("<font color='red'>");
        QStringList splitTail = questions[searchResultArr[j] - 1].question.split("</font>");
        questions[searchResultArr[j] - 1].question = splitHead[0] + splitHead[1].split("</font>")[0] + splitTail.last();
    }
    if (searchResultArr.contains(topicCount)){
        next(-3);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if (event -> key() == Qt::Key_J){
        next(-1);
    }
    if (event -> key() == Qt::Key_K){
        next(-2);
    }
    if (event -> key() == Qt::Key_Return){
        m_animation->popUpButton(pUpBtn , "无法使用该功能" , 300);return;
        if (searchBox->text() == ""){
            return;
        }
        QStringList split = searchBox->text().split(" ");
        if (split[0] == "query"){
            queryString(split[1]);
            findButtonArea();
            searchBox -> setText("");
        }
    }
}

void MainWindow::showAddTopicWindow(){
    m_animation->popUpButton(pUpBtn , "无法使用该功能" , 300);return;
    this -> hide();
    addWindow -> show();
}

void MainWindow::closeEvent(QCloseEvent *event) {
    fp -> updataSaveFile(topicName , QString::number(topicCount));
    QMainWindow::closeEvent(event);
}

void MainWindow::getChooesedFilePath(){
    chooeseFileBtn->hide();
    QString getFilePath = QFileDialog::getOpenFileName(this , "Open File" , "/home/toad" , "(*.txt)");
    filePath = getFilePath;
    fp->writeContent("filePath" , filePath);
    QStringList list = filePath.split("/");
    topicName = list.last().split(".")[0];
    topicCount = 1;
    fp->writeContent("save" , topicName + "." + topicCount);
    readQuestion(filePath , questions);
    showWidget();
    totalLabel->show();
    countLabel->show();
    topicLabel->show();
    options_A->show();
    options_B->show();
    options_C->show();
    options_D->show();
}

void MainWindow::switchFile(){
//    if (fp->isFileEmpty("filePath") == 0){QMessageBox::information(this , "info" , "您当前并未选择文件，无法使用该功能");return;}
    m_animation->popUpButton(pUpBtn , "无法使用该功能" , 300);return;
    clearQuestions();
    QString switchFilePath = QFileDialog::getOpenFileName(this , "Open File" , "/home/toad" , "(*.txt)");
    QStringList splitSwitchPath = switchFilePath.split("/");
    fp->writeContent("save" , splitSwitchPath.last().split(".")[0] + ".1");
    fp->writeContent("filePath" , switchFilePath);
    topicName = splitSwitchPath.last().split(".")[0];
    topicCount = 1;
    readQuestion(switchFilePath , questions);
    next(-3);
}

void MainWindow::clearQuestions(){
    questionCount = 0;
    topicCount = 1;
    for (int i = 0; i < maxQuestionNumber; ++i) {
        questions[i].question.clear();
        questions[i].optionA.clear();
        questions[i].optionB.clear();
        questions[i].optionC.clear();
        questions[i].optionD.clear();
        questions[i].coorrectAnswer.clear();
        questions[i].parse.clear();
    }
}

