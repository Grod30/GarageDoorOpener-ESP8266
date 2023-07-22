# GarageDoorOpener-ESP8266

This project was made for a real use at home using a ESP8266 and Firebase Realtime database

# Dependency

[mobizt/Firebase Arduino Client Library for ESP8266 and ESP32](https://github.com/mobizt/Firebase-ESP-Client)   
[PlatformIO](https://platformio.org/) but you can use [ArduinoIDE](https://www.arduino.cc/en/software)


# Hardware
- NodeMCU v2 ESP8266   
- Relay board SRD-05VDC-SL-C (Not the JQC-3FF-S-Z because this one does not work with the NodeMCU voltage)
- ***Optional* Protoboard (can be wired directly too)
- Dupont wires

  # Troubleshooting
  - Set the data rate on 9600(Serial.begin(9600)) to use the serial monitor without issues
  - 5ghz SSID frecuencies are not supported on the ESP8266
  - Use the SRD relay board because the JQC won't work because NodeMCU work with a lower voltage range than arduino
  - Connect the COM and the NO ports on the relay because is a low level trigger
  - Remember to always initialize (digitalWrite(RELAYPIN, HIGH)) the pin on HIGH before setting the pin mode (pinMode(RELAYPIN, OUTPUT))
