#define RFPIN 2
#define BTNPIN 3

// void readSerial(){
//   if (Serial.available() > 0) {
//     String CMD = Serial.readString();
//     CMD.trim();
//     Serial.print(">>");
//     Serial.println(CMD);
//     //
//     mode = CMD;
//   }
// }

void playNote(int hz, float factor = 0.5){
  int notef = 1000.00/hz/2*1000.00;
  Serial.println(hz);
  Serial.println(notef);
  Serial.println("---");
  int time = hz * factor;
  for(int i = 0; i<=time;i++){
    digitalWrite(RFPIN, 1);
    delayMicroseconds(notef);
    digitalWrite(RFPIN, 0);
    delayMicroseconds(notef);
  }
}


void test1(){
  for(int i =0; i<50;i++){
    digitalWrite(RFPIN, 1);
    delay(i);
    digitalWrite(RFPIN, 0);
    delay(i);
  }
}

void test2(){
  for(int i = 0; i < 500; i++){
    digitalWrite(RFPIN, 1);
    delay(1);
    digitalWrite(RFPIN, 0);
    delay(1);
  }
  for(int i = 0; i < 5; i++){
    digitalWrite(RFPIN, 1);
    delay(100);
    digitalWrite(RFPIN, 0);
    delay(100);
  }
}

void test3(){
  for(int i =0; i<2000;i++){
    digitalWrite(RFPIN, 1);
    delayMicroseconds(i);
    digitalWrite(RFPIN, 0);
    delayMicroseconds(i);
  }
}
void test3b(){
  for(int i =2000; i<3000;i++){
    digitalWrite(RFPIN, 1);
    delayMicroseconds(i);
    digitalWrite(RFPIN, 0);
    delayMicroseconds(i);
  }
}



void test4(){
  playNote(440);
  playNote(523);
  playNote(659);

  playNote(440);
  playNote(523);
  playNote(659);

  playNote(587);
  playNote(698);
  playNote(880);

  playNote(587);
  playNote(698);
  playNote(988, 0.25);
  playNote(880, 0.25);

  playNote(330);
  playNote(294);
  playNote(330);
  
  playNote(220);
  playNote(294);
  playNote(330);
}

void testAR(){
  for(int i=5000; i>0; i--){
    digitalWrite(RFPIN, 1);
    delayMicroseconds(i);
    digitalWrite(RFPIN, 0);
    delayMicroseconds(i);
    i--;
  }
}

void testPOT(){
  int aRead = analogRead(A0);
  if(aRead<100){
    aRead = 100;
  }
  aRead = aRead * 2.75;
  digitalWrite(RFPIN, 1);
  delayMicroseconds(aRead);
  digitalWrite(RFPIN, 0);
  delayMicroseconds(aRead);
}


void testPOT2(){
  int aRead = analogRead(A0);
  float f = (aRead/1000)*0.01;
  playNote(440+aRead,f);
  playNote(523+aRead,f);
  playNote(659+aRead,f);

  playNote(587+aRead,f);
  playNote(698+aRead,f);
  playNote(880+aRead,f);
}

void testPOT3(){
  //strange
  int aRead = analogRead(A0);
  float f = 0.01;
  playNote(440+aRead,f);
  playNote(523+aRead,f);
  playNote(659+aRead,f);

  playNote(587+aRead,f);
  playNote(698+aRead,f);
  playNote(880+aRead,f);
}

void testPOT4(){
  int aRead = analogRead(A0);
  //int w = aRead * 0.019;
  int w = aRead * 20;
  digitalWrite(RFPIN, 1);
  delayMicroseconds(w);
  digitalWrite(RFPIN, 0);
  delayMicroseconds(w);
}

void setup(){
  Serial.begin(115200);
  pinMode(RFPIN, OUTPUT);
  //pinMode(BTNPIN, INPUT);
  pinMode(BTNPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BTNPIN), changeMode, RISING);
}

int mode = 0;
bool btnp = 0;
int LIMIT = 9;

void changeMode(){
  mode++;
  if(mode>LIMIT){
    mode = 0;
  }
  Serial.println(mode);
  for(int x=3; x < mode+4; x++){
    for(int i =0; i < 400; i++){
      digitalWrite(RFPIN, 1);
      delayMicroseconds(i);
      digitalWrite(RFPIN, 0);
      delayMicroseconds(i);
    }
  }
}

void loop(){
  
  //
  switch(mode){
    case 0:
      testAR();
      break;
    case 1:
      test1();
      break;
    case 2:
      test2();
      break;
    case 3:
      test3();
      break;
    case 4:
      test3b();
      break;
    case 5:
      test4();
      break;
    case 6:
      testPOT();
      break;
    case 7:
      testPOT2();
      break;
    case 8:
      testPOT3();
      break;
    case 9:
      testPOT4();
      break;
  }
}