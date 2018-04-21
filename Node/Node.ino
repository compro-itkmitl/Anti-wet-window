#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

#define WIFI_SSID "sony"
#define WIFI_PASS "88888888"

#define FIREBASE_HOST "antiwetw.firebaseio.com"
#define FIREBASE_KEY "k1ykX4WX9Jwkgxws9kbtsZGggSgbTj19BOfflxEU"

#define LINE_TOKEN "SURanQHzquAnGZfWUVZU8yObu2viZMQPqNFsa98oHTq"

String message = "Raining, window closed. https://antiwetw.firebaseapp.com";

int firebaseCommand = 0;
int rain = 0;
int wd = 0;
int md = 0;
int chk = 0;
int stat = 0;

void setup() {
  //Setup
  Serial.begin(115200);
  pinMode(D1, OUTPUT); //Firebase_Com
  pinMode(D2, INPUT); //Window
  pinMode(D3, OUTPUT); //Mode_Manual-Auto
  pinMode(D4, OUTPUT); //Status_Done
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST, FIREBASE_KEY);
}

void loop() {
  //Loop
  wd = digitalRead(D2); //Read_SW
  rain = analogRead(A0); //Read_Rain_Sensor
  firebaseCommand = Firebase.getInt("firebaseCommand"); //Get_Command_From_Firebase_WebApp
  md = Firebase.getInt("mode");
  stat = digitalRead(D4);
  Serial.print("window");
  Serial.println(wd);
  Serial.print("rain");
  Serial.println(rain);
  Serial.print("command");
  Serial.println(firebaseCommand);
  Serial.print("mode");
  Serial.println(md);
  Serial.print("stat");
  Serial.println(stat);
  if(stat){
    Firebase.setInt("firebaseCommand", 0);
  }
  if(firebaseCommand){
    digitalWrite(D1, HIGH);
    delay(300);
    digitalWrite(D1, LOW);
    Firebase.setInt("firebaseCommand", 0);
  }
  else{
    digitalWrite(D1, LOW);
  }
  if(md){
    digitalWrite(D3, HIGH);
  }
  else{
    digitalWrite(D3, LOW);
  }
  if(rain < 500){
    Firebase.setBool("rain", true);
  }
  else{
    Firebase.setBool("rain", false);
  }
  if(wd){
    Firebase.setInt("window", 0);
  }
  else{
    Firebase.setInt("flag", 1);
    Firebase.setInt("window", 1);
  }
  if(md == 0 && wd==1 && chk == 0 && rain < 500){
    noti(message);
    chk = 1;
  }
  delay(500);
}

void noti(String message) {
  WiFiClientSecure client;
  if (!client.connect("notify-api.line.me", 443)) {
    Serial.println("connection failed");
    return;   
  }
  String req = "";
  req += "POST /api/notify HTTP/1.1\r\n";
  req += "Host: notify-api.line.me\r\n";
  req += "Authorization: Bearer " + String(LINE_TOKEN) + "\r\n";
  req += "Cache-Control: no-cache\r\n";
  req += "User-Agent: ESP8266\r\n";
  req += "Connection: close\r\n";
  req += "Content-Type: application/x-www-form-urlencoded\r\n";
  req += "Content-Length: " + String(String("message=" + message).length()) + "\r\n";
  req += "\r\n";
  req += "message=" + message;
  client.print(req);
  delay(200);
  while(client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      break;
    }
  }
}
