enum LIGHTS_STATES {
  NS_GREEN_EW_RED,
  NS_YELLOW_EW_RED,
  NS_RED_EW_GREEN,
  NS_RED_EW_YELLOW,
  WALK
};

enum STATE_BEFORE_WALK {
  NS,
  EW
};

// NORTH SOUTH direction pins
#define RED_NS 13
#define GREEN_NS 12

// EAST WEST direction pins
#define RED_EW 9
#define GREEN_EW 8

// Pedestrian light pins
#define RED_WALK 5
#define YELLOW_WALK 4
#define GREEN_WALK 3

// Button pin and initialization
int button_pin = 2;
bool buttonPressed = false;
int previousButtonState = HIGH;
STATE_BEFORE_WALK stateBeforeWalk;

// Set initial state and starting time
unsigned long stateStartTime;
LIGHTS_STATES currentState = NS_GREEN_EW_RED;

void setup() {
  // initialize output pins
  pinMode(RED_NS, OUTPUT);
  pinMode(GREEN_NS, OUTPUT);

  pinMode(RED_EW, OUTPUT);
  pinMode(GREEN_EW, OUTPUT);

  pinMode(RED_WALK, OUTPUT);
  pinMode(YELLOW_WALK, OUTPUT);
  pinMode(GREEN_WALK, OUTPUT);

  // Initialize lights (green for NS, red for EW, red for WALK)
  digitalWrite(GREEN_NS, HIGH);
  digitalWrite(RED_NS, LOW);

  digitalWrite(GREEN_EW, LOW);
  digitalWrite(RED_EW, HIGH);

  digitalWrite(RED_WALK, HIGH);
  digitalWrite(YELLOW_WALK, LOW);
  digitalWrite(GREEN_WALK, LOW);

  // record initial time
  stateStartTime = millis();

  // initialize button
  pinMode(button_pin, INPUT_PULLUP);
}

void loop() {
  unsigned long currentTime = millis();
  unsigned long elapsed = currentTime - stateStartTime;
  int currentButtonState = digitalRead(button_pin);                 // Read button state

  if(previousButtonState == HIGH && currentButtonState == LOW) {   // Button has been pressed, pedestrian light is yellow
    buttonPressed = true;

    // Set stateBeforeWalk based on current state
    if (currentState == NS_YELLOW_EW_RED || currentState == NS_GREEN_EW_RED) {
      stateBeforeWalk = NS;
    } else if (currentState == NS_RED_EW_YELLOW || currentState == NS_RED_EW_GREEN) {
      stateBeforeWalk = EW;
    }

    digitalWrite(RED_WALK, LOW);
    digitalWrite(YELLOW_WALK, HIGH);
    digitalWrite(GREEN_WALK, LOW);
  }

  switch (currentState) {
    case NS_GREEN_EW_RED:
      if (elapsed >= 10000) {                 // NS has been green for 10s, we change NS to to yellow (EW stays red)
        digitalWrite(RED_NS, HIGH);
        digitalWrite(GREEN_NS, HIGH);
        currentState = NS_YELLOW_EW_RED;
        stateStartTime = currentTime;
      }
      break;

    case NS_YELLOW_EW_RED:
      if (elapsed >= 3000) {                  // NS has been yellow for 3s, we change NS to to red and EW to green
        if(buttonPressed){                    // If the pedestrian button was pressed, all lights go red except pedestrian light (green)
          digitalWrite(RED_NS, HIGH);
          digitalWrite(GREEN_NS, LOW);

          digitalWrite(RED_EW, HIGH);
          digitalWrite(GREEN_EW, LOW);


          digitalWrite(RED_WALK, LOW);
          digitalWrite(YELLOW_WALK, LOW);
          digitalWrite(GREEN_WALK, HIGH);
          currentState = WALK;
          delay(10000);
        }
        else {
          digitalWrite(RED_NS, HIGH);
          digitalWrite(GREEN_NS, LOW);

          digitalWrite(RED_EW, LOW);
          digitalWrite(GREEN_EW, HIGH);

          currentState = NS_RED_EW_GREEN;
          stateStartTime = currentTime;
        }
      }
      break;

    case NS_RED_EW_GREEN:
      if (elapsed >= 10000) {                 // EW has been green for 10s, we change EW to to yellow (NS stays red)
        digitalWrite(RED_EW, HIGH);
        digitalWrite(GREEN_EW, HIGH);
        currentState = NS_RED_EW_YELLOW;
        stateStartTime = currentTime;
      }
      break;

    case NS_RED_EW_YELLOW:
      if (elapsed >= 3000) {                  // EW has been yellow for 3s, we change EW to to red and NS to green
        if(buttonPressed){                    // If the pedestrian button was pressed, all lights go red except pedestrian light (green)
          digitalWrite(RED_NS, HIGH);
          digitalWrite(GREEN_NS, LOW);

          digitalWrite(RED_EW, HIGH);
          digitalWrite(GREEN_EW, LOW);


          digitalWrite(RED_WALK, LOW);
          digitalWrite(YELLOW_WALK, LOW);
          digitalWrite(GREEN_WALK, HIGH);
          currentState = WALK;
          delay(10000);
        }
        else {
          digitalWrite(RED_EW, HIGH);
          digitalWrite(GREEN_EW, LOW);

          digitalWrite(RED_NS, LOW);
          digitalWrite(GREEN_NS, HIGH);

          currentState = NS_GREEN_EW_RED;
          stateStartTime = currentTime;
        }     
      }
      break;  

    case WALK:
      if(stateBeforeWalk == EW){
        digitalWrite(RED_NS, LOW);
        digitalWrite(GREEN_NS, HIGH);
        currentState = NS_GREEN_EW_RED;
      }
      else if (stateBeforeWalk == NS){
        digitalWrite(RED_EW, LOW);
        digitalWrite(GREEN_EW, HIGH);
        currentState = NS_RED_EW_GREEN;
      }

      digitalWrite(RED_WALK, HIGH);
      digitalWrite(YELLOW_WALK, LOW);
      digitalWrite(GREEN_WALK, LOW);

      stateStartTime = currentTime;
      previousButtonState = HIGH;
      buttonPressed = false;
      break;
  }
}
