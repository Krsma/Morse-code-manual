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

void setup(){  //initial values setup
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
  pause_value = map(analogRead(pot), 1023, 0, 70, 300); //setting up the pause_value variable via a potentiometer
  buttonState = !digitalRead(buttonPin); //inverting the value of buttonpin due to using input pullup with the button
                                       
  if(Serial.available() > 0) longclick = (Serial.read() == 't') ? true : false; //checking if the sound-disable button is on
  
  if (buttonState && lastButtonState){ //when the button is being continuously pressed
    signal_length++;       
    if (signal_length < 2*pause_value){
    tone(buzzer, 1500);  //turning on the buzzer and LED pins
    digitalWrite(ledPin, HIGH);
    }
    else if(longclick){
      tone(buzzer, 1000);  //sound and LED change if the button is held for long enough to be recognised as a dash (long click)
      analogWrite(ledPin, 50); 
      }
  }
  
  else if(!buttonState && lastButtonState){  //when the button is released 
     if (signal_length > 50 && signal_length < 2*pause_value ) 
         morse += dot;    // depending on the length of the click assign either dash or dot to morse variable
     else if (signal_length > 2*pause_value) 
         morse += dash;  //
         
    signal_length = 0; 
    digitalWrite(ledPin, LOW); //turning off the LED pin
    noTone(buzzer); //turning the buzzer off
  }
 
  else if(buttonState && !lastButtonState){  //when the button is just pressed
    pause = 0;   //value resets
    cheker = true;
    linecheker = true;
  }
  
  else if (!buttonState && !lastButtonState){  //when the button is continuously not pressed
    pause++;
    if (pause > 3*pause_value && cheker){ //checking if the pause between signals is long enough, if so trigger to part of the code which prints from morse to english
      translate(morse);  
      cheker = false;  //reset of values
      morse = "";  
    }
    if ((pause > 15*pause_value) && linecheker){  
      linecheker = false;
    }
  }
  
  lastButtonState = buttonState;  //assigning value to lastbuttonstate
  delay(1);
}

void translate(String text){  //more efficient managment of string to letter conversion
  int slovo=0;
  for (int i = 1; i < 35; i++)
  {
      if (text=="*-")  //ugly bodge but it works
      {
        slovo='a';
        break;
        }
      if (text == database[i]){  //comparing ascci values with position in a defined array
         if (i<26)        //this if block exists due to the ASCII encoding 
              slovo=65+i;
          
         else if (i>26) 
              slovo=48+i-27;
         
         break; 
      }
    }
    Serial.print((char)slovo);
}

