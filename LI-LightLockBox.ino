const int btn1 = 6;
const int btn2 = 7;
const int btn3 = 8;
const int btn4 = 9;
const int led1 = 2;
const int led2 = 3;
const int led3 = 4;
const int led4 = 5;
const int redLed = 11;
const int greenLed = 10;

const blinkDelay(200);

const int sequence[6] = {4,2,4,1,2,3};
volatile int myseq[6] = {0,0,0,0,0,0};

volatile int step = 0;
volatile int mystep = 0;
volatile bool result = false;

int checkButton(){
  int btn = 0;
  while(btn == 0) {
    for(int i = 6; i < 10; i++){
      if(digitalRead(i) == 0){ btn = i;}
    }
  }
  return btn - 5;
}

void blinkLed(int led){
  digitalWrite(led+1, 1);
  delay(blinkDelay);
  digitalWrite(led+1, 0);
  delay(blinkDelay);
}

void blinkSequence(){
  for(int i = 0; i <= step; i++){
    blinkLed(sequence[i]);
  }
}
void setup() {
  Serial.begin(9600);
  for(int i = 2; i < 6; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, 1);
    delay(500);
    digitalWrite(i, 0);
  }
  for(int i = 6; i < 10; i++){
    pinMode(i, INPUT_PULLUP);  
  }
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  digitalWrite(redLed, 1);
  delay(500);
  digitalWrite(redLed, 0);
}

void loop() {
  while(result == false){
    for(int i = 0; i <= step; i++){
      Serial.print("Boucle Step = ");
      Serial.println(step);
      blinkSequence();
      for(int a = 0; a <= step; a++){
        Serial.print("Boucle MyStep = ");
        Serial.println(mystep);
        int test = checkButton();
        Serial.print("Button = ");
        Serial.println(test);
        myseq[step] = test;
        if(myseq[step] == sequence[mystep]){
          blinkLed(test);
          mystep++;
        }
        else{
          step = 0;
          mystep = 0;
          digitalWrite(redLed, 1);
          delay(1000);
          digitalWrite(redLed, 0);
          return;
        }
      }
      step += 1;
      mystep = 0;
      Serial.print("fin avec step = ");
      Serial.println(step);
      if(step == 6){
        step = 0;
        result = true;
        return;
     
    }
    }
  }
  for(int i = 0; i < 5; i++){
    digitalWrite(greenLed, 1);
    delay(100);
    digitalWrite(greenLed, 0);
    delay(100);
  }
  digitalWrite(greenLed, 1);
  //OUVERTURE SERRURE
  delay(5000);
  digitalWrite(greenLed,0);
  digitalWrite(redLed, 1);
  //FERMETURE SERRURE
  delay(2000);
  digitalWrite(redLed, 0);  
  result = false;
  
}
