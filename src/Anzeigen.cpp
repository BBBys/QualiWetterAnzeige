/**
 * @file Anzeigen.cpp
 * Wetterdaten nach Umrechnung an Servo-Motoren übertragen.
 * nur bei der Temperatur ist die Abhängigkeit von der Jahreszeit statistisch signifikant (95-%-Niveau)
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @version 1.1
 * @date 16 Jan 2022 16 Dez 22 Nov 2021
 * @copyright Copyright (c) 2021-2022 B. Borys
*/
#include "wettertafel.h"

/**
 * @brief die Servos
 * für Druck, Temperatur, Feuchtigkeit und Windstärke
 */
Servo ZeigerT,ZeigerF, ZeigerD, ZeigerW; 
/// Jahreszeit 0: unbekannt, 1..4: Frühling..Winter
uint8_t Jahreszeit = 0;
uint8_t WinkelF = 90, WinkelT = 90, WinkelD = 90, WinkelW = 90;
const uint8_t DELAY = 60;

/**
 * @brief verbesserte Mapping-Funktion
 * 
 * @param in 
 * @param in_min 
 * @param in_max 
 * @param out_min 
 * @param out_max 
 * @return double 
 */
double dmap(double in, double in_min, double in_max, double out_min, double out_max)
{
    return ((in - in_min) * (out_max - out_min)) / (in_max - in_min) + out_min;
}
/**
 * @brief rel. Luftfeuchte in qualitative Zeigerstellung in Grad umrechnen
 * Datenbasis: Rohdaten: 16 K Messwerte stündlich von Mai 2019 bis März 2021, Auswertung 210919
 * @param feuchte die angezeigt werden soll
 * 
 * Perzentile ganzes Jahr
 * 
 * Perzentile:  Min 5   10  25  50  75    90    95    Max
 * Feuchte:     13  40  48	66	81	89	  93	  100	  100
 * Winkel:      0°	9°	19°	47°	95°	142°	171°	180°	180°
 * 
 */
void AnzeigenF(int feuchte)
{
    const int anzahl = 9;
    int wert[5][anzahl] = {{13, 40, 48, 66, 81, 89, 93, 96, 100},
                           {13, 32, 37, 50, 70, 86, 93, 96, 100 /*Frühling*/},
                           {13, 37, 42, 53, 69, 83, 93, 96, 100 /*Sommer*/},
                           {13, 49, 60, 75, 83, 93, 95, 97, 100 /*Herbst*/},
                           {13, 64, 69, 79, 86, 93, 96, 98, 100 /*Winter*/}};
    int winkel[anzahl] = {0, 9, 19, 47, 95, 142, 171, 180, 180};
    float ziel;
    //Zeiger.write(0);
    for (size_t i = 0; i < (anzahl - 1); i++)   //i von 0 bis 7
    {
        if (feuchte <= wert[Jahreszeit][i + 1])
        {
            ziel = dmap(feuchte, wert[Jahreszeit][i], wert[Jahreszeit][i + 1], winkel[i], winkel[i + 1]);
            break;
        }
        if (i==(anzahl-2))  //höchstes i aber kein break, dann max. Ausschlag
        {
            ziel = 180.0;
        }        
    }

    // if (feuchte < 40)
    //     ziel = dmap(feuchte, 13, 40, 0, 9);
    // else if (feuchte < 48)
    //     ziel = dmap(feuchte, 40, 48, 9, 19);
    // else if (feuchte < 66)
    //     ziel = dmap(feuchte, 48, 66, 19, 47);
    // else if (feuchte < 81)
    //     ziel = dmap(feuchte, 66, 81, 47, 95);
    // else if (feuchte < 89)
    //     ziel = dmap(feuchte, 81, 89, 95, 142);
    // else if (feuchte < 93)
    //     ziel = dmap(feuchte, 89, 93, 142, 171);
    // else
    //     ziel = dmap(feuchte, 93, 100, 171, 180);
#ifndef NDEBUG
    Serial.print("Anzeigen %r.F.: ");
    Serial.println(feuchte);
#endif

#ifdef SERVO
    WinkelF = Stellen(ZeigerF, WinkelF, (int)(180.5 - ziel), DELAY);
#endif //SERVO
}
/**
 * @brief Luftdruck in qualitative Zeigerstellung in Grad umrechnen
 * Datenbasis: Rohdaten: 16 K Messwerte stündlich von Mai 2019 bis März 2021, Auswertung 210919
 * @param druck der angezeigt werden soll
 * 
 * Perzentile ganzes Jahr
 * 
 * Perzentile:  Min 5   10    25    50    75    90    95    Max
 * Druck:       976 996	1002	1010	1016	1021	1026	1030	1047 hPa
 * Winkel:      0°	9   18    45    90    135   162   171   180°
 * 
 */
