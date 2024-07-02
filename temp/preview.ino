#include <HTTP_Method.h>
#include <Uri.h>
// #include <WebServer.h>
#include <Ultrasonic.h>

#include <WiFi.h>
#include <HTTPClient.h>
// const char* ssid = "TP-Link_5EBC";
// const char* password =  "04240044";
const char* ssid = "Kiol-phone";
const char* password =  "741852963";
// const char* ssid = "iPhone 15 Pro Max";
// const char* password =  "peko123000";
int* deviceIdArray=new int[40];
int* InputArray = new int[7];
bool* deviceStatus=new bool[40];
char** deviceName = new char*[40];
int* OutputArray = new int[7];
// WebServer server(80);
Ultrasonic ultrasonic(4, 15);
Ultrasonic ultrasonic2(21, 22);
int distance, distance2;
int startTime, duration;
int humans=3; //temp

void lightOn(int pin){
  digitalWrite(deviceIdArray[pin], 1);
  Serial.println(deviceIdArray[pin]);
  deviceStatus[pin] = true;
}
void lightOff(int pin){
  digitalWrite(deviceIdArray[pin], 0);
  Serial.println(deviceIdArray[pin]);
  deviceStatus[pin] = false;
}

void scanAP(void) {
  int n = WiFi.scanNetworks();
  delay(1000);
  Serial.println("scan Wi-Fi done");
  if (n == 0)
    Serial.println("no Wi-Fi networks found");
  else
  {
    Serial.print(n);
    Serial.println(" Wi-Fi networks found");
    for (int i = 0; i < n; ++i)
     {
      Serial.print(i + 1);
      Serial.print(": ");
      //印出SSID
      Serial.print(WiFi.SSID(i));
      Serial.print(" (");
      //印出RSSI強度
      Serial.print(WiFi.RSSI(i));
      Serial.print(")");
      //印出加密模式
      Serial.println(WiFi.encryptionType(i),HEX);
      delay(10);
     }
  }
}
void sendPost(){
  HTTPClient http;
  // http.begin("http://172.20.10.3:3000/api/posts");
  http.begin("http://192.168.129.220:3000/api/posts");
  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.POST("id:2,width:11.3,height:12.4,level:3,score:133");
  if(httpResponseCode>0){
    Serial.println(httpResponseCode);
  }else{
    Serial.print("error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
void deviceStatusChange(int pin){
  HTTPClient http;
  http.begin("http://172.20.10.3:3000/api/deviceChange");
  // http.begin("http://172.20.10.2:3000/api/deviceChange");
  // http.begin("http://192.168.129.220:3000/api/deviceChange");
  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.POST(deviceName[pin]);
  if(httpResponseCode>0){
    Serial.println(httpResponseCode);
  }else{
    Serial.print("error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
void postMembers(){
  HTTPClient http;
  http.begin("http://172.20.10.3:3000/api/getMembers");
  // http.begin("http://172.20.10.2:3000/api/deviceChange");
  // http.begin("http://192.168.129.220:3000/api/deviceChange");
  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.POST(String(humans));
  if(httpResponseCode>0){
    Serial.println(httpResponseCode);
  }else{
    Serial.print("error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
String getValue(String data, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void getDeviceStatus(){
  HTTPClient http;
  http.begin("http://172.20.10.3:3000/api/getDeviceStatus");
  // http.begin("http://172.20.10.2:3000/api/getDeviceStatus");
  // http.begin("http://192.168.129.220:3000/api/deviceChange");
  http.addHeader("Content-Type", "text/plain");
  int httpResponseCode = http.GET();
  if(httpResponseCode>0){
    Serial.println(httpResponseCode);
    String payload = http.getString();
    // Serial.println(payload);
    // Serial.println(getValue(payload, ':', 1));
    const String data = getValue(payload, ':', 1);
    Serial.println(data);
    int index=0;
    for(int i=0; i<data.length(); i++){
      if(index<5){
        if(data[i]=='f'){
          lightOff(InputArray[index]);
          index++;
        }else if(data[i]=='t'){
          lightOn(InputArray[index]);
          index++;
        }
      }
    }
    for(int i=0; i<5; i++) Serial.println(deviceStatus[InputArray[i]]);
  }else{
    Serial.print("error on sending GET: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
void IRAM_ATTR isr_Callback(){
  sendPost();
}

void variableInit(){//4 0 2 15 12 14 13
  InputArray[0]=27;
  InputArray[1]=35;
  InputArray[2]=26;
  InputArray[3]=12;
  InputArray[4]=36;

  OutputArray[0]=13;
  OutputArray[1]=14;
  OutputArray[2]=25;
  OutputArray[3]=33;
  OutputArray[4]=32;

  deviceName[27] = "light A";
  deviceName[35] = "light B";
  deviceName[26] = "light C";
  deviceName[36] = "light D";
  deviceName[12] = "fan A";
  // deviceName[13] = "fan B";
  // deviceName[14] = "fan C";
  for(int i=0; i<5; i++) deviceIdArray[InputArray[i]]=OutputArray[i];

  humans=0;
}

void setup() {
  variableInit();
  for(int i=0; i<5; i++) pinMode(InputArray[i], INPUT);
  for(int i=0; i<5; i++) pinMode(OutputArray[i], OUTPUT);
  // attachInterrupt(digitalPinToInterrupt(interruptPin), isr_Callback, RISING);
  Serial.begin(115200);
  // for(int i=0; i<3; i++){
  //   scanAP();
  //   delay(5000);
  // }
  delay(4000);   //Delay needed before calling the WiFi.begin
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("local ip:");
  Serial.println(WiFi.localIP());
  getDeviceStatus();
  postMembers();
  // startTime = millis();
}

// server.on("/sw", []() {
//     String state = server.arg("led");   // 伺服器物件.arg(參數名稱)，參數為 GET 或 POST
//     if (state == "on") {
//       lightOn(InputArray[0]);
//     } else if (state == "off") {
//       lightOff(InputArray[0]);
//     } else {
//       server.send(200, "text/html", "No such command.");
//       return;
//     }
//     server.send(200, "text/html", "LED is <b>" + state + "</b>.");
// });

void turnOffAll(){
  Serial.println("turn off all");
  for(int i=0; i<5; i++){
    if(deviceStatus[InputArray[i]]==true){
      lightOff(InputArray[i]);
      Serial.println("off");
      deviceStatusChange(InputArray[i]);
    }
  }
}

int pin;
void loop(){
  for(int i=0; i<5; i++){
    pin = InputArray[i];
    if(digitalRead(pin)==1&&deviceStatus[pin]==false){
      delay(25);
      while(digitalRead(pin));
      lightOn(InputArray[i]);
      Serial.println("on");
      deviceStatusChange(pin);
      delay(25);
    }else if(deviceStatus[pin]==true&&digitalRead(pin)==1){
      delay(25);
      while(digitalRead(pin));
      lightOff(InputArray[i]);
      Serial.println("off");
      deviceStatusChange(pin);
      delay(25);
    }
  }
  // server.handleClient();
  // duration = millis()-startTime;
  /*
  distance = ultrasonic.read();
  distance2 = ultrasonic2.read();
  if(distance2<50){
    Serial.println("exist something on back");
    startTime = millis();
    bool in=false;
    while(true){
      distance = ultrasonic.read();
      if(millis()-startTime>=3000) break;
      else if(distance<50){
        in=true;
        Serial.println("someone enter");
        break;
      }
    }
    if(in){
      humans++;
      postMembers();
      delay(1000);
    }
  }else if(distance<50){
    Serial.println("exist something on front");
    startTime = millis();
    bool out=false;
    while(true){
      distance2 = ultrasonic2.read();
      if(millis()-startTime>=3000) break;
      else if(distance2<50){
        out=true;
        break;
      }
    }
    if(out&&humans>0){
      // humans--;
      if(humans==0) turnOffAll();
      postMembers();
      delay(1000);
    }
  }
  */
  // Serial.println(distance);
  // Serial.println(distance2);
  // delay(5000);
}