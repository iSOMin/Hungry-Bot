#include <Adafruit_LEDBackpack.h>
#include <Adafruit_GFX.h>
#include <Wire.h>

#define MATRIX_SIZE 8
#define NONE 0
#define RED 1
#define GREEN 2
#define BLUE 3
#define DELAY_COUNT 2

int s0 = 3;           //Output frequency scaling selection inputs
int s1 = 4;           //Output frequency scaling selection inputs
int s2 = 5;           //Photodiode type selection inputs
int s3 = 6;           //Photodiode type selection inputs
int out = 2;          //Output frequency
int flag = 0;
int counter = 0;

int countR = 0;
int countG = 0;
int countB = 0;

int state;
int prevState;
int count;
int value;

Adafruit_8x8matrix matrix = Adafruit_8x8matrix();


void setup() {
     Serial.begin(115200);
      
     Serial.println("8x8 LED Matrix hungry test");
 
     matrix.begin(0x70);       //pass in the address

     pinMode(s0,OUTPUT);
     pinMode(s1,OUTPUT); 
     pinMode(s2,OUTPUT);
     pinMode(s3,OUTPUT);

    state = NONE;
    count = 0;
    matrix.setRotation(0);
}

void TCS() {
     flag=0;  
     digitalWrite(s1,HIGH);
     digitalWrite(s0,LOW);
     //digitalWrite(s1,HIGH);
     //digitalWrite(s0,HIGH);
     //digitalWrite(s2,LOW);
     //digitalWrite(s3,LOW);
     attachInterrupt(0, ISR_INTO, CHANGE);
     timer2_init();
}

void ISR_INTO()
 {
   counter++;
 }

 void timer2_init(void)
 {
    TCCR2A=0x00;
    TCCR2B=0x07;   //the clock frequency source 1024 points
    TCNT2= 100;    //10 ms overflow again
    TIMSK2 = 0x01; //allow interrupt
 }

 ISR(TIMER2_OVF_vect)//the timer 2, 10ms interrupt overflow again. Internal overflow interrupt executive function
{
    TCNT2=100;
    flag++; 
    if(flag==1)  {                      // flag가 1이면
        counter = 0;
    }  else if(flag==2)  {              // flag가 2이면
        countR=counter/1.051;
        //Serial.print("red=");
        //Serial.println(countR,DEC);
        digitalWrite(s2,HIGH);
        digitalWrite(s3,HIGH);
    }   else if(flag==3)  {             // flag가 3이면
        countG=counter/1.0157;
        //Serial.print("green=");
        //Serial.println(countG,DEC);
        digitalWrite(s2,LOW);
        digitalWrite(s3,HIGH);
    }   else if(flag == 4)  {           // flag가 4이면
        countB=counter/1.114;
        //Serial.print("blue=");
        //Serial.println(countB,DEC);
        //Serial.println("\n"); 
        digitalWrite(s2,LOW);
        digitalWrite(s3,LOW);
        
    }   else {
        flag = 0;
        //TIMSK2 = 0x00;
    }
    counter = 0;
}

//input red
static const uint8_t PROGMEM 
    heart[][MATRIX_SIZE] = 
    {
        {
            B00000000,
            B01100110,
            B11111111,
            B11111111,
            B01111110,
            B00111100,
            B00011000,
            B00000000 }
          , 
        {
            B00000000,
            B00100100,
            B01111110,
            B01111110,
            B00111100,
            B00011000,
            B00000000,
            B00000000 }
    };

