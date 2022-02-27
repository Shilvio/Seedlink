//function that makes the button only pressed once
int press(){

  unsigned long startTime;
  int8_t state = digitalRead(SW);

  if(state != lastState){

    if(state == LOW) {
      lastButtonPress = millis(); //start a timer for detecting long presses
      singlePress = true;
    }
    //detects short press
    if( state == HIGH && millis() - lastButtonPress < LONG_PRESS ){

      lastState = state;
      return 1;
    }

  }

  //detects long press
  if( singlePress == true & state == LOW && millis() - lastButtonPress >= LONG_PRESS ){

    singlePress = false;
    lastState = state;
    return 2;
    
  }

  lastState = state;
  return 0;

}

//encoder rotation
void rotateEncoder()
{

  int dtValue = digitalRead(DT);
  if (dtValue == HIGH) {
    Serial.println(maxSubmenu);
    selector++;
    if(selector > maxSubmenu){
      selector = minSubmenu;
    }

  }
  if (dtValue == LOW) {
    selector--;
    if (selector < minSubmenu){
       selector = maxSubmenu;
    }

  }

}