#define Led_Red_Pin 10
#define Led_Green_Pin 11
#define Led_Blue_Pin 12
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin Blink_Led_Pin as an output.
  pinMode(Led_Red_Pin, OUTPUT);    //定義Led_Red_Pin為輸出腳位
  pinMode(Led_Green_Pin, OUTPUT);    //定義Led_Green_Pin為輸出腳位
  pinMode(Led_Blue_Pin, OUTPUT);    //定義Led_Green_Pin為輸出腳位
  digitalWrite(Led_Red_Pin,LOW) ;
  digitalWrite(Led_Green_Pin,LOW) ;
  digitalWrite(Led_Blue_Pin,LOW) ;
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(Led_Red_Pin, HIGH);  
  delay(1000);              //休息1秒 wait for a second  
  digitalWrite(Led_Red_Pin, LOW);   
  delay(1000);              // 休息1秒 wait for a second
  digitalWrite(Led_Green_Pin, HIGH);   
  delay(1000);              //休息1秒 wait for a second  
  digitalWrite(Led_Green_Pin, LOW);  
  delay(1000);              // 休息1秒 wait for a second
  digitalWrite(Led_Blue_Pin, HIGH);   
  delay(1000);              //休息1秒 wait for a second  
  digitalWrite(Led_Blue_Pin, LOW);  
  delay(1000);              // 休息1秒 wait for a second
  digitalWrite(Led_Red_Pin, HIGH);  
  digitalWrite(Led_Green_Pin, HIGH);  
  digitalWrite(Led_Blue_Pin, LOW);   
  delay(1000);              //休息1秒 wait for a second  
  digitalWrite(Led_Red_Pin, HIGH);  
  digitalWrite(Led_Green_Pin, LOW);  
  digitalWrite(Led_Blue_Pin, HIGH);   
  delay(1000);              //休息1秒 wait for a second  
  digitalWrite(Led_Red_Pin, LOW);  
  digitalWrite(Led_Green_Pin, HIGH);  
  digitalWrite(Led_Blue_Pin,HIGH );   
  delay(1000);              //休息1秒 wait for a second  

// all color turn off
  digitalWrite(Led_Red_Pin, LOW);  
  digitalWrite(Led_Green_Pin, LOW);  
  digitalWrite(Led_Blue_Pin, LOW);   
  delay(1000);              //休息1秒 wait for a second  

}