void AnzeigenD(int druck)
{
    const int anzahl = 9;
    int wert[anzahl] = {976 ,996 ,1002 ,1010 ,1016 ,1021 ,1026 ,1030 ,1047};
    int winkel[anzahl] = {0, 9, 18, 45, 90, 135,162, 171, 180};
    float ziel;
    //Zeiger.write(0);
    for (size_t i = 0; i < (anzahl - 1); i++) //i von 0 bis 7
    {
        if (druck <= wert[i + 1])
        {
            ziel = dmap(druck, wert[i], wert[i + 1], winkel[i], winkel[i + 1]);
            break;
        }
        if (i == (anzahl - 2)) //höchstes i aber kein break, dann max. Ausschlag
        {
            ziel = 180.0;
        }
    }
    //Zeiger.write(0);
    // if (druck < 996)
    //     ziel = dmap(druck, 976, 996, 0, 9);
    // else if (druck < 1002)
    //     ziel = dmap(druck, 996, 1002, 9, 18);
    // else if (druck < 1010)
    //     ziel = dmap(druck, 1002, 1010, 18, 45);
    // else if (druck < 1016)7
    //     ziel = dmap(druck, 1010, 1016, 45, 90);
    // else if (druck < 1021)
    //     ziel = dmap(druck, 1016, 1021, 90, 135);
    // else if (druck < 1026)
    //     ziel = dmap(druck, 1021, 1026, 135, 162);
    // else if (druck < 1030)
    //     ziel = dmap(druck, 1026, 1030, 162, 171);
    // else
    //     ziel = dmap(druck, 1030, 1047, 171, 180);
#ifndef NDEBUG
    Serial.print("Anzeigen Druck: ");
    Serial.println(druck);
#endif
#ifdef SERVO
    WinkelD = Stellen(ZeigerD, WinkelD, (int)(180.5 - ziel), DELAY);
#endif //SERVO
}
/**
 * @brief Temperatur in qualitative Zeigerstellung in Grad umrechnen
 * Datenbasis: Rohdaten: 16 K Messwerte stündlich von Mai 2019 bis März 2021
 * Auswertung 210919: Temperatur ist signifikant von der Jahreszeit abhängig
 * 
 * @param Temperatur, die angezeigt werden soll
 * 
 * Perzentile ganzes Jahr
 * 
 * Perzentile:  Min   5     10    25    50    75    90    95    Max
 * Temperatur:  -19.7 -0.2  1.2   4.3   10.0  16.0  20.9  23.6  36.4 ganzes Jahr
 *              -1.9	2.5	  3.7	  6.9	  10.6	14.1	17.5	19.7	31.2 Herbst      
 * Winkel:      0°	  9     18    45    90    135   162   171   180°
 * 
 */
