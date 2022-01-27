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