/**
 * @file wettertafel.h
 * @author BBB
 * @brief 
 * @version 1.0
 * @date 22 Nov 1 Okt 2021
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _wettertafel_h
#define _wettertafel_h
//#include <Arduino.h>
#ifdef SERVO
#include <Servo.h>
int Stellen(Servo servo, int alt,int winkel,const int verzgrg=1);
#endif //SERVO
#define LED_EIN 0
#define LED_AUS 1
double dmap(double in, double in_min, double in_max, double out_min, double out_max);
void AnzeigenD(int Druck);
void AnzeigenF(int Feuchte);
void AnzeigenT(float Temp);
void AnzeigenW(float Wind);
void flip();
void schlafen();
#endif // _wettertafel_h
