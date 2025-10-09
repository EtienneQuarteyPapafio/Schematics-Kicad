unsigned long newMs=600; //default variabel
unsigned long firstTap=0;
unsigned long secondTap=0;
bool waitingForSecondTap=false;

int lastTapState = LOW;  // To detect state change
unsigned long lastBlink=0;
bool ledState=LOW;

unsigned long lastDebounceTime = 0;  
const unsigned long debounceDelay = 60; // ms

void setup() {
  // put your setup code here, to run once:

  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT); //No floating variables
  Serial.begin(9600);
}

void loop() {

int tap=digitalRead(A1);

// Debounce
if (lastTapState !=tap){
 
  if(millis() - lastDebounceTime >= debounceDelay ){

    if (tap==HIGH && lastTapState==LOW && !waitingForSecondTap){
   
    firstTap=millis(); //When you press the switch finds current time
    Serial.println("first ");
    Serial.println(firstTap);
    lastDebounceTime = millis();
    waitingForSecondTap=1;
    lastTapState=tap;
     }

}

if(millis() - lastDebounceTime >= debounceDelay ){
if (tap==HIGH && lastTapState==LOW && waitingForSecondTap==1){

    secondTap=millis(); //When you press the switch finds current time
    newMs=secondTap-firstTap; //Time between taps
    Serial.println("second ");
    Serial.println(secondTap);
    Serial.print("New interval: ");
    Serial.println(newMs);
    lastDebounceTime = millis();
    waitingForSecondTap=false; //reset
    
}

}

}
//blink LED
if (millis()-lastBlink>=(newMs/2)){
 ledState=!ledState;
digitalWrite(A0, ledState); 
lastBlink=millis();
}
lastTapState=tap;

}

