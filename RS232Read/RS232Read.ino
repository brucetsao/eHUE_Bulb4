#define pinCTS 11
#define pinRTS 10
#include <SoftwareSerial.h>   // 引用程式庫

// 定義連接藍牙模組的序列埠
SoftwareSerial BT(8, 9); // 接收腳, 傳送腳
char val;  // 儲存接收資料的變數

void setup() {
  Serial.begin(9600);   // 與電腦序列埠連線
    BT.begin(9600);
  Serial.println("BT is ready!");
 pinMode(pinCTS, INPUT); //INPUT    
    pinMode(pinRTS, OUTPUT);
    digitalWrite(pinRTS, HIGH);    //enable RTS
  // 設定藍牙模組的連線速率
  // 如果是HC-05，請改成9600

}

void loop() {

  // 若收到藍牙模組的資料，則送到「序列埠監控視窗」
    digitalWrite(pinRTS, HIGH);    //enable RTS
  //  digitalWrite(pinCTS, HIGH);    //enable RTS

  if (BT.available()) {

//    if (digitalRead(pinCTS))
        {
            val = BT.read();
            Serial.print(val);
        }
  }

  // 若收到「序列埠監控視窗」的資料，則送到藍牙模組
  if (Serial.available()) {
    val = Serial.read();
    BT.write(val);
  }
}
