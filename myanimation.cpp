#include "myanimation.h"

myAnimation::myAnimation()
{

}

void myAnimation::popUpButton(QPushButton * btn , QString content , int speed){
    btn->setText(content);

    if (isClick == false){
        isClick = true;
    }

    btn_x = btn->geometry().x();
    btn_y = btn->geometry().y();

    animation_down->setTargetObject(btn);
    animation_down->setPropertyName("geometry");
    animation_down->setDuration(speed);
    animation_down->setStartValue(QRect(btn_x , btn_y , btn->width() , btn->height()));
    animation_down->setEndValue(QRect(btn_x - 150 , btn_y, btn->width() , btn->height()));
    btn_x -= 150;

    animation_up->setTargetObject(btn);
    animation_up->setPropertyName("geometry");
    animation_up->setDuration(speed);
    animation_up->setStartValue(QRect(btn_x , btn_y , btn->width() , btn->height()));
    animation_up->setEndValue(QRect(btn_x + 150 , btn_y, btn->width() , btn->height()));
    btn_x += 150;

    moveGrop->addAnimation(animation_down);
    moveGrop->addAnimation(pauseAnimation);
    moveGrop->addAnimation(animation_up);
    moveGrop->start();
}