//input green  
static const uint8_t PROGMEM 
    monster[][MATRIX_SIZE] =
    {
        {
            B00000000,
            B00000000,
            B00000000,
            B00000001,
            B00000001,
            B00000001,
            B00000001,
            B00000001}
          ,
        {
            B00000000,
            B00000001,
            B00000001,
            B00000011,
            B00000010,
            B00000011,
            B00000010,
            B00000010}
          ,
        {
            B00000001,
            B00000010,
            B00000011,
            B00000111,
            B00000101,
            B00000111,
            B00000101,
            B00000101}
          ,
        {
            B00000100,
            B00000100,
            B00000111,
            B00001111,
            B00001011,
            B00001111,
            B00001010,
            B00001010}
          ,
        {
            B00000100,
            B00001001,
            B00001111,
            B00011111,
            B00010110,
            B00011111,
            B00010101,
            B00010101}
          ,
        {
            B00010010,
            B00010010,
            B00011110,
            B00111111,
            B00101101,
            B00111111,
            B00101010,
            B00101010}
         ,
        {
            B00010010,
            B00100100,
            B00111100,
            B01111110,
            B01011010,
            B01111110,
            B01010100,
            B01010100}
          ,
        {
            B01001000,
            B01001000,
            B01111000,
            B11111100,
            B10110100,
            B11111100,
            B10110100,
            B10110100}
        ,
        {
            B01001000,
            B10010000,
            B11110000,
            B11111000,
            B01101000,
            B11111000,
            B01010000,
            B01010000}
          ,
        {
            B00100000,
            B00100000,
            B11100000,
            B11110000,
            B11010000,
            B11110000,
            B10100000,
            B10100000}
          ,
       {
            B00100000,
            B01000000,
            B11000000,
            B11100000,
            B10100000,
            B11100000,
            B01000000,
            B01000000}
           ,
       {
            B10000000,
            B10000000,
            B10000000,
            B11000000,
            B01000000,
            B11000000,
            B10000000,
            B10000000}
          ,
        {
            B10000000,
            B00000000,
            B00000000,
            B10000000,
            B10000000,
            B10000000,
            B00000000,
            B00000000}
          ,
        {
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B00000000,
            B00000000}
          ,
        {
            B00000000,
            B00000000,
            B00000000,
            B10000000,
            B10000000,
            B10000000,
            B10000000,
            B10000000}
          ,
        {
            B00000000,
            B10000000,
            B10000000,
            B11000000,
            B01000000,
            B11000000,
            B01000000,
            B01000000}
          ,
        {
            B10000000,
            B01000000,
            B11000000,
            B11100000,
            B10100000,
            B11100000,
            B10100000,
            B10100000}
          ,
        {
            B00100000,
            B00100000,
            B11100000,
            B11110000,
            B11010000,
            B11110000,
            B01010000,
            B01010000}
          ,
        {
            B00100000,
            B10010000,
            B11110000,
            B11111000,
            B01101000,
            B11111000,
            B10101000,
            B10101000}
          ,
        {
            B01001000,
            B01001000,
            B01111000,
            B11111100,
            B10110100,
            B11111100,
            B01010100,
            B01010100}
          ,
        {
            B01001000,
            B00100100,
            B00111100,
            B01111110,
            B01011010,
            B01111110,
            B00101010,
            B00101010}
    };

//input blue
static const uint8_t PROGMEM 
    soso[][MATRIX_SIZE] =
    {
        {
            B00111100,
            B01111110,
            B11111111,
            B11011011,
            B11111111,
            B11000011,
            B01111110,
            B00111100
         } ,
        {
            B00111100,
            B01111110,
            B11111111,
            B10110111,
            B11111111,
            B10000111,
            B01111110,
            B00111100
         } ,
        {
            B00111100,
            B01111110,
            B11111111,
            B11011011,
            B11111111,
            B11000011,
            B01111110,
            B00111100
         } ,
        {
            B00111100,
            B01111110,
            B11111111,
            B11101101,
            B11111111,
            B11100001,
            B01111110,
            B00111100
         } ,
    };
     

void loop() {

    delay(100);
    TCS();
    
    value = max(countR,max(countG,countB));
    
    if(value<6) {
        state = NONE;
    } else if(value==countR) {  //red
        state = RED;
    } else if(value==countG) {  //green
        state = GREEN;
    } else {                    //blue
        state = BLUE;
    }
    
    if(prevState==state) {
        count++;
    } else {
        count=0;
    }
    //initialize matrix
    matrix.clear();

    if(state==RED&&count>-1) {
        Serial.print("this is in the heart state ");
        Serial.println(state);
        matrix.drawBitmap(0, 0, heart[count%(sizeof(heart)/MATRIX_SIZE)], MATRIX_SIZE, MATRIX_SIZE, LED_ON);
        delay(100); 
    }

    else if(state==GREEN&&count>-1) {
        Serial.print("this is in the monster state ");
        Serial.println(state);
        matrix.drawBitmap(0, 0, monster[count%(sizeof(monster)/MATRIX_SIZE)], MATRIX_SIZE, MATRIX_SIZE, LED_ON);
        delay(100);
    }

    else if(state==BLUE&&count>-1) {
        Serial.print("this is in the soso state ");
        Serial.println(state);
        matrix.drawBitmap(0, 0, soso[count%(sizeof(soso)/MATRIX_SIZE)], MATRIX_SIZE, MATRIX_SIZE, LED_ON);
        delay(100);
    }

    else { 
        Serial.print("this is in the NONE state ");
        Serial.println(state);
        matrix.setTextSize(1);
        matrix.setTextWrap(false); //we dont want text to wrap so it scrolls nicely
        matrix.setTextColor(LED_ON);
        matrix.print("Hungry");
        matrix.setCursor(-(count%37),0);
        delay(100);
    }
    prevState=state; 
    
    //draw
    matrix.writeDisplay();

    matrix.setRotation(0);
}
