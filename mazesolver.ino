#define LMF 10
#define LMR 11
#define RMF 5
#define RMR 6

#define MAX_SPEED 255

#define baseSpeed 80

//#define DEBUG

#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif


float distance[5], duration[5];
const int trig[5] = {13, 12, 9, 8, 7};
const int echo[5] = {A4, A3, A2, A1, A0};

void setup() {
  Serial.begin(115200);
  for (int i = 0; i < 5; i++) {
    pinMode(trig[i], OUTPUT);
  }
  for (int i = 0; i < 5; i++) {
    pinMode(echo[i], INPUT);
  }
  for (int i = 0; i < 5; i++) {
    digitalWrite(trig[i], LOW);
  }
  pinMode(5, OUTPUT);
  analogWrite(5, 70);

  pinMode(A5, INPUT);

  pinMode(LMF, OUTPUT);
  pinMode(RMF, OUTPUT);
  pinMode(LMR, OUTPUT);
  pinMode(RMR, OUTPUT);

  moveMotor(81, 80);
  delay(100);
  /*while(1){
    Serial.println(abs(getDistance(0) - getDistance(1)),DEC);
    }*/
}

void loop() {

  if (getDistance(1) < 7.5 ) {
    analogWrite(RMF, 0);
    delay(10);
    analogWrite(RMF, 80);
    delay(10);
  }

  if (getDistance(0) < 7.5 ) {
    analogWrite(LMF, 0);
    delay(10);
    analogWrite(LMF, 81);
    delay(10);
  }

  if (!digitalRead(A5)) {
    moveMotor(0, 0);
    moveMotor(-61, -60);
    delay(500);
    if (getDistance(0) > getDistance(1)) {
      moveMotor(81, -80);
      delay(290);
      moveMotor(0, 0);
      delay(200);
      moveMotor(-81, -80);
      delay(800);
      moveMotor(81, 80);
    } else {
      moveMotor(-81, 80);
      delay(290);
      moveMotor(0, 0);
      delay(200);
      moveMotor(-81, -80);
      delay(800);
      moveMotor(81, 80);
    } 
  }

  if (getDistance(2) < 10 ) {
    moveMotor(0, 0);
    moveMotor(-51, -50);
    delay(100);

    if (getDistance(0) > 25 && getDistance(1)> 25) {
      moveMotor(-81, 80);
      delay(290);
      moveMotor(0, 0);
      delay(200);
      moveMotor(81, 80);
    } else if (getDistance(0) > getDistance(1)) {
      moveMotor(81, -80);
      delay(290);
      moveMotor(0, 0);
      delay(200);
      moveMotor(-81, -80);
      delay(800);
      moveMotor(81, 80);
    } else {
      moveMotor(-81, 80);
      delay(290);
      moveMotor(0, 0);
      delay(200);
      moveMotor(-81, -80);
      delay(800);
      moveMotor(81, 80);
    }

  }

  if (getDistance(1) < 13 && getDistance(2) > 50) {
    Serial.println("turn detected");
    //int _tmp = getDistance(2);
    /*while (abs(_tmp - getDistance(2)) < 16) {
      moveMotor(80, 80);
      }
    */
    for (int i = 0; i < 150; i++) {
      Serial.println(i, DEC);
      if (getDistance(2) < 10) {
        break;
      }
    }

    if (getDistance(1) > 25) {
      Serial.println("turn left");

      moveMotor(-81, 80);
      delay(280);
      moveMotor(0, 0);
      delay(200);
      moveMotor(-81, -80);
      delay(800);
      moveMotor(81, 80);
    }
  }
}

void moveMotor(int m1Speed, int m2Speed) {
  if (m1Speed > 0 ) {
    analogWrite(LMF, m1Speed);
    analogWrite(LMR, 0);
  } else {
    analogWrite(LMF, 0);
    analogWrite(LMR, -m1Speed);
  }
  if (m2Speed > 0) {
    analogWrite(RMF, m2Speed);
    analogWrite(RMR, 0);
  } else {
    analogWrite(RMF, 0);
    analogWrite(RMR, -m2Speed);
  }
}

int getDistance(int i) {
  digitalWrite(trig[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trig[i], LOW);
  duration[i] = pulseIn(echo[i], HIGH);
  distance[i] = duration[i] * 0.034 / 2;

#ifdef DEBUG
  if (distance[i] > 0) {
    Serial.print(distance[i], DEC);
    Serial.print(" ");
  }
#endif
  return distance[i];
}

