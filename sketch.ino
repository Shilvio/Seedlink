
#include <LiquidCrystal_I2C.h>
#include <dht.h>
#include <RTClib.h>

//MANOVELLA
#define ENCODER_CLK 2
#define ENCODER_DT  3
#define ENCODER_BTN 4

//COSTANTI GLOBALI
#define MAX_OPTION_LENGTH 14

//VARIABILI GLOBALI
bool cursorPos = 0;
int selected_menu = 0;
int selected_item = 0;

//LCD settings
LiquidCrystal_I2C lcd(0x27,16,2); //lcd settings

//NTC settings
const float BETA = 3950; // should match the Beta Coefficient of the thermistor for data conversion

//RTC settings
RTC_DS1307 rtc; // setting rtc to appropriatwe model
char week[7][4] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};

//Humidity sensor settings
dht DHT;
#define DHT22_PIN 5

//INTERRUPT

void rotatePin()
{
  int dtValue = digitalRead(ENCODER_DT);

  if (dtValue == HIGH && cursorPos == 0) {
    selected_menu++; // Clockwise
  }
  if (dtValue == LOW && cursorPos == 1) {
    selected_menu--; // Counterclockwise
  }
}

void btnPress()
{
  Serial.println("press()");
}

void setup() {

  //setting up lcd
  lcd.init();
  lcd.backlight();

  //starting serial
  Serial.begin(115200);

  //starting rtc and checking if is new
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if(! rtc.isrunning()){
    rtc.adjust(DateTime(F(__DATE__),F(__TIME__)));
  }

  pinMode(ENCODER_CLK, INPUT);
  pinMode(ENCODER_DT, INPUT);
  pinMode(ENCODER_BTN, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);

  attachInterrupt (digitalPinToInterrupt (ENCODER_CLK), rotatePin, CHANGE);
  attachInterrupt (digitalPinToInterrupt (ENCODER_BTN), btnPress, FALLING);

}

void loop() {

  renderMenu(selected_menu);

  //Premi il pulsante e guarda che succede
  if (digitalRead(ENCODER_BTN) == HIGH) {
    cursorPos = !cursorPos;
  }
}

// ---------------- SELETTORE SCHERMATE ----------------- //

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


// --------------- DEFINIZIONE SCHERMATE ----------------- //

//Schermata principale - mostra temperatura ed umidità
void defaultScreen () {

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

  delay(200);
}

//Menu - per selezionare altri schermi
void mainMenu () {
  
  char arr[][MAX_OPTION_LENGTH] =
  { "Watering",
    "Settings"
  };

  lcd.setCursor(0,cursorPos);
  lcd.print('>');

  int i = 0;

  lcd.setCursor(2,0);
  lcd.print(arr[i]);
  lcd.setCursor(2,1);
  lcd.print(arr[i+1]);
  
  //delay(200);
}
