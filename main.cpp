/*
============================================================================
Name : main.cpp
Author : Lucas Herrmann, Maurizio Härtel, Michael Zeising
Version : 1.0
Description : Calculator for complex numbers
============================================================================
*/

#include "calculator.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    calculator w;
    w.show();
    return a.exec();
}
