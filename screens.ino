
//imported from iohandler.ino
void press();
void rotateEncoder();

//menu renderer
void renderMenu(int menu)
{
  switch (menu)
  {
    case 1:
      mainMenu();
    break;
    default:
      defaultScreen();
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
//main menu using millis()
void defaultScreen () {

  timeNow = millis();

  //inputs
  press();

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

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){
  }
}
// watering menu
void wateringScreen()
{
  //inputs reading
  press();

  int timeNow = millis();

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){

  }
}

// settings menu
void settingsScreen()
{ 
  //inputs reading
  press();

  int timeNow = millis();

  lcd.setCursor(0,0);
  lcd.print("<");
  lcd.setCursor(15, 0);
  lcd.print(">");

  lcd.setCursor(2,0);
  lcd.print("SETTING");
  lcd.setCursor(0,1);
  lcd.print("Info");

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){

  }
}
