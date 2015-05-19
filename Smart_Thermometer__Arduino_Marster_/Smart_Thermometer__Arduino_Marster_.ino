/* 
  Smart Thermometer (Arduino_Master)
  By Zhenxi Mi
  zhenximi@uw.edu
  02/26/2015
  */
  
#include <IRremote.h>
 
int RECV_PIN = 10;
IRrecv irrecv(RECV_PIN);
decode_results results;
int sts = 0;

#define LED_R 3
#define LED_G 5
#define LED_B 6

int PWMValueR = 0;
int PWMValueG = 0;
int PWMValueB = 0;
int InitialLedLoop = 0;

#include <Servo.h> //引入lib
Servo myservo;  // 创建一个伺服电机对象
#define LM35  A0  // 设定连接可变电阻的模拟引脚
// this constant shows where we'll find the temp sensor on the Arduino board
const int sensorPin = A1; 

// this constant controls the sampling interval for temperature values
const int tempSampling = 500; // ms, 1 ms = 1/1000 second, so 500 = 1/2 second

// these variables are used to calculate the temperature
int   sensorValue;  // raw analog data
int   sensorMV;     // corresponding voltage (millivolts)
float tempCent;     // degrees Centigrade
float tempFahr;     // degrees Fahrenheit
float val;
 
//Light sensor
#define ADpin A5
int ADBuffer = 0;

//Buzzer
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

#define melodyPin 11
//Mario main theme melody
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,

  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underwolrd tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

//Serial communication
char face = 0;

