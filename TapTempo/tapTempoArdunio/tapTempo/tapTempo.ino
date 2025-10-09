//Variables
bool ledState=HIGH; //state of LED
unsigned long lastBlink=0; //last time LED was on

int tapState;
int lastTapState = LOW;  // previous reading from input pin
bool waitingForSecondTap=false;

unsigned long newMs=600; //default Ms
unsigned long firstTap=0; //Ms of first tap
unsigned long secondTap=0; //Ms ofs second tap

unsigned long lastDebounceTime = 0;  //last time input was toggled
const unsigned long debounceDelay = 60; // debounce time

void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT); //To read high or low

  pinMode(A1, OUTPUT); //For LED

  Serial.begin(9600);
}

void loop() {
//read state of switch
int tap=digitalRead(A0);

// If the switch changed, due to noise or pressing:
  if (tap != lastTapState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
    
  }

  if(millis() - lastDebounceTime > debounceDelay ){
  //if what we are reading is longer than the debounce

    //if button state has changed
    if (tap != tapState){
      tapState =tap;

    if (tap==HIGH && !waitingForSecondTap){
   
    firstTap=millis(); //When you press the switch finds current time
    Serial.println("first ");
    Serial.println(firstTap);
    //lastDebounceTime = millis();
    waitingForSecondTap=1;
    //lastTapState=tap;
     }

     else if (tap==HIGH && waitingForSecondTap==1){

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
digitalWrite(A1, ledState); 
lastBlink=millis();
}
lastTapState=tap;

}

