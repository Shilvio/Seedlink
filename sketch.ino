#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <RTClib.h>

//pin for rotary encoder
#define CLK 2
#define DT 3
#define SW 4 //rotary encoder switch


//LCD settings
LiquidCrystal_I2C lcd(0x27,16,2); //lcd settings

//NTC settings
const float BETA = 3950; // should match the Beta Coefficient of the thermistor for data conversion

//RTC settings
RTC_DS1307 rtc; // setting rtc to appropriatwe model


//Humidity sensor settings
dht DHT;
#define DHT22_PIN 5


//Costants
#define DEFAULT_RESPONSE_TIME 50
#define LONG_PRESS 1000
#define ZERO 0
#define MAX_MENU 2

//global variables
int8_t lastState = HIGH;
unsigned long timeNow = 0;
char week[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
unsigned long lastButtonPress = 0;
bool singlePress= false;
bool encoderPos;
int selectedMenu = 0;
int lastCLK = digitalRead(CLK);

//imported from screens.ino
void renderMenu();

//imported from iohandler.io
void rotateEncoder();

void setup() {

  //setup lcd
  lcd.init();
  lcd.backlight();

  //starting serial
  Serial.begin(9600);

  //setup rotary encoder
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(CLK), rotateEncoder, FALLING);
  encoderPos = digitalRead(DT);
  

  //starting rtc and checking if is new
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if(! rtc.isrunning()){
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  }

}

void loop() {
  Serial.print(selectedMenu);
  renderMenu();
}
