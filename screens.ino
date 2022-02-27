
//imported from iohandler.ino
int press();
void rotateEncoder();

//menu renderer
void renderMenu()
{ 
  switch (selectedMenu)
  {
    case 0:
      maxSubmenu = 1;
      minSubmenu = 0;
      defaultScreen();

      break;
    
    case 1:
      maxSubmenu = 1;
      minSubmenu = 0;
      mainMenu();
      break;
    
    case 2:

      maxSubmenu = 1;
      minSubmenu = 0;
      if (selectedSubmenu == 0){
        wateringScreen();
      } 
      else if (selectedSubmenu == 1){
        settingsScreen();
      }
      break;

    case 3:
      break;
      
  }
}

//main menu for selecting settings or irrigation
void mainMenu () {
  
  

  //inputs
  int button = press(); 

  if(button == 1){
    selectedMenu ++;
    lcd.clear();
    return;
  }
  else if(button == 2)
  {
    selectedMenu --;
    lcd.clear();
    return;
  }

  timeNow = millis();

  DateTime now = rtc.now();//set current time to a variable
  lcd.setCursor(1,0);
  lcd.print("Watering");
  lcd.setCursor(1,1);
  lcd.print("Settings");

  //menu cursor
  if (selector == 0){
    selectedSubmenu = 0;
    lcd.setCursor(0,1);
    lcd.print(char(000));
    lcd.setCursor(0,0);
    lcd.print(">");
    
  }
  if (selector == 1){
    selectedSubmenu = 1;
    lcd.setCursor(0,0);
    lcd.print(char(000));
    lcd.setCursor(0,1);
    lcd.print(">");
  }

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){
    
  }
}

//main menu using millis()
void defaultScreen () {

  timeNow = millis();

  
  //inputs
  int button = press(); 

  if(button == 1){
    selectedMenu ++;
    lcd.clear();
    return;
  }

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
  
  int timeNow = millis();

  //inputs
  int button = press(); 

  if(button == 1){
    Serial.println(true);
  }
  else if(button == 2)
  {
    selectedMenu --;
    lcd.clear();
    return;
  }

  lcd.setCursor (0,0);
  lcd.print("settings");

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){

  }
}

// settings menu
void settingsScreen()
{ 
  
  int timeNow = millis();

  //inputs
  int button = press(); 

  if(button == 1){
    Serial.println(true);
  }
  else if(button == 2)
  {
    selectedMenu --;
    lcd.clear();
    return;
  }

  lcd.setCursor (0,0);
  lcd.print("settings");

  while(millis() < timeNow + DEFAULT_RESPONSE_TIME){

  }
}
