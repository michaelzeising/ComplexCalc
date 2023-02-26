/*
============================================================================
Name : calculator.cpp
Author : Lucas Herrmann, Maurizio Härtel, Michael Zeising
Version : 1.0
Description : Calculator for complex numbers
============================================================================
*/

#include "calculator.h"
#include "./ui_calculator.h"
#include <cmath>
#include <QDebug>

float value_A, argument_A;
QString plus = "+", times_j = "*i", q_real_result, q_im_result;
complex_number number_A, number_B, complex_result;

//setup
calculator::calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::calculator)
{
    ui->setupUi(this);
}

// close window when x is pressed
calculator::~calculator()
{
    delete ui;
}


//INPUT AND OUTPUT
// The input function gets the complex numbers from the upper LineEdits.
void calculator::standard_input()
{
    number_A.real_num = ui->real_A->text().toFloat(); // convert the input QStrings from the LineEdits to float and storing them to the number A and B structs
    number_B.real_num = ui->real_B->text().toFloat();
    number_A.im_num = ui->im_A->text().toFloat();
    number_B.im_num = ui->im_B->text().toFloat();
}

// Thw output function displays a complex number in the result-LineEdit.
void calculator::standard_output (complex_number complex_input)
{
    QString output;
    q_real_result = QString::number(round(complex_input.real_num)); //transform input to QString
    q_im_result = QString::number(round(complex_input.im_num));
    if (complex_input.im_num < 0) //displaying the input based on the sign of the imaginary part
    {
        output = q_real_result + q_im_result + times_j;
    }
    else if (complex_input.im_num == 0)
    {
        output = q_real_result;
    }
    else
    {
        output = q_real_result + plus + q_im_result + times_j;
    }
    ui->result_le->setText(output);
}

// The as_QString function returns a given float number as a QString.
QString as_QString (float input)
{
    QString output;
    output = QString::number(input); //transformation of input to QString
    return output;
}


// The insert_text function prints a QString in the result LineEdit.
void calculator::insert_text (QString output)
{
    ui->result_le->insert(output);
}


// MATH FUNCTIONS:
// The round fuction rounds a float number to the decimal place that is stored in the dec_place variable.
float calculator::round(float input)
{
    int dec_place = 3;
    return floor(input * pow(10, dec_place) + 0.5) * pow(10, -dec_place);
}

//The argument fuction returns the argument of a given complex number.
float calculator::argument(complex_number input)
{
    float result = atan2(input.im_num, input.real_num);
    return result;
}

// The angle function returns the angle of a given complex number.
float calculator::angle(complex_number input)
{
    float result = argument(input) / 0.0174533;
    return result;
}

//The value_of function returns the absolute value of a complex number.
float value_of (complex_number input)
{
    float output = sqrt(pow(input.real_num,2)+pow(input.im_num,2));
    return output;
}


//UI-BUTTON FUNCTIONS
//This function calculates and returns the sum of two complex numbers and prints it in the result LineEdit.
void calculator::on_plus_button_released()
{
    standard_input();
    complex_result.real_num = number_A.real_num + number_B.real_num;
    complex_result.im_num = number_A.im_num + number_B.im_num;
    standard_output(complex_result);
}

//This function calculates and returns the difference of two complex numbers and prints it in the result LineEdit.
void calculator::on_minus_button_released()
{
    standard_input();
    complex_result.real_num = number_A.real_num - number_B.real_num;
    complex_result.im_num = number_A.im_num - number_B.im_num;
    standard_output(complex_result);
}

// This function copies the last answer to the number A LineEdit.
void calculator::on_ans_to_A_button_released()
{
    ui->real_A->setText(q_real_result);
    ui->im_A->setText(q_im_result);
}

//This function calculates and returns the product of two complex numbers and prints it in the result LineEdit.
void calculator::on_multiply_button_released()
{
    standard_input();
    complex_result.real_num = number_A.real_num * number_B.real_num - number_A.im_num * number_B.im_num;
    complex_result.im_num = number_A.real_num * number_B.im_num + number_A.im_num * number_B.real_num;
    standard_output(complex_result);
}

