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