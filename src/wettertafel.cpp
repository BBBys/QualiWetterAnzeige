/**
 * @file wettertafel.cpp
 * Qualitative Anzeige von Wetterdaten auf einer Wettertafel über Servo-Motoren
 * ============================================================================
 * @author Dr. Burkhard Borys, Zeller Ring 15, 34246 Vellmar, Deutschland
 * @version 1.1
 * @date 16 Jan 2022 16 Dez 21 20 Nov 26 Okt 30 19 Sep 2021
 * @copyright Copyright (c) 2021-2022 B. Borys
 */

#include "wettertafel.h"
#include <Ticker.h> // Load library "ticker"
extern uint8_t Jahreszeit, WinkelF, WinkelT, WinkelD, WinkelW;
/// Servo?
#ifdef SERVO
extern Servo ZeigerT, ZeigerF, ZeigerD, ZeigerW; // create servo object to control a servo
#endif        // Servo

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
#ifndef NDEBUG
  Serial.println("onConnectionEstablished");
#endif
  WinkelW = Stellen(ZeigerW, WinkelW, 100);
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
  MQTTClient.subscribe("Wettertafel/direkt", [](const String &payload) 
                   {/// direktes Stellen zum Testen
#ifdef SERVO
                     WinkelF = Stellen(ZeigerF, WinkelF, payload.toInt());
                     WinkelT = Stellen(ZeigerT, WinkelT, payload.toInt());
                     WinkelD = Stellen(ZeigerD, WinkelD, payload.toInt());
                     WinkelW = Stellen(ZeigerW, WinkelW, payload.toInt());
#endif //SERVO
#ifndef NDEBUG
                     Serial.println("...Stellen fertig");
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
#endif //SERVOS
#ifdef MQTTein
#ifdef NDEBUG
  MQTTClient.enableDebuggingMessages(false);
#else                            //NDEBUG
  MQTTClient.enableDebuggingMessages(true);
  WinkelT = Stellen(ZeigerT, WinkelT, 180);
  WinkelF = Stellen(ZeigerF, WinkelF, 180);
#endif                           //NDEBUG
  MQTTClient.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword.
  MQTTClient.enableLastWillMessage("Wettertafel/lastwill", "Abbruch Wettertafel"); /// LWT-Meldung
#endif                                                                         //MQTTein
#ifndef NDEBUG
  Serial.println("Setup OK");
  WinkelD = Stellen(ZeigerD, WinkelD, 180);
  WinkelW = Stellen(ZeigerW, WinkelW, 180);
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