void AnzeigenT(float temp)
{
    float ziel;
    const int anzahl = 9;
    float wert[5][anzahl] = {
        {-19.7, -0.2,  1.2,  4.3, 10.0, 16.0, 20.9, 23.6, 36.4 /*ganzes Jahr*/},
        { -5.6,  0.0,  1.6,  4.4,  8.0, 12.9, 17.0, 19.1, 22.9 /*Frühling*/},
        {  6.4, 11.0, 12.5, 14.9, 18.2, 21.8, 25.4, 27.9, 36.4 /*Sommer*/},
        { -1.9,  2.5,  3.7,  6.9, 10.6, 14.1, 17.5, 19.7, 31.2 /*Herbst*/},
        {-19.7, -3.4, -1.1,  0.9,  3.0,  5.7,  8.3,  9.9, 17.4 /*Winter*/}};
    int winkel[anzahl] = {0, 9, 18, 45, 90, 135, 162, 171, 180};
    //Zeiger.write(0);
    for (size_t i = 0; i < (anzahl - 1); i++) //i von 0 bis 7
    {
        if (temp <= wert[Jahreszeit][i + 1])
        {
            ziel = dmap(temp, wert[Jahreszeit][i], wert[Jahreszeit][i + 1], winkel[i], winkel[i + 1]);
            break;
        }
        if (i == (anzahl - 2)) //höchstes i aber kein break, dann max. Ausschlag
        {
            ziel = 180.0;
        }
    }
    //Zeiger.write(0);
    // if (temp < 2.5)
    //     ziel = dmap(temp, -1.9, -2.4, 0, 9);
    // else if (temp < 3.7)
    //     ziel = dmap(temp, 2.5, 3.7, 9, 18);
    // else if (temp < 6.9)
    //     ziel = dmap(temp, 3.7, 6.9, 18, 45);
    // else if (temp < 10.6)
    //     ziel = dmap(temp, 6.9, 10.6, 45, 90);
    // else if (temp < 14.1)
    //     ziel = dmap(temp, 10.6, 14.1, 90, 135);
    // else if (temp < 17.5)
    //     ziel = dmap(temp, 14.1, 17.5, 135, 162);
    // else if (temp < 19.7)
    //     ziel = dmap(temp, 17.5, 19.7, 162, 171);
    // else
    //     ziel = dmap(temp, 19.7, 31.2, 171, 180);
#ifndef NDEBUG
    Serial.print("Anzeigen Temp: ");
    Serial.println(temp);
#endif
#ifdef SERVO
    WinkelT = Stellen(ZeigerT, WinkelT, (int)(180.5 - ziel), DELAY);
#endif //SERVO
}
/**
 * @brief windgeschwindigkeit in qualitative Zeigerstellung in Grad umrechnen
 * Datenbasis: Rohdaten: 16 K Messwerte stündlich von Mai 2019 bis März 2021, Auswertung 210919
 * @param Windgeschwindigkeit, die angezeigt werden soll
 * 
 * Perzentile ganzes Jahr
 * 
 * Perzentil	  Min	5	  10	25	50	75	90	95	Max
 * Wind [m/s]	  0,1	0,5	1,0	1,5	3,1	4,6	6,2	7,2	17,0
 * Anzeige [°]	0	  9	  18	45	90	135	162	171	180
 * Unabhängig von Jahreszeit
 * 
 */
void AnzeigenW(float wind)
{
    float ziel;
    const int anzahl = 9;
    float wert[anzahl] = {0.1, 0.5, 1.0, 1.5, 3.1, 4.6, 6.2, 7.2, 17.0};
    int winkel[anzahl] = {0, 9, 18, 45, 90, 135, 162, 171, 180};
    //Zeiger.write(0);
    for (size_t i = 0; i < (anzahl - 1); i++) //i von 0 bis 7
    {
        if (wind <= wert[i + 1])
        {
            ziel = dmap(wind, wert[i], wert[i + 1], winkel[i], winkel[i + 1]);
            break;
        }
        if (i == (anzahl - 2)) //höchstes i aber kein break, dann max. Ausschlag
        {
            ziel = 180.0;
        }
    }
    //Zeiger.write(0);
    // if (wind < 0.5)
    //     ziel = dmap(wind, 0.1, 0.5, 0, 9);
    // else if (wind < 1.0)
    //     ziel = dmap(wind, 0.5, 1.0, 9, 18);
    // else if (wind < 1.5)
    //     ziel = dmap(wind, 1.0, 1.5, 18, 45);
    // else if (wind < 3.1)
    //     ziel = dmap(wind, 1.5, 3.1, 45, 90);
    // else if (wind < 4.6)
    //     ziel = dmap(wind, 3.1, 4.6, 90, 135);
    // else if (wind < 6.2)
    //     ziel = dmap(wind, 4.6, 6.2, 135, 162);
    // else if (wind < 7.7)
    //     ziel = dmap(wind, 6.2, 7.2, 162, 171);
    // else
    //     ziel = dmap(wind, 7.2, 17.0, 171, 180);
#ifndef NDEBUG
    Serial.print("Anzeigen Wind: ");
    Serial.println(wind);
#endif
#ifdef SERVO
    WinkelW = Stellen(ZeigerW, WinkelW, (int)(180.5 - ziel), DELAY);
#endif //SERVO
}
