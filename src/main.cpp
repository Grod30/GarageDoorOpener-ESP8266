#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>

// Provide the token generation process info.
#include "addons/TokenHelper.h"
// Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

#define SSID " " //Your Wifi network name goes here
#define SSID_PASSWORD " " //Your wifi network password goes here
#define DBVAR " " //Here goes your database variable

#define RELAYPIN 14

#define FIREBASE_DATABASE_URL " " //Add here your database link
#define FIREBASE_API_KEY " " // Set here the firebase api key

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

bool signupOK = false;

int WiFiCon()
{
  // Check if we have a WiFi connection, if we don't, connect.
  int xCnt = 0;

  if (WiFi.status() != WL_CONNECTED)
  {

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.mode(WIFI_STA);

    WiFi.begin(SSID, SSID_PASSWORD);

    while (WiFi.status() != WL_CONNECTED && xCnt < 50)
    {
      delay(500);
      Serial.print(".");
      xCnt++;
    }

    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("WiFiCon=0");
      return 0; // never connected
    }
    else
    {
      Serial.println("WiFiCon=1");
      Serial.println("");
      Serial.println("WiFi connected");
      Serial.println("IP address: ");
      Serial.println(WiFi.localIP());
      return 1; // 1 is initial connection
    }
  }
  else
  {
    Serial.println("WiFiCon=2");
    return 2; // 2 is already connected
  }
}

void setup()
{
  Serial.begin(9600);
  digitalWrite(RELAYPIN, HIGH);
  pinMode(RELAYPIN, OUTPUT);
  WiFiCon();
  config.api_key = FIREBASE_API_KEY;
  config.database_url = FIREBASE_DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", ""))
  {
    Serial.println("ok");
    signupOK = true;
  }
  else
  {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; // see addons/TokenHelper.h

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  // Here checks if the connection to firebase works
  if (Firebase.ready() && signupOK)
  {
    if (Firebase.RTDB.getInt(&fbdo, DBVAR) == 1)
    {
      if (fbdo.dataType() == "int") //just validating the value
      {
        int Value = fbdo.intData(); 
        Serial.println(Value); 
        if (Value == 1)
        {
          Serial.println("Writing to pin LOW");
          digitalWrite(RELAYPIN, LOW);
          delay(1000);
          Serial.println("Writing to pin HIGH");
          Firebase.RTDB.setInt(&fbdo, DBVAR, 0);
          digitalWrite(RELAYPIN, HIGH);
        }
      }
    }
  }

  delay(5000); //Delay just for while the garage door open/close
}