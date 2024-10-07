# Qualitative Weather Display
QualiWetterAnzeige
## Goal
Display weather data like
temperature, pressure, humidity, wind, moon phase not as numeric, but as qualitative values ​​such as high/low, strong/weak ... by pointers over a scale, each driven by a servo motor.
## Measured values ​​and illustration
Temperature, relative humidity, air pressure and wind speed are taken into account.
The conversion should be carried out in such a way that
- the entire scale of the display (0° ... 180°) is used
- the average (mediam) value<sup>(2)</sup> is displayed by the pointer in 90° position.
### Example
* the air humidity (relative humidity r.h.) reaches 93 to 100% r.h. when it rains, but rarely<sup>(1)</sup> falls below 40% r.h. and never<sup>(1)</sup> below 13% r.h.
* Pointer position at 13 % r.h. --> 0° (i.e. left edge)
* Pointer position at 40 % RH --> 9°
* Pointer position at 93 % RH --> 171°
* Pointer position at 100 % RH --> 180° (right edge)
* Furthermore, the measured values ​​are below 81% half the time<sup>(1)(2)</sup>
* Pointer position at 81 % RH --> 90° (i.e. middle)
## Adjustment
Since the values ​​are partly dependent on the season,
- Temperature in summer and autumn higher than in spring and winter
- Humidity in spring and summer lower than in autumn and winter
the conversion is also adjusted (the differences in air pressure and wind speed are not statistically significant<sup>(1)</sup>)

* (1) Approx. 16,000 measured values ​​were evaluated at hourly intervals from May 2019 to March 2021
* (2) Median value
-------------------
# Qualitative Wetteranzeige
QualiWetterAnzeige
## Ziel
Anzeige von Wetterdaten wie 
Temperatur, Druck, Feuchte, Wind, Mondphase als qualitative Werte wie hoch/niedrig, stark/schwach ... durch Zeiger über je einer Skala, angetrieben von Servo-Motoren
## Messwerte und Abbildung
Berücksichtigt werden Temperatur, relative Luftfeuchte, Luftdruck und Windeschwindigkeit

Dabei soll die Umrechnung so vorgenommen werden, dass 
  -   der gesammte Stellbereich (0° ... 180°) ausgenutzt wird
  -   der mittlere (Median) Wert<sup>(2)</sup>  durch den Zeiger in der als 90°-Stellung angezeigt wird.
 ### Beispiel
 * die Luftfeuchte (relative Feuchte r.F.) erreicht bei Regen 93 bis 100 % r.F., fällt aber selten<sup>(1)</sup> unter 40 % r.F. und nie(1) unter 13 % r.F.
 * Zeigerstellung bei  13 % r.F. -->   0° (also linker Rand)
 * Zeigerstellung bei  40 % r.F. -->   9°
 * Zeigerstellung bei  93 % r.F. --> 171°
 * Zeigerstellung bei 100 % r.F. --> 180° (rechter Rand)
 * weiter liegen die Messwerte in der Hälfte der Zeit(1) unter 81 % <sup>(2)</sup>
 * Zeigerstellung bei  81 % r.F. -->  90° (also Mitte)
## Anpassung
Da die Werte zum Teil von der Jahreszeit abhängig sind, 
 -    Temperatur im Sommer und Herbst höher als im Frühling und Winter
 -    Luftfeuchte im Frühling und Sommer niedriger als im Herbst und Winter

wird die Umrechnung auch angepasst (die Unterschiede bei Luftdruck und Windgeschwindigkeit sind statistisch<sup>(1)</sup> nicht signifikant)

* (1) ausgewertet wurden ca. 16.000 Messwerte in stündlichem Abstand von Mai 2019 bis März 2021
* (2) Medianwert 
