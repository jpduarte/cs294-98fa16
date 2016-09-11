/*
 Pushbutton interrupt example with debouncing
 for RedBear Duo with internal pull-down resistor.

 
 Blink an LED as long as a button is pressed.
 Adapted from the Particle Photon documentation.
 modified 29 Aug 2016
 by Bjoern Hartmann for RedBear Duo
 
 The circuit:
 * internal LED on D7
 * pushbutton connected to D1 and 3V3
 
 see https://docs.particle.io/reference/firmware/photon/#attachinterrupt-
 */

// do not use the cloud functions - assume programming through Arduino IDE
#if defined(ARDUINO) 
SYSTEM_MODE(MANUAL); 
#endif

// note: Particle documentation states external interrupts
// DO NOT work on D0 and A5, so we choose D1 instead
const int button = D0;                      // button is connected to D0 and 3V3
const int button1 = D1;                      // button is connected to D1 and 3V3
const int button2 = D2;                      // button is connected to D1 and 3V3
const int button3 = D3;                      // button is connected to D1 and 3V3
const int button4 = D4;                      // button is connected to D1 and 3V3

void toggle(void);
void isr(void);

long debounceDelay = 50;    // the debounce time in ms
volatile int updatekeyboard = 0;
volatile int buttonpressed = 0;
String chars1 = "ABCDEF  ";
String chars2 = "GHIJKL  ";
String chars3 = "MNOPQRS ";
String chars4 = "TUVWXYZ ";
int state0 = 0;
int state1 = 0;
int state2 = 0;
String sentence = "";


Timer timer(debounceDelay, toggle, true); // oneshot

void setup()
{
  Serial.begin(115200);

  pinMode(button, INPUT_PULLDOWN);
  pinMode(button1, INPUT_PULLDOWN);
  pinMode(button2, INPUT_PULLDOWN);
  pinMode(button3, INPUT_PULLDOWN); 
  pinMode(button4, INPUT_PULLDOWN);   
  
  attachInterrupt(button, isr, CHANGE); //CHANGE, RISING or FALLING  
  attachInterrupt(button1, isr, CHANGE); //CHANGE, RISING or FALLING 
  attachInterrupt(button2, isr, CHANGE); //CHANGE, RISING or FALLING  
  attachInterrupt(button3, isr, CHANGE); //CHANGE, RISING or FALLING   
  attachInterrupt(button4, isr, CHANGE); //CHANGE, RISING or FALLING  
  delay(5000);
  printkeyboard();
}

void loop()
{
  String stringaux = "";
  
  if(updatekeyboard==1){
    //this flag is set to 0 so its not printed this all over again
    updatekeyboard=0;  

    if (buttonpressed==5) { 
        Serial.println("Character: Space");    
        sentence = sentence+" ";
        Serial.println("Sentence: "+sentence);       
        state0=0;
        state1=0;
        state2=0;
        printkeyboard();       
    } else {
      //enter value at each state in order, check it is filled up or not then add it
      if (state0==0){
        state0 = buttonpressed;
      } else if (state1==0){
        state1 = buttonpressed;
      } else {
        state2 = buttonpressed;
      } 
  
      //print keyboard and current values states
      printkeyboard();
  
      //reset all states to zero
      if (state2>0) {
        switch (state0) {
            case 1:
              stringaux = chars1;
              break;
            case 2:
              stringaux = chars2;
              break;    
            case 3:
              stringaux = chars3;
              break;
            case 4:
              stringaux = chars4;
              break;                        
            default: 
              ;
              break;
          } 
  
        switch (state1) {
            case 1:
              stringaux = stringaux.substring(0,2);
              break;
            case 2:
              stringaux = stringaux.substring(2,4);
              break;    
            case 3:
              stringaux = stringaux.substring(4,6);
              break;
            case 4:
              stringaux = stringaux.substring(6,8);
              break;                        
            default: 
              ;
              break;
          } 
        switch (state2) {
            case 1:
              stringaux = stringaux.charAt(0);
              break;
            case 2:
              stringaux = stringaux.charAt(1);
              break;    
            case 3:
              stringaux = "";
              break;
            case 4:
              stringaux = "";
              break;                        
            default: 
              ;
              break;
          }  
        Serial.println("Character: "+stringaux);    
        sentence = sentence+stringaux;
        Serial.println("Sentence: "+sentence);       
        state0=0;
        state1=0;
        state2=0;
        printkeyboard(); 
        }      
      
    }

   
    
  }
}

void toggle() {

      if(digitalRead(button)==HIGH){
        updatekeyboard = 1;
        buttonpressed = 1;
      }
      if(digitalRead(button1)==HIGH){
        updatekeyboard = 1;
        buttonpressed = 2;
      }    
      if(digitalRead(button2)==HIGH){
        updatekeyboard = 1;
        buttonpressed = 3;
      }  
      if(digitalRead(button3)==HIGH){
        updatekeyboard = 1;
        buttonpressed = 4;
      } 
      if(digitalRead(button4)==HIGH){
        updatekeyboard = 1;
        buttonpressed = 5;
      }       

}

