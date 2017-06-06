#define buttonPin  2
#define ledPin 6
#define buzzer 9

boolean buttonState, lastButtonState, cheker = false, linecheker = false;

int pause_value, signal_length = 0, pause = 0;

String morse;
char dash = '-', dot = '*';

void setup(){
  Serial.begin(9600); 
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
}

void loop() {
  pause_value = map(analogRead(A0), 0, 1023, 85, 300);
  buttonState = !digitalRead(buttonPin);
  
  if (buttonState && lastButtonState){
    signal_length++;       
    if (signal_length<2*pause_value){
    tone(buzzer, 1500) ;
    analogWrite(ledPin, 255);
    }
    else{
      tone(buzzer, 1000) ;
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
      print(morse);
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
void print(String translate){
  
  if (translate=="*-")
    Serial.print("A");
  else if (translate=="-***")  
    Serial.print("B");
  else if (translate=="-*-*")  
    Serial.print("C");
  else if (translate=="-**")  
    Serial.print("D");
  else if (translate=="*")  
    Serial.print("E");
  else if (translate=="**-*")  
    Serial.print("F");
  else if (translate=="--*")  
    Serial.print("G");
  else if (translate=="****")  
    Serial.print("H");
  else if (translate=="**")  
    Serial.print("I");
  else if (translate=="*---")  
    Serial.print("J");
  else if (translate=="-*-")  
    Serial.print("K");
  else if (translate=="*-**")  
    Serial.print("L");
  else if (translate=="--")  
    Serial.print("M");
  else if (translate=="-*")  
    Serial.print("N");
  else if (translate=="---")  
    Serial.print("O");
  else if (translate=="*--*")  
    Serial.print("P");
  else if (translate=="--*-")  
    Serial.print("Q");
  else if (translate=="*-*")  
    Serial.print("R");
  else if (translate=="***")  
    Serial.print("S");
  else if (translate=="-")  
    Serial.print("T");
  else if (translate=="**-")  
    Serial.print("U");
  else if (translate=="***-")  
    Serial.print("V");
  else if (translate=="*--")  
    Serial.print("W");
  else if (translate=="-**-")  
    Serial.print("X");
  else if (translate=="-*--")  
    Serial.print("Y");
  else if (translate=="--**")  
    Serial.print("Z");

  else if (translate=="*----")  
    Serial.print("1");
  else if (translate=="**---")  
    Serial.print("2");
  else if (translate=="***--")  
    Serial.print("3");
  else if (translate=="****-")  
    Serial.print("4");
  else if (translate=="*****")  
    Serial.print("5");
  else if (translate=="-****")
    Serial.print("6");
  else if (translate=="--***")  
    Serial.print("7");
  else if (translate=="---**")  
    Serial.print("8");
  else if (translate=="----*")  
    Serial.print("9");
  else if (translate=="-----")  
    Serial.print("0");
  
  translate=""; 
}
