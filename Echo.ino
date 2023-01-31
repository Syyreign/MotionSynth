#include <NewPing.h>
#include <NewTone.h>

//Ultrasonic pins and max distance
const int trigPin = 3;
const int echoPin = 2;
const int maxDistance = 250;

//The ping class from the NewPing.h
NewPing sonar(trigPin, echoPin, maxDistance);

//How often the ping is sent in ms
unsigned int pingSpeed = 50;
unsigned long pingTimer;

//distance of the ping
unsigned long distance;
int smoothedDistance = 0;

//Used to check if a value has been updated
int oldSwitchDistance = -1;
int oldPin = -1;

void setup() {
  Serial.begin(9600);
  pingTimer = millis();

}

void loop() {
  //Pings every 50ms
  if (millis() >= pingTimer) {
    pingTimer += pingSpeed;
    sonar.ping_timer(distanceCheck);

  }  

  //Get analog input
  int yValue = analogRead(A5);
  //gets the ping to use on analog input
  int currentBuzzPin = getCurrentBuzzPin(yValue);
  
  //plays a tone on the give pin
  playTone(exponentialSmooth(distance, 0.2f), currentBuzzPin);
}

//Exponential smoothing function to prevent jittery ultrasonic values
int exponentialSmooth(int distance, float a){
  smoothedDistance = (a * distance) + ((1.0f - a) * (float)smoothedDistance);
  Serial.print("Smoothed Distance: ");
  Serial.println(smoothedDistance);
  return (int)smoothedDistance;
}

//Gets the ping distance in cm
void distanceCheck(){
  if (sonar.check_timer()) {
    distance = sonar.ping_result / US_ROUNDTRIP_CM;
    
  }
}

//Gets the current pin to use base on joystick value
int getCurrentBuzzPin(int value){
  value = max(0, value);
  if(value < 480 && value >= 300){
    return 11;
  }
  else if(value < 300 && value >= 20){
    return 12;
  }
  else if(value < 20){
    return 13;
  }
  
  return -1;
}

//Removes all currently playing tones
void clearTones(){
  noNewTone(11);
  noNewTone(12);
  noNewTone(13);
  // Serial.println("cleared");
}

//Used to get the switch value int from the ping distance
int getSwitchDistance(unsigned long dist){
  return dist / (unsigned long)10;
}

//Plays tones
void playTone(int distance, int pin){

  int switchDistance = getSwitchDistance(distance);

  //Only moves past this if any values have updated
  if(oldSwitchDistance == switchDistance && oldPin == pin){
    return;
  } 

  //If they have been updated, then set the new ones and clear the tone
  oldSwitchDistance = switchDistance;
  oldPin = pin;
  clearTones();
  
  //Switch to choose which tone to play based on a smoothed value
  switch(switchDistance)
  {
    case 1:
      NewTone(pin, 294);
      Serial.println("1");
      break;
    case 2:
      NewTone(pin, 330);
      Serial.println("2");
      break;
    case 3:
      NewTone(pin, 349);
      Serial.println("3");
      break;
    case 4:
      NewTone(pin, 392);
      Serial.println("4");
      break;
    case 5:
      NewTone(pin, 440);
      Serial.println("5");
      break;
    case 6:
      NewTone(pin, 494);
      Serial.println("6");
      break;
    case 7:
      NewTone(pin, 523);
      Serial.println("7");
      break;
    case 8:
      NewTone(pin, 587);
      Serial.println("8");
      break;
    case 9:
      NewTone(pin, 659);
      Serial.println("9");
      break;
    case 10:
      NewTone(pin, 698);
      Serial.println("10");
      break;
    case 11:
      NewTone(pin, 784);
      Serial.println("10");
      break;
    case 12:
      NewTone(pin, 880);
      Serial.println("10");
      break;
    case 13:
      NewTone(pin, 988);
      Serial.println("10");
      break;
    case 14:
      NewTone(pin, 1047);
      Serial.println("10");
      break;
    case 15:
      NewTone(pin, 1175);
      Serial.println("10");
      break;
    case 16:
      NewTone(pin, 1319);
      Serial.println("10");
      break;
    default:
      Serial.println("default");
      
  }
}
