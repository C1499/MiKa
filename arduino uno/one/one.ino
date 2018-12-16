//调用IRremote.h库
#include <IRremote.h>
//调用Servo.h库
#include <Servo.h>

// 最多可以控制 8 路舵机
Servo myservo;
// 用于存储舵机位置的变量
int pos = 0;

//初始化

//定义RECV_PIN变量为10
int RECV_PIN = 10;
//设置RECV_PIN（也就是10引脚）为红外接收端
IRrecv irrecv(RECV_PIN);
//定义results变量为红外结果存放位置
decode_results results;
//设定执行程序的用户码，根据自己实际更改
long a[] = {0xFF02FD,0xD7E84B1B,0xA25DC639,0x61D648B7,0x61D6D827,0x61D658A7,0x61D620DF,0x61D6609F,0x61D6A05F};

void setup(){
  //串口波特率设为9600
  Serial.begin(9600); 
    //启动红外解码
  irrecv.enableIRIn();
  //设置9引脚为舵机信号接收端
  myservo.attach(9);
}

void loop(){
  //是否接收到解码数据,把接收到的数据存储在变量results中
    if (irrecv.decode(&results)){
  //接收到的数据以16进制的方式在串口输出
  Serial.println(results.value, HEX);
    //判断接收到的用户码是否匹配
    for (int b =0;b<9;b++){
      if (results.value == a[b]){
        // 从 180 度 - 2 度，步进度数为2
        for (pos = 170; pos > 2; pos -= 5){
          // 输入对应的角度值，舵机会转到此位置
          myservo.write(pos);
          // 15ms 后进入下一个位置
          delay(15);
        }
        // 从 2 度 - 180 度，步进度数为2
        for(pos = 2; pos< 170; pos+=5){
          // 输入对应的角度值，舵机会转到此位置
          myservo.write(pos);
          // 15ms 后进入下一个位置
          delay(15);
        }
      }
    }
  // 继续等待接收下一组信号
  irrecv.resume();
  }
}
