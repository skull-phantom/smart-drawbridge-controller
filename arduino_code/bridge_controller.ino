const int pinRichting2 = 9;

const int pinEindeloopBoven = 2;
const int pinEindeloopOnder = 3;

const int pinKnop = 4;

const int OVERRIDE = 5;

const int OVERRIDESTOP = 11;
const int OVERRIDEUP = 12;
const int OVERRIDEDOWN = 13;


// =========================
// MOTOR FUNCTIES
// =========================

void stopMotor() {
  digitalWrite(pinRichting1, LOW);
  digitalWrite(pinRichting2, LOW);
}

void omhoog() {
  digitalWrite(pinRichting1, HIGH);
  digitalWrite(pinRichting2, LOW);
}

void omlaag() {
  digitalWrite(pinRichting1, LOW);
  digitalWrite(pinRichting2, HIGH);
}


// =========================
// SETUP
// =========================

void setup() {

  pinMode(pinRichting1, OUTPUT);
  pinMode(pinRichting2, OUTPUT);

  pinMode(pinEindeloopBoven, INPUT_PULLUP);
  pinMode(pinEindeloopOnder, INPUT_PULLUP);

  pinMode(pinKnop, INPUT_PULLUP);

  pinMode(OVERRIDE, INPUT_PULLUP);

  pinMode(OVERRIDESTOP, INPUT_PULLUP);
  pinMode(OVERRIDEUP, INPUT_PULLUP);
  pinMode(OVERRIDEDOWN, INPUT_PULLUP);

  stopMotor();

  Serial.begin(9600);
}


// =========================
// LOOP
// =========================

void loop() {

  // =========================
  // OVERRIDE MODE
  // =========================

  if (digitalRead(OVERRIDE) == HIGH) {

    Serial.println("OVERRIDE MODE");

    while (digitalRead(OVERRIDE) == HIGH) {

      // STOP
      if (digitalRead(OVERRIDESTOP) == HIGH) {
        stopMotor();
      }

      // OMHOOG
      else if (
        digitalRead(OVERRIDEUP) == HIGH &&
        digitalRead(pinEindeloopBoven) == HIGH
      ) {
        omhoog();
      }

      // OMLAAG
      else if (
        digitalRead(OVERRIDEDOWN) == HIGH &&
        digitalRead(pinEindeloopOnder) == HIGH
      ) {
        omlaag();
      }

      // GEEN KNOP
      else {
        stopMotor();
      }

      delay(20);
    }

    stopMotor();
  }


  // =========================
  // AUTOMATISCH OMHOOG
  // =========================

  Serial.println("Brug gaat omhoog");

  while (digitalRead(pinEindeloopBoven) == HIGH) {

    // Override check
    if (digitalRead(OVERRIDE) == HIGH) {
      stopMotor();
      return;
    }

    omhoog();
  }

  stopMotor();

  Serial.println("Boven bereikt");


  // wachten op knop
  while (digitalRead(pinKnop) == LOW) {

    if (digitalRead(OVERRIDE) == HIGH) {
      return;
    }

    delay(50);
  }

  delay(300);


  // =========================
  // AUTOMATISCH OMLAAG
  // =========================

  Serial.println("Brug gaat omlaag");

  while (digitalRead(pinEindeloopOnder) == HIGH) {

    // Override check
    if (digitalRead(OVERRIDE) == HIGH) {
      stopMotor();
      return;
    }

    omlaag();
  }

  stopMotor();

  Serial.println("Onder bereikt");


  // wachten op knop
  while (digitalRead(pinKnop) == LOW) {

    if (digitalRead(OVERRIDE) == HIGH) {
      return;
    }

    delay(50);
  }

  delay(300);
}