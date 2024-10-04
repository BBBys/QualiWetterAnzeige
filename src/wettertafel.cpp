/**
 * @file wettertafel.cpp
 * Qualitative Anzeige von Wetterdaten auf einer Wettertafel über Servo-Motoren
 * ============================================================================
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
<<<<<<< Updated upstream
 * @version 1.1
 * @date 21 16 Jan 2022 16 Dez 21 20 Nov 26 Okt 30 19 Sep 2021
=======
 * @version 2.1
 * @date 18 17 15 9 Aug 25 Feb 21 16 Jan 2022 16 Dez 21 20 Nov 26 Okt 30 19 Sep 2021
>>>>>>> Stashed changes
 * @copyright Copyright (c) 2021-2022 B. Borys
 * @note Verwendeter Beispielcode von Adafruit:
 *   Written by Limor Fried/Ladyada for Adafruit Industries.
 */

#include "wettertafel.h"
#include <Ticker.h> // Load library "ticker"
extern uint8_t Jahreszeit, WinkelF, WinkelT, WinkelD, WinkelW, WinkelM;
/// Servo?
#ifdef SERVO
extern Servo ZeigerT, ZeigerF, ZeigerD, ZeigerW, ZeigerM; // create servo object to control a servo
<<<<<<< Updated upstream
#endif        // Servo
=======
#else
#include <Adafruit_PWMServoDriver.h>
// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#endif // Servo
>>>>>>> Stashed changes

/**
 * @brief blinken
 * 
 */
Ticker Zeitgeber;

#ifdef MQTTein
#include "EspMQTTClient.h"
/*
   ================================================================================================
   MQTT
*/

/**
 * @brief MQTT
 * 
 */
EspMQTTClient MQTTClient(
    WLANSSID,
    WLANPWD,
    MQTTBROKERIP, // MQTT Broker server ip
    OTAUSER,      // Can be omitted if not needed
    OTAPASSWD,    // Can be omitted if not needed
    MQTTNAME,     // Client name that uniquely identify your device
    1883          // The MQTT port, default to 1883. this line can be omitted
);
/*
   MQTT
   ====================================================================================================
*/
#endif

/**
 * @brief Servo aus und 15 Minuten schlafen legen
 * Quelle: https://raw.githubusercontent.com/RuiSantosdotme/ESP32-Course/master/code/DeepSleep/TimerWakeUp/TimerWakeUp.ino
 */
void schlafen()
{
#ifndef NDEBUG
  Serial.println("schlafen");
  Serial.flush();
#endif
#ifdef SERVO
  ZeigerF.detach();
  ZeigerT.detach();
  ZeigerD.detach();
  ZeigerW.detach();
  ZeigerM.detach();
#endif
  delay(1000);
#ifdef NDEBUG
  ESP.deepSleep(991000000L);
#else
  ESP.deepSleep(5000000L);
#endif
  delay(1000);
  //yield();
}

/**
 * @brief Messdaten über MQTT anfordern
 * 
 */
void onConnectionEstablished()
{
<<<<<<< Updated upstream
#ifndef NDEBUG
  Serial.println("onConnectionEstablished");
#endif
  WinkelW = Stellen(ZeigerW, WinkelW, 100);
=======
DbgsOut("onConnectionEstablished");
  WinkelW = Stellen  (ZeigerW, WinkelW, 100);
>>>>>>> Stashed changes
#ifdef MQTTein
  MQTTClient.subscribe("Datum/JZeit", [](const String &payload)
                   { Jahreszeit = payload.toInt(); });
  MQTTClient.subscribe("Wetter/Feuchte", [](const String &payload)
                   { AnzeigenF(payload.toInt()); });
  MQTTClient.subscribe("Wetter/Wind", [](const String &payload)
                   { AnzeigenW(payload.toFloat()); });
  MQTTClient.subscribe("Temp/Aussen", [](const String &payload)
                   { AnzeigenT(payload.toFloat()); });
  MQTTClient.subscribe("Wetter/Druck", [](const String &payload)
                   { AnzeigenD(payload.toInt()); });
  MQTTClient.subscribe("Datum/MondN", [](const String &payload)
                       { AnzeigenM(payload.toFloat()); });
  // MQTTClient.subscribe("ein", [](const String &payload)
  //                      { digitalWrite(DISABLE, LOW); });
  // MQTTClient.subscribe("aus", [](const String &payload)
  //                      { digitalWrite(DISABLE, HIGH); });
  MQTTClient.subscribe("Wettertafel/direkt", [](const String &payload) { /// direktes Stellen zum Testen
    int w = payload.toInt();
    WinkelF = Stellen(ZeigerF, WinkelF,w );
    WinkelT = Stellen(ZeigerT, WinkelT, w);
    WinkelD = Stellen(ZeigerD, WinkelD, w);
    WinkelW = Stellen(ZeigerW, WinkelW, w);
    WinkelM = Stellen(ZeigerM, WinkelM, w);
#ifndef NDEBUG
    Serial.println("...direkt fertig");
#endif
  });
  MQTTClient.publish("SWVersion", VERSION);
  MQTTClient.publish("SWDatum", __DATE__);
  MQTTClient.publish("OTA-Usr", OTAUSER);
  MQTTClient.publish("OTA-Pwd", OTAPASSWD);
  MQTTClient.publish("Status", "Wettertafel läuft");
  MQTTClient.publish("Abfrage", "jetzt"); ///trigger die sofortige Übertragung der Daten
  Zeitgeber.detach();
  digitalWrite(LED_BUILTIN, LED_EIN); //ein
#endif                                //MQTTein
#ifndef NDEBUG
  Serial.println("... onConnectionEstablished return");
#endif
  WinkelW = Stellen(ZeigerW, WinkelW, 90);
} //void onConnectionEstablished()
/**
 * @brief LED blinken lassen
 * 
 */