//This function calculates and returns the quotient of two complex numbers and prints it in the result LineEdit.
void calculator::on_division_button_released()
{
    standard_input();
    float div = pow(number_B.real_num,2) + pow(number_B.im_num,2);
    complex_result.real_num = (number_A.real_num * number_B.real_num + number_A.im_num * number_B.im_num) / div;
    complex_result.im_num = (number_A.im_num * number_B.real_num - number_A.real_num * number_B.im_num) / div;
    standard_output(complex_result);
}

//This function calculates the absolute value of complex number A and prints it in the result LineEdit.
void calculator::on_Betrag_button_released()
{
    standard_input();
    complex_result.real_num = sqrt(pow(number_A.real_num,2)+pow(number_A.im_num,2));
    complex_result.im_num = 0;
    standard_output(complex_result);
}

//This function calculates the argument and angle of complex number A and prints it in the result LineEdit.
void calculator::on_argument_button_released()
{
    float angle_A;
    standard_input();
    angle_A = round(angle(number_A)); //calculating and rounding angle of number A
    argument_A = round(argument(number_A)); //calculating and rounding argument of number A
    ui->result_le->clear(); //printing the result to the result LineEdit
    insert_text("Radian Measure: ");
    insert_text(as_QString(argument_A));
    insert_text("; Degree Measure: ");
    insert_text(as_QString(angle_A));
    insert_text("°");
    q_real_result = as_QString(number_A.real_num); //set result variables to number A for ANS-->A
    q_im_result = as_QString(number_A.im_num);
}

//This function displays complex number A in the Euler-form in the result LineEdit.
void calculator::on_euler_button_released()
{
    standard_input();
    value_A = round(value_of(number_A)); //calculating and rounding angle of number A
    argument_A = round(argument(number_A)); //calculating and rounding argument of number A
    ui->result_le->clear(); //printing the result to the result LineEdit
    insert_text(as_QString(value_A));
    insert_text(" * e ^ (i*");
    insert_text(as_QString(argument_A));
    insert_text(")");
    q_real_result = as_QString(number_A.real_num); //set result variables to number A for ANS-->A
    q_im_result = as_QString(number_A.im_num);
}

//This function displays complex number A in the trigonometric form in the result LineEdit.
void calculator::on_trig_button_released()
{
    standard_input();
    value_A = round(value_of(number_A)); //calculating and rounding angle of number A
    argument_A = round(argument(number_A)); //calculating and rounding argument of number A
    ui->result_le->clear(); //printing the result to the result LineEdit
    insert_text(as_QString(value_A));
    insert_text(" * (cos(");
    insert_text(as_QString(argument_A));
    insert_text(") + i * sin(");
    insert_text(as_QString(argument_A));
    insert_text("))");
    q_real_result = as_QString(number_A.real_num); //set result variables to number A for ANS-->A
    q_im_result = as_QString(number_A.im_num);
}

//This function calculates the natural logarithm of complex number A and prints it in the result LineEdit.
void calculator::on_ln_button_released()
{
    standard_input();
    float ln_value_A;
    ln_value_A = value_of(number_A); //calculating absolute value of number A
    ln_value_A = round(log(ln_value_A)); //calculating natural logarithm of this value
    argument_A = round(argument(number_A)); //calculating and rounding argument of number A
    ui->result_le->clear(); //printing the result to the result LineEdit
    insert_text(as_QString(ln_value_A));
    insert_text(" + i * (");
    insert_text(as_QString(argument_A));
    insert_text(" + 2 * k * π)");
    q_real_result = as_QString(number_A.real_num); //set result variables to number A for ANS-->A
    q_im_result = as_QString(number_A.im_num);

}

//This function calculates the complex number A to the power of the real part of complex number B and prints the result in the result LineEdit.
void calculator::on_power_button_released()
{
    standard_input();
    ui->im_B->clear();
    value_A = round(pow(value_of(number_A), number_B.real_num)); //calculating absolute value of number A
    argument_A = round(number_B.real_num * argument(number_A)); //calculating and rounding argument of number A
    ui->result_le->clear(); //printing the result to the result LineEdit
    insert_text(as_QString(value_A));
    insert_text(" * (cos(");
    insert_text(as_QString(argument_A));
    insert_text(") + i * sin(");
    insert_text(as_QString(argument_A));
    insert_text("))");
    q_real_result = as_QString(number_A.real_num); //set result variables to number A for ANS-->A
    q_im_result = as_QString(number_A.im_num);
}