void setup()
{
  Serial.begin(115200);
  irrecv.enableIRIn(); //Initializing IRremote
//  pinMode(12,1);

  analogWrite(LED_R,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，红色LED熄灭
  analogWrite(LED_G,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，绿色LED熄灭
  analogWrite(LED_B,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，蓝色LED熄灭
  
  myservo.attach(9);  // 9号引脚输出电机控制信号
                     //仅能使用PWM引脚
    // setup the pin for the temp sensor input
  pinMode(sensorPin, INPUT);  
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
//  analogReference(INTERNAL);
  pinMode(11, OUTPUT);//buzzer
  pinMode(13, OUTPUT);//led indicator when singing a note
}//setup
 
void loop() {
  if (irrecv.decode(&results)) {
  if(results.value==16724175)      //If 1 is pressed
  { 
    sts = 1;
//    Serial.print("STS = 1");
  }
  
  else if(results.value==16718055)   //If 2 is pressed
  {
    sts = 2;
//    Serial.println("STS = 2");
//   digitalWrite(12,0);            //turn off LED on PIN 12
//    Serial.println("Play Mario");    //Serial print
  }
    irrecv.resume(); // wait for the next signal
  }
  if ( sts == 1 )
  {
//    Serial.print(sts);
//  digitalWrite(12,1);                //light LED on PIN 12
//   Serial.println("turn on LED"); //Serial print
       // read the raw analog value of the temp sensor
  sensorValue = analogRead(sensorPin); 

  // an Arduino analog port returns a 10-bit value (0 - 1023)
  // convert it to an equivalent voltage level, in millivolts (between 0 and 5000, since the Arduino port is +5V)
  sensorMV = map(sensorValue, 0, 1023, 0, 4999  );

  // now convert this voltage to degrees Centigrade
  // this calculation comes from the spec of the specific sensor we are using:
  // TMP36, details here: http://www.adafruit.com/products/165
  tempCent = (sensorMV - 500) / 10.0;

  // and convert that to Fahrenheit
  tempFahr = (tempCent * 9 / 5.0) + 32.0;  // the standard formula you learned in high school


  // write the Fahrenheit value out to the serial port as ASCII text 
  // this will be in the format (xx.xx) because that is what the Arduino print library uses
  // and that is because the Arduino has no floating point processor, so it does the best it can
//  Serial.println(tempCent);

  // since temperature doesn't change so rapidly, we can set the delay here until the next check
  // this should also work with shorter or longer delays, or zero for ultra real-time (OK, 9600 baud...)
  delay (tempSampling); 
if (tempCent < 10) 
  {
  face = 'f';
  }
if (tempCent > 40) 
  {
  face = 'f';
  }
  
  if (tempCent > 10 && tempCent <40) 
  {
  face = 's';
  }

  val = map(tempCent, 0, 50, 179, 60);     // 利用“map”函数缩放该值，得到伺服电机需要的角度（0到180之间） 
  myservo.write(val);     // 设定伺服电机的位置
  
    if (InitialLedLoop < 1) {
     int i = 0;
    PWMValueR = 255;
    for(i = 0 ; i < 255 ; i++)		//红色逐渐变亮
    {
      analogWrite(LED_R,PWMValueR);
      analogWrite(LED_G,PWMValueG--);
      analogWrite(LED_B,PWMValueB);
      delay(12);									
    }
   // PWMValueG = 0;
    for(i = 0 ; i < 255 ; i++)		//逐渐变暗
    {
      analogWrite(LED_R,PWMValueR);
      analogWrite(LED_G,PWMValueG);
      analogWrite(LED_B,PWMValueB++);
      delay(12);
    }
    
   //  PWMValueB = 255;
    for(i = 0 ; i < 255 ; i++)		//绿色逐渐变亮
    {
      analogWrite(LED_R,PWMValueR--);
      analogWrite(LED_G,PWMValueG);
      analogWrite(LED_B,PWMValueB);
      delay(12);
    }
  //  PWMValueR = 0;
    for(i = 0 ; i < 255 ; i++)		//逐渐变暗
    {
      analogWrite(LED_R,PWMValueR);
      analogWrite(LED_G,PWMValueG--);
      analogWrite(LED_B,PWMValueB);
      delay(12);
    }
    
  //  PWMValueG = 255;
    for(i = 0 ; i < 255 ; i++)		//蓝色逐渐变亮
    {
      analogWrite(LED_R,PWMValueR--);
      analogWrite(LED_G,PWMValueG);
      analogWrite(LED_B,PWMValueB);
      delay(12);
    }
  //  PWMValueR = 0;
    for(i = 0 ; i < 255 ; i++)		//逐渐变暗
    {
      analogWrite(LED_R,PWMValueR);
      analogWrite(LED_G,PWMValueG);
      analogWrite(LED_B,PWMValueB--);
      delay(12);
    }
    InitialLedLoop++;
   }
  else {
    analogWrite(LED_R,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，红色LED熄灭
    analogWrite(LED_G,255);			//高电平255 = 占空比是100%，IO相当于输出高电平，绿色LED熄灭
    analogWrite(LED_B,255);
    }
    
  
  ADBuffer = analogRead(ADpin);		//读取AD值
//  Serial.print("AD = ");
//  Serial.println(ADBuffer);
  if(ADBuffer > 800)					//ADBuffer值大于设定值，相当于光照强度小于设定值
  {
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    if (tempCent > 40) {
      analogWrite(LED_R,0);
      analogWrite(LED_G,(tempCent - 40)*12.75);
      analogWrite(LED_B,255);
    }
    else if (tempCent > 30 && tempCent <40) {
      analogWrite(LED_R,(tempCent - 30)*22.5);
      analogWrite(LED_G,0);
      analogWrite(LED_B,255);
    }
    else if (tempCent > 20 && tempCent <30) {
      analogWrite(LED_R,255);
      analogWrite(LED_G,0);
      analogWrite(LED_B,(tempCent - 20)*22.5);
    }
    else if (tempCent > 0 && tempCent <20) {
      analogWrite(LED_R,255);
      analogWrite(LED_G,tempCent*12.75);
      analogWrite(LED_B,0);
    }
    
//    Serial.print("LEDS ON");		//点亮LED
  }
  else
  {
    digitalWrite(8, LOW);
    digitalWrite(7, LOW);
//    Serial.print("LEDS OFF");		//关闭LED
  }
  }
  else if (sts == 2) {
//    Serial.println(sts);
    Serial.println(face);
    //sing the tunes
  sing(1);
 // sing(1);
  sing(2);
  sts = 1;
  Serial.println('o');
  }
}//end of loop
int song = 0;

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
//    Serial.println(" 'UNDERWORD THEME'");
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];

      buzz(melodyPin, underworld_melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
  else {

//    Serial.println(" 'MARIO THEME'");
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {

      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];

      buzz(melodyPin, melody[thisNote], noteDuration);

      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);

      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);

    }
  }
}

void buzz(int targetPin, long frequency, long length) {
  digitalWrite(13, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
  digitalWrite(13, LOW);

  }

