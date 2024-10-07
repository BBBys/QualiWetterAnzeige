# Qualitative Wetteranzeige
QualiWetterAnzeige
## Ziel
Anzeige von Wetterdaten wie 
Temperatur, Druck, Feuchte, Wind, Mondphase als qualitative Werte wie hoch/niedrig, stark/schwach ... durch Zeiger über je einer Skala, angetrieben von Servo-Motoren
## Messwerte und Abbildung
Berücksichtigt werden Temperatur, relative Luftfeuchte, Luftdruck und Windeschwindigkeit

Dabei soll die Umrechnung so vorgenommen werden, dass 
  -   der gesammte Stellbereich (0° ... 180°) ausgenutzt wird
  -   der Mittlere Wert(2)  durch den Zeiger in der als 90°-Stellung angezeigt wird.
 
### Beispiel

 * die Luftfeuchte (relative Feuchte r.F.) erreicht bei Regen 93 bis 100 % r.F., fällt aber selten(1) unter 40 % r.F. und nie(1) unter 13 % r.F.
 * Zeigerstellung bei  13 % r.F. -->   0° (also linker Rand)
 * Zeigerstellung bei  40 % r.F. -->   9°
 * Zeigerstellung bei  93 % r.F. --> 171°
 * Zeigerstellung bei 100 % r.F. --> 180° (rechter Rand)
 * weiter liegen die Messwerte in der Hälfte der Zeit(1) unter 81 % (2)
 * Zeigerstellung bei  81 % r.F. -->  90° (also Mitte)
## Anpassung
Da die Werte zum Teil von der Jahreszeit abhängig sind, 
 -    Temperatur im Sommer und Herbst höher als im Frühling und Winter
 -    Luftfeuchte im Frühling und Sommer niedriger als im Herbst und Winter

wird die Umrechnung auch angepasst (die Unterschiede bei Luftdruck und Windgeschwindigkeit sind statistisch(1) nicht signifikant)

* (1) ausgewertet wurden ca. 16.000 Messwerte in stündlichem Abstand von Mai 2019 bis März 2021
- (2) Medianwert 
