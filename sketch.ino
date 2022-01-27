
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <RTClib.h>

//pin for rotary encoder
#define CLK 2
#define DT 4
#define SW 3 //rotary encoder switch

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

//global variables
int8_t lastState = HIGH;
unsigned long timeNow = 0;
char week[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
unsigned long lastButtonPress = 0;
bool singlePress= false;
bool encoderPos;

void setup() {

  //setup lcd
  lcd.init();
  lcd.backlight();

  //starting serial
  Serial.begin(115200);

  //setup rotary encoder
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
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

  defaultScreen ();

}

//function that makes the button only pressed once
void press(){

  unsigned long startTime;
  int8_t state = digitalRead(SW);
  
  if(state != lastState){

    if(state == LOW) {
      lastButtonPress = millis(); //start a timer for detecting long presses
      singlePress = true;
    }
    //detects short press
    if( state == HIGH && millis() - lastButtonPress < LONG_PRESS ){
      Serial.println("si abbassa il pipo");
    }
    
  }

  //detects long press
  if( singlePress == true & state == LOW && millis() - lastButtonPress >= LONG_PRESS ){
    Serial.println("si alza il pipo");
    singlePress = false;
    
  }

  lastState = state;

}
 
//main menu using millis()
void defaultScreen () {

  timeNow = millis();

  DateTime now = rtc.now();//set current time to a variable
  //print current day
  lcd.setCursor(0,0);
  lcd.print(week[now.dayOfTheWeek()]);

  //print current moisture
  char hum[3];
  DHT.read22(DHT22_PIN);
  lcd.setCursor(6,0);
  lcd.print("Moist ");
  sprintf(hum,int(DHT.humidity));
  lcd.print(int(DHT.humidity));
  lcd.print(char(045));
  lcd.print(char(000));

  //print current time
  lcd.setCursor(0,1);
  char hours[2];
  char minutes[2];
  sprintf(hours,"%02d",now.hour());
  lcd.print(hours);
  lcd.print(":");
  sprintf(minutes,"%02d",now.minute());
  lcd.print(minutes);

  //print current greenhouse temperature
  lcd.setCursor(9,1);
  lcd.print(char(223));
  lcd.print("C");
  int analogValue = analogRead(A0);
  float celsius = 1 / (log(1 / (1023. / analogValue - 1)) / BETA + 1.0 / 298.15) - 273.15;
  lcd.setCursor(12,1);
  lcd.print(celsius);
  press(); // detects button press

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){
    
  }
}

//main menu for selecting settings or irrigation
void mainMenu () {

  timeNow = millis();

  DateTime now = rtc.now();//set current time to a variable
  lcd.setCursor(1,0);
  lcd.print("Watering");
  lcd.setCursor(1,1);
  lcd.print("Settings");

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){
    
  }
}
//encoder rotation
void rotateEncoder()
{
  int dtValue = digitalRead(DT);

  if (dtValue == HIGH && encoderPos == 0) {
    Serial.print("Clockwise"); // Clockwise
  }
  if (dtValue == LOW && encoderPos == 1) {
    Serial.print("counter clockwise"); // Counterclockwise
  }

}

//menu renderer
void renderMenu(int menu)
{
  switch (menu)
  {
    case 1:
      Serial.println(menu);
      mainMenu();
    break;
    default:
      Serial.println(menu);
      defaultScreen();
  }
}


