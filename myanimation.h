#ifndef MYANIMATION_H
#define MYANIMATION_H

#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QPauseAnimation>
#include <QPushButton>
class myAnimation
{
public:
    myAnimation();

    QPauseAnimation * pauseAnimation = new QPauseAnimation(2000);
    QPropertyAnimation * animation_up = new QPropertyAnimation;
    QPropertyAnimation * animation_down = new QPropertyAnimation;
    QSequentialAnimationGroup * moveGrop = new QSequentialAnimationGroup;

    int btn_x;
    int btn_y;
    bool isClick = false;
    void popUpButton(QPushButton * , QString , int);
};

#endif // MYANIMATION_H
