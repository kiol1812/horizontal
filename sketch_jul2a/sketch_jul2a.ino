#include <HTTP_Method.h>
// #include <Uri.h>
// #include <WebServer.h>
// #include <Ultrasonic.h>

#include <WiFi.h>
#include <HTTPClient.h>

// const char* ssid = "iPhone";
// const char* password =  "741852963";
const char* ssid = "usb_lab_5G";
const char* password =  "usblabwifi";

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
  // http.begin("http://192.168.129.220:3000/api/posts");
  // http.begin("http://172.20.10.1:3000/api/newRecord");
  http.begin("http://192.168.1.50:3000/api/newRecord");
  http.addHeader("Content-Type", "text/plain");
  // int httpResponseCode = http.POST("id:2,width:11.3,height:12.4,level:3,score:133");
  int httpResponseCode = http.POST("time:100,offset_x:10,offset_y:10");
  if(httpResponseCode>0){
    Serial.println(httpResponseCode);
  }else{
    Serial.print("error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}
void setup() {
  Serial.begin(115200);
  delay(4000);   //Delay needed before calling the WiFi.begin
  for(int i=0; i<5; i++){
    scanAP();
    delay(5000);
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) { //Check for the connection
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  Serial.print("local ip:");
  Serial.println(WiFi.localIP());
}
void loop(){
  delay(10000);
  sendPost();
}
