/**
 * @file Servo.cpp
 * @brief alle Servo-Routinen
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @version 1.1
 * @date 16 Jan 2022  16 Dez 21 Nov 26 Okt 30 19 Sep 2021
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
#endif
