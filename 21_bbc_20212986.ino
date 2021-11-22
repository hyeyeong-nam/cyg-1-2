// Arduino pin assignment
#include <Servo.h>
#define PIN_IR A0
#define PIN_LED 9
#define PIN_SERVO 10

#define _DUTY_MIN 540 // servo full clockwise position (0 degree)
#define _DUTY_NEU 1380 // servo neutral position (90 degree)
#define _DUTY_MAX 2420 // servo full counterclockwise position (180 degree)

Servo myservo;
float dist_min, dist_max, dist_neu;

int a, b; // unit: mm

void setup() {
// initialize GPIO pins
  pinMode(PIN_LED,OUTPUT);
  digitalWrite(PIN_LED, 1);
  myservo.attach(PIN_SERVO); 
  myservo.writeMicroseconds(1320);
  
  
// initialize serial port
  Serial.begin(57600);

  a = 88;
  b = 390;
}

float ir_distance(void){ // return value unit: mm
  float val;
  float volt = float(analogRead(PIN_IR));
  val = ((6762.0/(volt-9.0))-4.0) * 10.0;
  return val;
}

void loop() {
  float raw_dist = ir_distance();
  float dist_cali = 100 + 300.0 / (b - a) * (raw_dist - a);
  Serial.print("min:0,max:500,dist:");
  Serial.print(raw_dist);
  Serial.print(",dist_cali:");
  Serial.println(dist_cali);
  if(raw_dist > 225){ 
    digitalWrite(PIN_LED, 0);
     myservo.writeMicroseconds(1690);
  }
  else {digitalWrite(PIN_LED, 255);
   myservo.writeMicroseconds(1480);
  delay(20);
  }
}
