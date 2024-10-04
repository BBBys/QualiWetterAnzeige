/**
 * @file Servo.cpp
 * @brief alle Servo-Routinen
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
<<<<<<< Updated upstream
 * @version 1.1
 * @date 16 Jan 2022  16 Dez 21 Nov 26 Okt 30 19 Sep 2021
=======
 * @version 2.1
 * @date 18 17 15 9 Aug 25 Feb 16 Jan 2022  16 Dez 21 Nov 26 Okt 30 19 Sep 2021
>>>>>>> Stashed changes
 * 
 * @copyright Copyright (c) 2021-2022 B. Borys
 * 
 */
#include "wettertafel.h"
#ifdef SERVO
/**
 * @brief stellt Servo auf Winkel, beschränkt auf 0...180
 * 
 * @param Servo, Winkel, neuer Winkel, Verzögerung
 */
int Stellen(Servo Zeiger, int ist,int winkel, const int DELAY)
{
    int ziel;
    ziel = max(min(winkel, 180), 0);
#ifndef NDEBUG
    Serial.print("Anzeigen Winkel: ist=");
    Serial.println(ist);
    Serial.print("................Ziel=");
    Serial.println(ziel);
    //const int DELAY = 30;
#else
    //const int DELAY = 17;
#endif
if (DELAY>0)
{
    for (uint8 i = 0; i < 180; i++)
    {
        flip();
        delay(DELAY);
        if (ziel > ist)
            ist++;
        else if (ziel < ist)
            ist--;
        else
            break;
        Zeiger.write(ist);
    }
}
    Zeiger.write(ziel);
#ifndef NDEBUG
    Serial.println("Ziel erreicht");
#endif
    digitalWrite(LED_BUILTIN, LED_AUS); //aus
    return ziel;
}
<<<<<<< Updated upstream
=======
#else   //SERVO
#include <Adafruit_PWMServoDriver.h>
// called this way, it uses the default address 0x40
extern Adafruit_PWMServoDriver pwm;
/**
 * @brief stellt Servo über Multiplexer PCA9685 auf Winkel, beschränkt auf 0...180
 *
 * @param Adresse des Servo 
 * @param Winkel
 * @param neuer Winkel
 * @param Verzögerung 
 */
int Stellen(int Zeiger, int ist, int winkel, const int DELAY)
{
    int ziel;
    int stellwert;
    ziel = max(min(winkel, 180), 0);
#ifndef NDEBUG
    Serial.print("Anzeigen Winkel: ist=");
    Serial.println(ist);
    Serial.print("              Zeiger=");
    Serial.println(Zeiger);
    Serial.print("................Ziel=");
    Serial.println(ziel);
    // const int DELAY = 30;
#else
    // const int DELAY = 17;
#endif
    // digitalWrite(DISABLE, LOW);
    // delay(500);
    pwm.wakeup();
    if (DELAY > 0)
    {
        for (uint8 i = 0; i < 180; i++)
        {
            flip();
            delay(DELAY);
            if (ziel > ist)
                ist++;
            else if (ziel < ist)
                ist--;
            else
                break;
            stellwert = dmap(ist, 0, 180, SERVOMIN, SERVOMAX);
            pwm.setPin(Zeiger, stellwert);
        }
    }
    digitalWrite(LED_BUILTIN, LED_EIN); // ein
    stellwert = dmap(ziel, 0, 180, SERVOMIN, SERVOMAX);
    pwm.setPin(Zeiger, stellwert);
DbgsOut("Ziel erreicht");
    digitalWrite(LED_BUILTIN, LED_AUS); // aus
    // delay(500);
    // digitalWrite(DISABLE, HIGH);
    pwm.sleep();
    return stellwert;
}
>>>>>>> Stashed changes
#endif