void isr()
{ 
  noInterrupts();
  if(digitalRead(button)==HIGH){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else if(digitalRead(button1)==HIGH){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else if(digitalRead(button2)==HIGH){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else if(digitalRead(button3)==HIGH){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else if(digitalRead(button4)==HIGH){
    timer.resetFromISR(); //start or reset timer on every rising edge
  } else {
    timer.stopFromISR(); //stop on falling edge
  } 
  interrupts(); 
}

void printkeyboard() {
  
  String stringaux1 = chars1;
  String stringaux2 = chars2;
  String stringaux3 = chars3;
  String stringaux4 = chars4;
  String stringaux;  
  Serial.print(state0);
  Serial.print(state1);
  Serial.println(state2);
  
  //choose string of characters at 4 positions, first choose
  switch (state0) {
    case 1:
      stringaux = stringaux1;
      break;  
    case 2:
      stringaux = stringaux2;
      break;
    case 3:
      stringaux = stringaux3;
      break; 
    case 4:
      stringaux = stringaux4;
      break;                                 
    default: 
      ;
      break;
  } 
  if (state0>0){
      stringaux1 = stringaux.substring(0,2);
      stringaux2 = stringaux.substring(2,4);
      stringaux3 = stringaux.substring(4,6);
      stringaux4 = stringaux.substring(6,8);  
  }
  
  
  //choose string of characters at 4 positions, second choose
  switch (state1) {
    case 1:
      stringaux = stringaux1;
      break;  
    case 2:
      stringaux = stringaux2;
      break;
    case 3:
      stringaux = stringaux3;
      break; 
    case 4:
      stringaux = stringaux4;
      break;                                 
    default: 
      ;
      break;
  } 
  if (state1>0){
      stringaux1 = stringaux.substring(0,1);
      stringaux2 = stringaux.substring(1,2);
      stringaux3 = stringaux.substring(2,3);
      stringaux4 = stringaux.substring(3,4);  
  }

  //this print keyboard in a "pretty" way
  //////////////////////////////////////////////////print horizontal
  Serial.print("-");
  for (int i=0; i <= stringaux4.length(); i++){
        Serial.print("-");
     }
  Serial.print("-");
  for (int i=0; i <stringaux1.length(); i++){
        Serial.print("-");
     } 
  Serial.print("-");    
  for (int i=0; i < stringaux2.length(); i++){
        Serial.print("-");
     } 
  Serial.println("-");      
 /////////////////////////////////////////////////
  //print first row letters    
  Serial.print("|");
  for (int i=0; i <= stringaux4.length(); i++){
        Serial.print(" ");
     }
  Serial.print("|");
  Serial.print(stringaux1);
  Serial.println("|");

  //////////////////////////////////////////////////print horizontal
  Serial.print("-");
  for (int i=0; i <= stringaux4.length(); i++){
        Serial.print("-");
     }
  Serial.print("-");
  for (int i=0; i <stringaux1.length(); i++){
        Serial.print("-");
     } 
  Serial.print("-");    
  for (int i=0; i < stringaux2.length(); i++){
        Serial.print("-");
     } 
  Serial.println("-");      
 /////////////////////////////////////////////////


  //first second row of letters
  Serial.print("|");
  Serial.print(stringaux4);
  Serial.print(" |");
  for (int i=0; i < stringaux1.length(); i++){
        Serial.print(" ");
     }
  Serial.print("|");
  Serial.print(stringaux2);
  Serial.println("|");

  //////////////////////////////////////////////////print horizontal
  Serial.print("-");
  for (int i=0; i <= stringaux4.length(); i++){
        Serial.print("-");
     }
  Serial.print("-");
  for (int i=0; i <stringaux1.length(); i++){
        Serial.print("-");
     } 
  Serial.print("-");    
  for (int i=0; i < stringaux2.length(); i++){
        Serial.print("-");
     } 
  Serial.println("-");      
 /////////////////////////////////////////////////

  //print last row of letters
  Serial.print("|");
  for (int i=0; i <= stringaux4.length(); i++){
        Serial.print(" ");
     }  
  Serial.print("|");   
  Serial.print(stringaux3);
  Serial.println("|");

  //////////////////////////////////////////////////print horizontal
  Serial.print("-");
  for (int i=0; i <= stringaux4.length(); i++){
        Serial.print("-");
     }
  Serial.print("-");
  for (int i=0; i <stringaux1.length(); i++){
        Serial.print("-");
     } 
  Serial.print("-");    
  for (int i=0; i < stringaux2.length(); i++){
        Serial.print("-");
     } 
  Serial.println("-");      
 /////////////////////////////////////////////////  
         
}


