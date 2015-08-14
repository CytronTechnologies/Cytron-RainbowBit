//Example sketch for Home Plate with RainbowBit LED
//Compiled with Arduino 1.6.4 IDE
//Please include the Adafruit_NeoPixel library
//Using Cuteduiono, 77 pcs of RainbowBit and Infrared sensor

#include <Adafruit_NeoPixel.h> //library developed by Adafruit.

#define PIN 0          //pin 0 is connected to RainbowBit's Input pin.
#define ADC  A1        //ADC input from Ultrasonic EZ1 distance sensor
#define BitNumber  77  //number of RainbowBit
#define LED 1          //pin 1 is connected to LED on Cuteduino
int RainbotBitNum = 1;
int distance = 1;
long ADCacc = 0;       //ADC value accumulator
byte current_color = 0;
int light=0;

// Parameter 1 = number of RainbowBit in strip
// Parameter 2 = pin number connected to RainbowBit's input (most are valid)
// Parameter 3 = pixel type flags, add together as needed:

#define color 30
Adafruit_NeoPixel strip = Adafruit_NeoPixel(BitNumber, PIN, NEO_GRB + NEO_KHZ800);

//preset the color value
uint32_t purple = strip.Color(color, 0, color);
uint32_t red = strip.Color(color, 0, 0);
uint32_t green = strip.Color(0, color, 0);
uint32_t yellow = strip.Color(color, color, 0);
uint32_t blue = strip.Color(0, 0, color);
uint32_t cyan = strip.Color(0, color, color);
uint32_t white = strip.Color(color, color, color);
uint32_t blank = strip.Color(0, 0, 0);
uint32_t rainbowBit_color[7] = {red, green, blue, purple, yellow, cyan, white};

void setup() {
  
  pinMode(LED,OUTPUT);
  pinMode(ADC, INPUT);  
  strip.begin();  
  delay(100); 
  strip.show();             // Initialize all RainbowBits to 'off'  
  delay(10);
  digitalWrite(LED,HIGH);  
}

void loop() {   
   
  while(1)
  {
//    ADCacc = 0;  //clearing the previous data
//    for(int i = 0; i < 33; i ++)
//    {
//      ADCacc = ADCacc + analogRead(ADC); //accumulate 50 samples
//    }
//    ADCacc = ADCacc / 33; //get the average
    //float infraredVoltage = ADCacc * 0.0048828;  //convert to voltage
    
    ADCacc = analogRead(ADC);
    /*linearation for GP2Y0A21*/    
    ADCacc = constrain (ADCacc, 82, 573);  //make the voltage valid for linearization
    distance = (6787/(ADCacc -3)) - 4 ;  //obtain the distance in cm detected by infrared sensor 
    //distance = map (distance, 8 , 82, 32, 3);
    
     //Serial.println(distance);     
    

        if(distance<=80 && distance>20){
          light=map(distance,20,80,77,0);
          for(uint16_t i=0; i<strip.numPixels(); i++) {
            if( i < light){
            strip.setBrightness(200); //set the brightness 
            strip.setPixelColor(i, rainbowBit_color[current_color]);
            strip.show();
           
            
            }
            
            else {strip.setPixelColor(i, blank);
              
            }strip.show();
          }
          
        }
        else if(distance <=20){
            uint16_t i, j;

            for(j=0; j<256*5; j++) {               // 5 cycles of all colors on wheel
            for(i=0; i< strip.numPixels(); i++){
            strip.setBrightness(20);               //set the brightness
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
            }
            strip.show();
            
            }
               current_color ++;  //change color   
      if(current_color >= 6) current_color = 0;
            } 
        else for(uint16_t i=0; i<strip.numPixels(); i++)strip.setPixelColor(i, blank);
        strip.show();
    
}
}
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}


