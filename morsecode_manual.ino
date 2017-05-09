//Made by Vladimir Krsmanovic
const int buttonPin = 2;    
const int ledPin = 13;      
const int buzzer = 9;

int ledState = HIGH;         
int buttonState = LOW;             
int lastButtonState = LOW;  
int doesitwork = LOW;  // variable used for debuging early versions of the code
int slovo=0;

int pause_value = 250;  // depending on your skill and how fast your fingers are you can change this value to make typing a message faster or slower
long signal_length = 0;
long pause = 0;

String database[36]={"*-","-***","-*-*","-**","*","**-*","--*","****","**","*---","-*-","*-**","--","-*","---","*--*","--*-","*-*","***","-","**-","***-","*--","-**-","-*--","--**","*----","**---","***--","****-","*****","-****","--***","---**","----*","-----"};

String morse = "";
String dash = "-";
String dot = "*";

boolean cheker = false;
boolean linecheker = false;

long lastDebounceTime = 0;  
long debounceDelay = 50;    
void setup()
{
  Serial.begin(9600);
  
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
  
  Serial.println("Welcome to Arduino-Uno morse machine");
  Serial.println("Using these values print out your message in morse and read out the message in english in the serial monitor");
  Serial.println("https://goo.gl/images/R4AIsW morse code values for learing");

  while(!digitalRead(buttonPin))
    ;
  
}

void loop() {
 
  buttonState = digitalRead(buttonPin);

  
  
  if (buttonState && lastButtonState)       // basic state machine depending on the state of the signal from the button
  {
    ++signal_length;       
    if (signal_length<2*pause_value)        //this help to notice that there is a change in the signal length aka that its not a dot anymore but a dash
    {                                       // best use for the measuring of signal_length would be use of the millis() but this was used  for simplicity 
    tone(buzzer, 1500) ;
    }
    else
    {
      tone(buzzer, 1000) ;
      }
  }
  else if(!buttonState && lastButtonState)          //this part of the code happens when the button is released and it send either * or - into the buffer
  {
     
     if (signal_length>50 && signal_length<2*pause_value )
     {
       morse =  morse + dot;
     } 
      else if (signal_length>2*pause_value)
      {
        morse = morse +  dash;
      }
    signal_length=0; 
    digitalWrite(13, LOW); 
    noTone(buzzer); 
  }
  else if(buttonState && !lastButtonState)          // this part happens when the button is pressed and its use to reset several values
  {
    pause=0;
    digitalWrite(13, HIGH);  
    cheker = true;
    linecheker = true;
  }
  else if (!buttonState && !lastButtonState)
  {  
    ++pause;
    if (( pause>3*pause_value ) && (cheker))
    { 
      printaj(morse);
      cheker = false;
      morse = "";
    }
    if ((pause>15*pause_value) && (linecheker))
    {
      Serial.println();
      linecheker = false;
    }
  }
  lastButtonState=buttonState;
  delay(1);
}
void printaj(String prevodilac)   //ugly part of the code but it works fine
{                                 //compare morse string to known morse values and print out the letter or a number 
                                  //the code is written based on the international morse code, one thing i changed is that insted of typing a special string to end the line it happens with enough delay  
  if (prevodilac=="*-")
    Serial.print("A");
  else if (prevodilac=="-***")  
    Serial.print("B");
  else if (prevodilac=="-*-*")  
    Serial.print("C");
  else if (prevodilac=="-**")  
    Serial.print("D");
  else if (prevodilac=="*")  
    Serial.print("E");
  else if (prevodilac=="**-*")  
    Serial.print("F");
  else if (prevodilac=="--*")  
    Serial.print("G");
  else if (prevodilac=="****")  
    Serial.print("H");
  else if (prevodilac=="**")  
    Serial.print("I");
  else if (prevodilac=="*---")  
    Serial.print("J");
  else if (prevodilac=="-*-")  
    Serial.print("K");
  else if (prevodilac=="*-**")  
    Serial.print("L");
  else if (prevodilac=="--")  
    Serial.print("M");
  else if (prevodilac=="-*")  
    Serial.print("N");
  else if (prevodilac=="---")  
    Serial.print("O");
  else if (prevodilac=="*--*")  
    Serial.print("P");
  else if (prevodilac=="--*-")  
    Serial.print("Q");
  else if (prevodilac=="*-*")  
    Serial.print("R");
  else if (prevodilac=="***")  
    Serial.print("S");
  else if (prevodilac=="-")  
    Serial.print("T");
  else if (prevodilac=="**-")  
    Serial.print("U");
  else if (prevodilac=="***-")  
    Serial.print("V");
  else if (prevodilac=="*--")  
    Serial.print("W");
  else if (prevodilac=="-**-")  
    Serial.print("X");
  else if (prevodilac=="-*--")  
    Serial.print("Y");
  else if (prevodilac=="--**")  
    Serial.print("Z");

  else if (prevodilac=="*----")  
    Serial.print("1");
  else if (prevodilac=="**---")  
    Serial.print("2");
  else if (prevodilac=="***--")  
    Serial.print("3");
  else if (prevodilac=="****-")  
    Serial.print("4");
  else if (prevodilac=="*****")  
    Serial.print("5");
  else if (prevodilac=="-****")
    Serial.print("6");
  else if (prevodilac=="--***")  
    Serial.print("7");
  else if (prevodilac=="---**")  
    Serial.print("8");
  else if (prevodilac=="----*")  
    Serial.print("9");
  else if (prevodilac=="-----")  
    Serial.print("0");
  
  Serial.print(" ");
    
  prevodilac=""; 
}

void printb(String prevodilac)
{
  slovo=0;
  for (int i = 1; i<35; i++)
    {
      if (prevodilac==database[i])
      {
         if (i<26)        
         slovo=65+i;
          
         else if (i>26) 
         slovo=48+i-27;
         
         break; 
      }
    }
    Serial.print(slovo);
    Serial.print(" ");

}


