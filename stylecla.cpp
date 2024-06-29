#include "stylecla.h"

styleCla::styleCla()
{

}

QString styleCla::getButtonStyle(){
    return "QPushButton { \n"
           "    background-color: #5CD0B5; \n"
           "    border: none; \n"
           "    color: white; \n"
           "    padding: 10px 15px; \n"
           "    text-align: center; \n"
           "    text-decoration: none; \n"
           "    display: inline-block; \n"
           "    font-family: 楷体;      \n"
           "    font-size: 14px; \n"
           "    margin: 4px 2px; \n"
           "    cursor: pointer; \n"
           "} \n"
           "QPushButton:hover { \n"
           "    background-color: #47E0BC; \n"
           "}";
}

QString styleCla::getQLabelFont(){
    return "QLabel { \n"
           "    font-family: 楷体; \n"
           "    font-size: 15px; \n"
           "}";
}
