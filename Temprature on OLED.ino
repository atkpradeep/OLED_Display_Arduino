/*********************************************************************
This is an example for Monochrome OLEDs based on SSD1306 drivers
Show the temperature on the OLED display using DHT11 sensor   

  
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h" //Include DHT library

#define DHTTYPE  DHT11   // we are using DHT 11 sensor

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

int arduionPin=2; //Arduino board input pin connect with DHT sensor signal pin
// Initialize DHT sensor.
// Note that older versions of this library took an optional third parameter to
// tweak the timings for faster processors.  This parameter is no longer needed
// as the current DHT reading algorithm adjusts itself to work on faster procs.
DHT dht(arduionPin, DHTTYPE);

#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
  dht.begin(); //Start DHT sensor to read temperature  
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  // init done
  
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
  delay(2000);
  
}


void loop() {
   // To get correct value of temperature, Wait for few seconds.
  delay(250);
  display.clearDisplay(); 
  // Read temperature as Celsius (the default) or (isFahrenheit = true)
  float temperature = dht.readTemperature();
 
  // Check if any reads failed and exit early (to try again).
  if (isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    //try to read again
    while(!isnan(temperature)){
        temperature = dht.readTemperature();
      }
  }
  // Clear the buffer.
  display.clearDisplay();

  // text setting for display 
  display.setTextSize(1); //Set
  display.setTextColor(WHITE);
  display.setCursor(0,0); //Start position 
  display.println("Temperature is:");
  println("");
  display.setTextSize(2); //font size
  display.println(temperature);
  display.display();
  delay(250);
  display.clearDisplay(); //Clear previous diaplay to refresh one

  //For debugging 
  Serial.print("Temperature is: "); //Print temperature reading from DHT sensor
  Serial.print(temperature);
  Serial.println("");
}


