#define buttonPin  2
#define ledPin 6
#define buzzer 9
#define pot A0

bool buttonState, lastButtonState, cheker = false, linecheker = false, longclick = true;

int pause_value, signal_length = 0, pause = 0;

String database[36]={"*-","-***","-*-*","-**","*","**-*","--*","****","**","*---","-*-","*-**","--","-*","---","*--*","--*-","*-*","***","-","**-","***-","*--","-**-","-*--","--**","*----","**---","***--","****-","*****","-****","--***","---**","----*","-----"};
//array which is latter used for conversion to char
String morse="";
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

  if(Serial.available() > 0) longclick = (Serial.read() == 't') ? true : false; //checking if the sound-disable button is on
  
  if (buttonState && lastButtonState){
    signal_length++;       
    if (signal_length < 2*pause_value){
    tone(buzzer, 1500);
    digitalWrite(ledPin, HIGH);
    }
    else if(longclick){
      tone(buzzer, 1000);
      analogWrite(ledPin, 50);
      }
  }
  
  else if(!buttonState && lastButtonState){
     if (signal_length > 50 && signal_length < 2*pause_value ) morse += dot;
      else if (signal_length > 2*pause_value) morse += dash;
    signal_length = 0; 
    digitalWrite(ledPin, LOW); 
    noTone(buzzer); 
  }
 
  else if(buttonState && !lastButtonState){
    pause = 0; 
    cheker = true;
    linecheker = true;
  }
  
  else if (!buttonState && !lastButtonState){  
    pause++;
    if (pause > 3*pause_value && cheker){ 
      translate(morse);
      cheker = false;
      morse = "";
    }
    if ((pause > 15*pause_value) && linecheker){
      linecheker = false;
    }
  }
  
  lastButtonState = buttonState;
  delay(1);
}

void translate(String text){  //more efficient managment of string to letter conversion
  int slovo=0;
  for (int i = 1; i<35; i++)
    {
      if (text == database[i])  //comparing ascci values with position in a defined array
      {
         if (i<26)        
              slovo=65+i;
          
         else if (i>26) 
              slovo=48+i-27;
         
         break; 
      }
    }
    text = char(slovo);  // conversion from int to char
    Serial.print(text);
    Serial.print(" ");

  
  

}

