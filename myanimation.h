#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QPauseAnimation>
#include <QPushButton>
#include <QDebug>
class myAnimation
{
public:
    myAnimation();
//    int isShow = 0;
    QPauseAnimation * pauseAnimation = new QPauseAnimation(900);
    QPropertyAnimation * animation_up = new QPropertyAnimation;
    QPropertyAnimation * animation_down = new QPropertyAnimation;
    QSequentialAnimationGroup * moveGrop = new QSequentialAnimationGroup;

    int btn_x;
    int btn_y;
    bool isClick = false;
    void popUpButton(QPushButton * , QString , int);
};
#endif // MYANIMATION_H
