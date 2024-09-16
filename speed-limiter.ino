const int buttonPin = 14;
int myRelay = 27;
volatile byte relayState = LOW;
const unsigned long interval = 5000;
const unsigned long interval2 = 10000;

bool listening = true;

unsigned long previousMillis = 0;
unsigned long previousMillisLow = 0;
int buttonPressCount = 0;

void setup() {
  pinMode(buttonPin, INPUT_PULLDOWN);
  Serial.begin(115200);
  pinMode(myRelay, OUTPUT);
  pullRelayHIGH();
}

void loop() {
  checkStuff();

  if (digitalRead(buttonPin) == HIGH) {
    buttonPressCount++;
    delay(50);
    // Wait for button release
    while ((digitalRead(buttonPin) == HIGH)) {
      checkStuff();
    }
  } else {
  //  previousMillisLow = millis();
  }
}


void checkStuff() {
  unsigned long currentMillis = millis();
    if(digitalRead(buttonPin) == HIGH){
previousMillisLow = millis();
    }
  if (millis() - previousMillisLow >= interval2) {
    listening = true;

   // Serial.println(" listening = true;");
  }
  if ((currentMillis - previousMillis >= interval) && (listening == true)) {
    Serial.print("Button presses in the last 10 seconds: ");
    Serial.println(buttonPressCount);
    Serial.print("Relay state: ");
    Serial.println(relayState);
    if (buttonPressCount == 6) {
      pullRelayLOW();
      while (digitalRead(buttonPin) == HIGH) {
        Serial.print("turbogashik...");
        // Do nothing, just wait
      }
      Serial.println("quit...");
      Serial.println("quit...");
      pullRelayHIGH();
      buttonPressCount = 0;
      previousMillis = currentMillis;
      listening = false;
      previousMillisLow = millis();
    } else {
      pullRelayHIGH();
      buttonPressCount = 0;
      previousMillis = currentMillis;
    }

    
  }

}

void pullRelayHIGH() {
  if (relayState != HIGH) {
    digitalWrite(myRelay, HIGH);
    relayState = HIGH;
    Serial.println("RELAY ON");
  }
}

void pullRelayLOW() {
  if (relayState != LOW) {
    digitalWrite(myRelay, LOW);
    relayState = LOW;
    Serial.println("RELAY OFF");
  }
}
