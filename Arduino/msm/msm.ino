#define buttonPin  2
#define ledPin 6
#define buzzer 9
#define pot A0

boolean buttonState, lastButtonState, cheker = false, linecheker = false;

int pause_value, signal_length = 0, pause = 0;

String morse;
char dash = '-', dot = '*';

void setup(){
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(ledPin, HIGH);
  tone(buzzer, 1500);
  delay(200);
  digitalWrite(ledPin, LOW);
  noTone(buzzer);
  
}

void loop() {
  pause_value = map(analogRead(pot), 0, 1023, 70, 300);
  buttonState = !digitalRead(buttonPin);
  
  if (buttonState && lastButtonState){
    signal_length++;       
    if (signal_length<2*pause_value){
    tone(buzzer, 1500);
    digitalWrite(ledPin, HIGH);
    }
    else{
      tone(buzzer, 1000);
      analogWrite(ledPin, 50);
      }
  }
  
  else if(!buttonState && lastButtonState){
     if (signal_length>50 && signal_length<2*pause_value ) morse += dot;
      else if (signal_length>2*pause_value) morse += dash;
    signal_length=0; 
    digitalWrite(ledPin, LOW); 
    noTone(buzzer); 
  }
 
  else if(buttonState && !lastButtonState){
    pause=0; 
    cheker = true;
    linecheker = true;
  }
  
  else if (!buttonState && !lastButtonState){  
    pause++;
    if (( pause>3*pause_value ) && (cheker)){ 
      translate();
      cheker = false;
      morse = "";
    }
    if ((pause>15*pause_value) && (linecheker)){
      linecheker = false;
    }
  }
  
  lastButtonState = buttonState;
  delay(1);
}
void translate(){
  
  if (morse=="*-")
    Serial.print("A");
  else if (morse=="-***")  
    Serial.print("B");
  else if (morse=="-*-*")  
    Serial.print("C");
  else if (morse=="-**")  
    Serial.print("D");
  else if (morse=="*")  
    Serial.print("E");
  else if (morse=="**-*")  
    Serial.print("F");
  else if (morse=="--*")  
    Serial.print("G");
  else if (morse=="****")  
    Serial.print("H");
  else if (morse=="**")  
    Serial.print("I");
  else if (morse=="*---")  
    Serial.print("J");
  else if (morse=="-*-")  
    Serial.print("K");
  else if (morse=="*-**")  
    Serial.print("L");
  else if (morse=="--")  
    Serial.print("M");
  else if (morse=="-*")  
    Serial.print("N");
  else if (morse=="---")  
    Serial.print("O");
  else if (morse=="*--*")  
    Serial.print("P");
  else if (morse=="--*-")  
    Serial.print("Q");
  else if (morse=="*-*")  
    Serial.print("R");
  else if (morse=="***")  
    Serial.print("S");
  else if (morse=="-")  
    Serial.print("T");
  else if (morse=="**-")  
    Serial.print("U");
  else if (morse=="***-")  
    Serial.print("V");
  else if (morse=="*--")  
    Serial.print("W");
  else if (morse=="-**-")  
    Serial.print("X");
  else if (morse=="-*--")  
    Serial.print("Y");
  else if (morse=="--**")  
    Serial.print("Z");

  else if (morse=="*----")  
    Serial.print("1");
  else if (morse=="**---")  
    Serial.print("2");
  else if (morse=="***--")  
    Serial.print("3");
  else if (morse=="****-")  
    Serial.print("4");
  else if (morse=="*****")  
    Serial.print("5");
  else if (morse=="-****")
    Serial.print("6");
  else if (morse=="--***")  
    Serial.print("7");
  else if (morse=="---**")  
    Serial.print("8");
  else if (morse=="----*")  
    Serial.print("9");
  else if (morse=="-----")  
    Serial.print("0");

}
