int DC_MOTOR[6] = {42,44,46,48,4,5};
int LED[8] = {22,24,26,28,30,32,34,36};
int SWITCH[8] = {23,25,27,29,31,33,35,37};

int LED_EN_PIN =6, SW_EN_PIN = 7;
int light_sensor = A1;
int open_detect1 = 3, open_detect2 = 2;
int z=0;

#define LED_EN 1
#define SW_EN 1


void setup() {
  Serial.begin(9600);
  LED_SW_EN();
  for(z=0;z<8;z++){
    pinMode(LED[z],OUTPUT);
    pinMode(SWITCH[z],INPUT);
  }
  for(z=0;z<6;z++){
    pinMode(DC_MOTOR[z],OUTPUT);
  }
  pinMode(light_sensor,INPUT);
  pinMode(open_detect1,INPUT);
  pinMode(open_detect2,INPUT);
}

void loop() {

  float light_data = analogRead(light_sensor)/204.6;
  Serial.print("light_data[v] : ");
  Serial.println(light_data);

  if(light_data <= 3.00){ // low
   
    MOTOR_control(10); // turn
    PWM_open(0);
    PWM_close(7); // move to od1
    Serial.println("turn");
   
    if(digitalRead(open_detect1)){
      Serial.println("detect1111"); // od1 detect
      PWM_close(0); // stop
      delay(2000);
      LED_blank();
      Serial.println("open_d1 is detected");
     
    }else{
      MOTOR_control(10); // turn
      PWM_open(0);
      PWM_close(7); // move to od1
    }
   
  }else{ // high
    PWM_open(0);
    MOTOR_control(5); // turn reverse
    PWM_close(0);
    PWM_open(7); // move to od2   
    Serial.println("turn reverse");
   
    if(digitalRead(open_detect2)){ // od2 detect
      Serial.println("detect22222");
      //DC_MOTOR stop
      PWM_open(0); // stop
      delay(2000);
      LED_blank();
      Serial.println("open_d2 is detected");
     
    }else{
        MOTOR_control(5); // turn reverse
        PWM_close(0);
        PWM_open(7); // move to od2 
    }
   
  }
}
void MOTOR_control(unsigned char da){
  for(z=0;z<4;z++){
    if(da & 0x08){
      digitalWrite(DC_MOTOR[z],HIGH);
    }else{
      digitalWrite(DC_MOTOR[z],LOW);
    }
    da *= 2;
  }
}

void PWM_open(unsigned char spe){
  analogWrite(DC_MOTOR[4],spe);
}

void PWM_close(unsigned char spe){
  analogWrite(DC_MOTOR[5],spe);
}

void LED_blank(){
  for(z=0;z<8;z++){
    digitalWrite(LED[z],HIGH);
  }
  delay(100);
  for(z=0;z<8;z++){
    digitalWrite(LED[z],LOW);
  }
  delay(100);
}

void LED_SW_EN(){
  pinMode(LED_EN_PIN,OUTPUT);
  pinMode(SW_EN_PIN,OUTPUT);
  #ifdef LED_EN
    digitalWrite(LED_EN_PIN,LOW);
  #else
    digitalWrite(LED_EN_PIN,HIGH);
  #endif
  #ifdef SW_EN
    digitalWrite(SW_EN_PIN,LOW);
  #else
    digitalWrite(SW_EN_PIN,HIGH);
  #endif
}