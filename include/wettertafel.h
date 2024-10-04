/**
 * @file wettertafel.h
 * @author BBB
 * @brief 
<<<<<<< Updated upstream
 * @version 1.0
 * @date 22 Nov 1 Okt 2021
=======
 * @version 2.1
 * @date 18 17 Aug 25 Feb 2022 22 Nov 1 Okt 2021
>>>>>>> Stashed changes
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef _wettertafel_h
#define _wettertafel_h
//#include <Arduino.h>
#ifdef SERVO
#include <Servo.h>
<<<<<<< Updated upstream
int Stellen(Servo servo, int alt,int winkel,const int verzgrg=1);
#endif //SERVO
=======
int Stellen(Servo servo, int alt, int winkel, const int verzgrg = 1);
#else   //SERVO
// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!
// Gängig ist ein 50 - Hz - Signal(20 ms Periodenlänge), welches zwischen 500 Mikrosekunden(linker Anschlag, 0 Grad) und
// 2500 Mikrosekunden(rechter Anschlag, 180 Grad) auf High - Pegel und den Rest der Periodenlänge auf Low - Pegel ist.
// AZ-Delivery MG995 Guide
// 20 ms = 4095
// 0,5 ms = 103
// 2,5 ms = 511
#define SERVOMIN 103    // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 511    // This is the 'maximum' pulse length count (out of 4096)
#define USMIN 500       // This is the rounded 'minimum' microsecond length based on the minimum pulse of 150
#define USMAX 2500      // This is the rounded 'maximum' microsecond length based on the maximum pulse of 600
#define SERVO_FREQ 50.0 // Analog servos run at ~50 Hz updates
int Stellen(int servoadresse, int alt, int winkel, const int verzgrg = 1);
#endif // SERVO
>>>>>>> Stashed changes
#define LED_EIN 0
#define LED_AUS 1
double dmap(double in, double in_min, double in_max, double out_min, double out_max);
void AnzeigenD(int Druck);
void AnzeigenF(int Feuchte);
void AnzeigenT(float Temp);
void AnzeigenW(float Wind);
void flip();
void schlafen();
#define ZeigerT 15
#define ZeigerF 13
#define ZeigerD 7
#define ZeigerW 9
#define ZeigerM 11

#endif // _wettertafel_h
