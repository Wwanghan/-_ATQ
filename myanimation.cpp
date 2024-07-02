#include "myanimation.h"

myAnimation::myAnimation()
{
}

void myAnimation::popUpButton(QPushButton * btn , QString content , int speed){

//    if (isShow == 1) {
//        qDebug() << "isShow == 1 , so , current show failed";
//        return;
//    }
//    isShow = 1;
    btn->setText(content);
    btn->adjustSize();

    btn_x = btn->geometry().x();
    btn_y = btn->geometry().y();

    animation_down->setTargetObject(btn);
    animation_down->setPropertyName("geometry");
    animation_down->setDuration(speed);
    animation_down->setStartValue(QRect(btn_x , btn_y , btn->width() , btn->height()));
    animation_down->setEndValue(QRect(btn_x , btn_y + 80 , btn->width() , btn->height()));
    btn_y += 80;

    animation_up->setTargetObject(btn);
    animation_up->setPropertyName("geometry");
    animation_up->setDuration(speed);
    animation_up->setStartValue(QRect(btn_x , btn_y , btn->width() , btn->height()));
    animation_up->setEndValue(QRect(btn_x , btn_y - 80, btn->width() , btn->height()));
    btn_y -= 80;

    moveGrop->addAnimation(animation_down);
    moveGrop->addAnimation(pauseAnimation);
    moveGrop->addAnimation(animation_up);
    moveGrop->start();
}


