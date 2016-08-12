#include <ArduinoJson.h>
#include <LiquidCrystal.h>
#include <LCDKeypad.h>
#include <ESP8266WiFi.h>


const char* ssid     = "*****";      // SSID of local network
const char* password = "*****";   // Password on network

int fBracket = 0;
int bBracket = 0;
WiFiClient client;
char servername[]="remote.server.com";  // remote server we will connect to

String result;
String intResult;

int setTemp = 0; 
int curTemp = 0;
int tarTemp = 0;
int readKey;
int count;
int cursorPosition;

// The LCD screen
LCDKeypad lcd;

int button;
int x = 0;
void setup() {
  //Setup Serial
  Serial.begin(9600);

  //Setup LCD
  lcd.begin(16, 2);
    //Connecting to server and get current temperature and set temperature
  lcd.print("Connecting");  
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  lcd.setCursor(0,1);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("NOT CONNECTED");
    if(cursorPosition == 16) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Connecting");
      cursorPosition = 0;
      lcd.setCursor(cursorPosition,1);
      lcd.print(".");
    }
    lcd.setCursor(cursorPosition,1); 
    lcd.print(".");
    cursorPosition++;
  }
  getNestData();
  printLCDValues();
  //Serial.println("Connected");*/
  delay(1000);

}

void loop() {
  
    switch (lcd.buttonBlocking()) {
    case KEYPAD_LEFT:
      //Select
      if(curTemp != setTemp) {
        setTargetTemp();
      }
      break;
    case KEYPAD_RIGHT:
      //Cancel
      setTemp = tarTemp;
      break;
    case KEYPAD_UP:
      if(setTemp < 100){
        setTemp += 1;
      }
      break;
    case KEYPAD_DOWN:
      if(setTemp > 50){
        setTemp -= 1;
      }
      break;
    case KEYPAD_SELECT:
      x = 0;
      break;
    }
    printLCDValues();   
  }
void printLCDValues(){
  
  lcd.setCursor(0,0);
  lcd.print("CurT: "); 
  lcd.print(curTemp,1);
  lcd.print((char)223);
  lcd.setCursor(0,1);
  lcd.print(setTemp,1);
  lcd.print((char)223);
}

void getNestData() //client function to send/receive GET request data.
{
  lcd.clear();
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    lcd.print("Connected");
    Serial.println("CONNECTED");
    client.println("GET /nest/getTemp.php?API=tresiba HTTP/1.1");
    client.println("Host: " + servername);
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Connection");
    lcd.setCursor(0,2);
    lcd.print("Failed");
    Serial.println("connection failed"); //error message if no client connect
    Serial.println();
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Fetching Data");
  cursorPosition = 0;
  lcd.setCursor(0,1);
  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result += c;
      if(cursorPosition == 15){
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Fetching Data");
        cursorPosition = 0;
        lcd.setCursor(0,1);
      }
      else{
        lcd.setCursor(cursorPosition,1);
        lcd.print(".");
      }
      lcd.clear();
    }
  
  client.stop(); //stop client
  fBracket = result.indexOf('{'); //receiving NEST data in {XX|XX} format
  bBracket = result.indexOf('}');
  result = result.substring(fBracket+1,bBracket);
  Serial.println(result);
  curTemp = result.substring(0,result.indexOf('|')).toInt(); //Setting current temperature
  setTemp = result.substring(result.indexOf('|')+1).toInt(); //Setting target temperature
  tarTemp = setTemp;
}

//Display temperature on the LCD
void displayTemperature()
{
 lcd.setCursor(0,0);
 lcd.print("CurT: "); 
 lcd.print(curTemp);
 lcd.print((char)223);
 lcd.print("F ");
 lcd.setCursor(0,1);
 lcd.print("Temp: ");
 lcd.print(setTemp);
 lcd.print((char)223);
 lcd.print("F ");
}

void displayGettingData()
{
  lcd.clear();
  lcd.print("Getting data");
}

//client function to send GET request data to server
void setTargetTemp() 
{
  lcd.clear();
  if (client.connect(servername, 80)) {  //starts client connection, checks for connection
    lcd.print("Connected");
    Serial.println("CONNECTED");
    client.println("GET /nest/setCurTemp.php?API=tresiba&SETTEMP=" + String(setTemp) + " HTTP/1.1");
    client.println("Host: " + servername);
    client.println("User-Agent: ArduinoWiFi/1.1");
    client.println("Connection: close");
    client.println();
  } 
  else {
    lcd.clear();
    lcd.setCursor(0,1);
    lcd.print("Connection");
    lcd.setCursor(0,2);
    lcd.print("Failed");
    Serial.println("connection failed"); //error message if no client connect
  }
  Serial.println("Waiting for response");
  while(client.connected() && !client.available()) delay(1); //waits for data
  while (client.connected() || client.available()) { //connected or data available
    char c = client.read(); //gets byte from ethernet buffer
      result += c;
    }
  client.stop(); //stop client
  Serial.println("Client Stoped");
  Serial.println("Response: " + result);
  
}

