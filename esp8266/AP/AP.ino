#include <Servo.h>

#include <IRrecv.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <IRtimer.h>
#include <IRutils.h>
#include <ir_Argo.h>
#include <ir_Coolix.h>
#include <ir_Daikin.h>
#include <ir_Fujitsu.h>
#include <ir_Gree.h>
#include <ir_Haier.h>
#include <ir_Hitachi.h>
#include <ir_Kelvinator.h>
#include <ir_LG.h>
#include <ir_Magiquest.h>
#include <ir_Midea.h>
#include <ir_Mitsubishi.h>
#include <ir_NEC.h>
#include <ir_Panasonic.h>
#include <ir_Samsung.h>
#include <ir_Toshiba.h>
#include <ir_Trotec.h>
#include <ir_Whirlpool.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// 最多可以控制 8 路舵机
Servo servo;
// 用于存储舵机位置的变量
int pos = 0;

//初始化

//定义RECV_PIN变量为10
int RECV_PIN =04;
//设置RECV_PIN（也就是10引脚）为红外接收端
IRrecv irrecv(RECV_PIN);
//定义results变量为红外结果存放位置
decode_results results;
//设定执行程序的用户码，根据自己实际更改
long a[] = {0xFF02FD,0xD7E84B1B,0x6B26D4C0,0xA25DC639,0x61D648B7,0x61D6D827,0x61D658A7,0x61D620DF,0x61D6609F,0x61D6A05F};

const char* ssid = "MiKa";
const char* password = "CLYWD";
ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}
  
void setup() {
  Serial.begin(9600); 
    //启动红外解码
  irrecv.enableIRIn();
  //设置9引脚为舵机信号接收端
  servo.attach(14);
  WiFi.mode(WIFI_AP);           //Only Access point
  WiFi.softAP(ssid, password); 
  Serial.print("HotSpt IP:");
  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
server.handleClient();
}
