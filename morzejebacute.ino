
const int buttonPin = 2;    
const int ledPin = 13;      
const int buzzer = 9;

int ledState = HIGH;         
int buttonState = LOW;             
int lastButtonState = LOW;  
int doesitwork = LOW;
int jedinica = 250;
long duzina = 0;
long pauza = 0;

String morze = "";
String crta = "-";
String tacka = "*";

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
  
  Serial.println("Doborodosli u morze masinu");
  Serial.println("Pomocu tabele pored Arduina, ispisite svoju poruku u morzeovom kodu");
  Serial.println("I Gledajte rezultat na ekranu");

  while(!digitalRead(buttonPin))
    ;
  
}

void loop() {
 
  buttonState = digitalRead(buttonPin);

  
  
  if (buttonState && lastButtonState)       //meri duzinu klika
  {
    ++duzina;
    tone(buzzer, 2000); 
    
  }
  else if(!buttonState && lastButtonState)          //u zavisnoti od duzine ubacuje ili * ili - u string
  {
     
     if (duzina>50 && duzina<2*jedinica )
     {
       morze =  morze + tacka;
     } 
      else if (duzina>2*jedinica)
      {
        morze = morze +  crta;
      }
    duzina=0; 
    digitalWrite(13, LOW); 
    noTone(buzzer); 
  }
  else if(buttonState && !lastButtonState)          
  {
    pauza=0;
    digitalWrite(13, HIGH);  
    cheker = true;
    linecheker = true;
  }
  else if (!buttonState && !lastButtonState)
  {  
    ++pauza;
    if (( pauza>3*jedinica ) && (cheker))
    { 
      printaj(morze);
      cheker = false;
      morze = "";
    }
    if ((pauza>15*jedinica) && (linecheker))
    {
      Serial.println();
      linecheker = false;
    }
  }
  lastButtonState=buttonState;
  delay(1);
}
void printaj(String prevodilac)
{  

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
