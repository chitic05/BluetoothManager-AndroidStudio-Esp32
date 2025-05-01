#include <Arduino.h>
#include <BluetoothSerial.h>
#include <cstring>


class btManager{
  public:
    btManager(HardwareSerial& serial) : serial(serial){
      serial.begin(9600);
      serialBt.begin("ESP-32");
      serial.println("Bluetooth ready. Waiting for data...");
    } 
    
    void Send(char* message){
      serialBt.println(message);
    }
    
    char* Receieve() {
      if(serialBt.available()) {
        int character = serialBt.read();

        if (character != '\n' && newLineIndex < 127) { // Check for newline and buffer overflow
          newLine[newLineIndex++] = (char)character;
          newLine[newLineIndex] = '\0'; // Null-terminate the string
        } else if (character == '\n') {

          strcpy(currentLine, newLine);
          newLineIndex = 0; // Reset index
          newLine[0] = '\0'; // Clear the string
          return currentLine;
        }
      }
      return nullptr;
    }
    
  private:
    BluetoothSerial serialBt;
    HardwareSerial serial;
    char currentLine[128] = "";
    char newLine[128] = "";
    int newLineIndex = 0;

    void processMessage(const char* message)
    {
      if(strcmp(message, "forward") == 0){

      }
      else if(strcmp(message, "reverse") == 0){

      }

      if(strcmp(message, "left") == 0){
        
      }
      else if(strcmp(message, "right") == 0){

      }
    }
    
};
