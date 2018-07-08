
const byte echoPin = 6;
const byte trigPin = 7;
unsigned long time, prevMillis = 0;
int distance, sumDistance = 0, fDistance = 0;
float distanceInches, sumDistanceInches = 0, fDistanceInches = 0;
byte ledState = LOW, interval;


void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  //pinMode(echoPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  getDistance();
  blinkWithoutDelay(distance);
  delay(150); //delay for 150ms before next reading
}

void getDistance() {
  for (byte counter = 0; counter < 10; counter++) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(5);

    digitalWrite(trigPin, LOW);

    time = pulseIn(echoPin, HIGH); //returns microseconds

    distanceInches = (time / 74.746) / 2; //returns distance in inches
    distance = (time / 29) / 2; //returns distance in cm
    sumDistance += distance;
    sumDistanceInches += distanceInches;
  }
  fDistance = sumDistance / 10;
  sumDistance = 0;
  fDistanceInches = sumDistanceInches / 10;
  sumDistanceInches = 0;
  if (fDistance <= 70) {
    Serial.print(fDistance);
    Serial.print("cm/");
    Serial.print(distanceInches);
    Serial.println("\"");
  }
}

void blinkWithoutDelay(int distance) {
  unsigned long currentMillis = millis();
  if (distance <= 70 && distance >= 26) {
    ledState = HIGH; // turn on LED
  } else if (distance < 26) {
    if (distance <= 25 && distance >= 20) {
      interval = 500;
    } else if (distance <= 19 && distance >= 15) {
      interval = 250;
    } else if (distance <= 14 && distance >= 10) {
      interval = 125;
    } else if (distance <= 9 && distance >= 0) {
      interval = 25;
    }
    if (currentMillis - prevMillis >= interval) {
      prevMillis = currentMillis; // save the last time the LED blinked
      //turn the LED on/off
      if (ledState == LOW) {
        ledState = HIGH;
      } else {
        ledState = LOW;
      }
    }
  }
  else { // turn off LED if distance is greater than 70
    ledState = LOW;
  }
  digitalWrite(LED_BUILTIN, ledState); //set the LED state
}


