void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600) ;
    Serial.println("Start here"); 
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println(millis() ) ;
    delay(1000) ;
}
