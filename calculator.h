/*
============================================================================
Name : calculator.h
Author : Lucas Herrmann, Maurizio Härtel, Michael Zeising
Version : 1.0
Description : Calculator for complex numbers
============================================================================
*/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

struct complex_number {
    float real_num;
    float im_num;
};


QT_BEGIN_NAMESPACE
namespace Ui { class calculator; }
QT_END_NAMESPACE

class calculator : public QMainWindow
{
    Q_OBJECT

public:
    calculator(QWidget *parent = nullptr);
    ~calculator();

private slots:
    void standard_input();
    void standard_output(complex_number complex_input);
    void insert_text (QString output);
    float round(float input);
    float argument(complex_number input);
    float angle(complex_number input);
    void on_plus_button_released();
    void on_minus_button_released();
    void on_ans_to_A_button_released();
    void on_multiply_button_released();
    void on_division_button_released();
    void on_Betrag_button_released();
    void on_argument_button_released();
    void on_euler_button_released();
    void on_trig_button_released();
    void on_ln_button_released();
    void on_power_button_released();


public:
    Ui::calculator *ui;
};
#endif // CALCULATOR_H