void flip()
{
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}

void setup()
{
#ifndef NDEBUG
  Serial.begin(115200);
  Serial.println("\n...setup");
#endif
      pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(DISABLE, OUTPUT);
  Zeitgeber.attach(.5, flip);
#ifdef SERVO
#ifndef NDEBUG
  Serial.println("Attach Servos");
#endif
  /*
 * Achtung: 1 (=TX) und 7 (=?) funktioniert nicht
 * PWM-Ports für D1_Mini: D1..8, TX und RX
 * verwendet: D2, D3, D6, D7
 * D1, D8 geht auch, D5 sollte auch gehen
 * D4 hängt mit der LED zusammen?
 */
  ZeigerF.attach(D1, 500, 2500);
  ZeigerM.attach(D2, 500, 2500);
  ZeigerT.attach(D6, 500, 2500);
  ZeigerD.attach(D3, 500, 2500);
  ZeigerW.attach(D8, 500, 2500);
#ifndef NDEBUG
  Serial.println("Servos OK");
  WinkelT = Stellen(ZeigerT, WinkelT, 0);
  WinkelF = Stellen(ZeigerF, WinkelF, 0);
  WinkelD = Stellen(ZeigerD, WinkelD, 0);
  WinkelW = Stellen(ZeigerW, WinkelW, 0);
#endif
<<<<<<< Updated upstream
#endif //SERVOS
=======
#else //SERVO

  pwm.begin();
      /*
     * In theory the internal oscillator (clock) is 25MHz but it really isn't
     * that precise. You can 'calibrate' this by tweaking this number until
     * you get the PWM update frequency you're expecting!
     * The int.osc. for the PCA9685 chip is a range between about 23-27MHz and
     * is used for calculating things like writeMicroseconds()
     * Analog servos run at ~50 Hz updates, It is importaint to use an
     * oscilloscope in setting the int.osc frequency for the I2C PCA9685 chip.
     * 1) Attach the oscilloscope to one of the PWM signal pins and ground on
     *    the I2C PCA9685 chip you are setting the value for.
     * 2) Adjust setOscillatorFrequency() until the PWM update frequency is the
     *    expected value (50Hz for most ESCs)
     * Setting the value here is specific to each individual I2C PCA9685 chip and
     * affects the calculations for the PWM update frequency.
     * Failure to correctly set the int.osc value will cause unexpected PWM results
     */
  pwm.wakeup();
  pwm.setOscillatorFrequency(26645063L); // Kalibriert 2022-08-17
  pwm.setPWMFreq(SERVO_FREQ);            // Analog servos run at ~50 Hz updates
#endif //SERVO
  delay(10);
>>>>>>> Stashed changes
#ifdef MQTTein
#ifdef NDEBUG
  MQTTClient.enableDebuggingMessages(false);
#else                            //NDEBUG
  MQTTClient.enableDebuggingMessages(true);
  // digitalWrite(DISABLE, LOW);
  WinkelT = Stellen(ZeigerT, WinkelT, 90);
  WinkelF = Stellen(ZeigerF, WinkelF, 90);
#endif                           //NDEBUG
  MQTTClient.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword.
  MQTTClient.enableLastWillMessage("Wettertafel/lastwill", "Abbruch Wettertafel"); /// LWT-Meldung
#endif                                                                         //MQTTein
#ifndef NDEBUG
  Serial.println("Setup OK");
  WinkelD = Stellen(ZeigerD, WinkelD, 90);
  WinkelW = Stellen(ZeigerW, WinkelW, 90);
  WinkelM = Stellen(ZeigerM, WinkelM, 90);
#endif
}

void loop()
{
#ifdef MQTTein
  MQTTClient.loop();
  //if (!MQTTClient.isConnected())    Serial.println("!connected");
  //if (!MQTTClient.isWifiConnected())    Serial.println("!WIFIconnected");
  //if (!MQTTClient.isMqttConnected () )Serial.println("!MQTTconnected");
#endif
  delay(100);
}