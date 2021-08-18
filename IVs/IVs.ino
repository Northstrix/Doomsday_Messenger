// Doomsday messenger with a sophisticated encryption scheme
// Initialization Vector Setter
// Distributed under the MIT License
// © Copyright Maxim Bortnikov 2021
// For more information please visit
// https://github.com/Northstrix/Doomsday_Messenger
#include <ESP8266WiFi.h>
#include <FS.h>

String readFile(fs::FS &fs, const char * path){
  Serial.printf("Reading file: %s\r\n", path);
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- empty file or failed to open file");
    return String();
  }
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, String IV){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path, "w");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(IV)){
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
}
void setup() {
  Serial.begin(115200);
  // Initialize SPIFFS
    if(!SPIFFS.begin()){
      Serial.println("An Error has occurred while mounting SPIFFS");
      return;
    }

  String fiv = "74167432";
  String siv = "83624730";
  String tiv = "31637439";
  String foiv = "35095347";
  String fiiv = "39298901";
  
  writeFile(SPIFFS, "/FIV.txt", fiv);
  writeFile(SPIFFS, "/SIV.txt", siv);
  writeFile(SPIFFS, "/TIV.txt", tiv);
  writeFile(SPIFFS, "/FOIV.txt", foiv);
  writeFile(SPIFFS, "/FIIV.txt", fiiv);

}

void loop() {
  String f = readFile(SPIFFS, "/FIV.txt");
  String s = readFile(SPIFFS, "/SIV.txt");
  String t = readFile(SPIFFS, "/TIV.txt");
  String fourth_iv = readFile(SPIFFS, "/FOIV.txt");
  String fifth_iv = readFile(SPIFFS, "/FIIV.txt");
  unsigned int fir = f.toInt();
  unsigned int sec = s.toInt();
  unsigned int thi = t.toInt();
  unsigned int fou = fourth_iv.toInt();
  unsigned int fif = fifth_iv.toInt();
  Serial.println("IVs:");
  Serial.println(fir);
  Serial.println(sec);
  Serial.println(thi);
  Serial.println(fou);
  Serial.println(fif);
  delay(5000);

}

