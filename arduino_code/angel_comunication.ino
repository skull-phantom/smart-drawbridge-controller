// =========================================================
// SMART DRAWBRIDGE CONTROL SYSTEM - ARDUINO (GEUPGRADE)
// =========================================================
// + tijd-gebaseerde hoekregeling via SERIAL ANGLE
// + kalibratie van bewegingstijd
// =========================================================


// =========================
// PIN DEFINITIES
// =========================
const int pinRichting1 = 8;
const int pinRichting2 = 9;

const int pinEindeloopBoven = 2;
const int pinEindeloopOnder = 3;

const int pinKnop = 4;

const int OVERRIDE = 5;
const int OVERRIDESTOP = 11;
const int OVERRIDEUP = 12;
const int OVERRIDEDOWN = 13;


// =========================
// SERIELE ANGLE INPUT
// =========================
String input = "";
int targetAngle = 0;


// =========================
// TIMING VARIABELEN
// =========================
float msPerDegree = 0;          // wordt berekend via calibratie
int MAX_ANGLE = 90;             // pas aan aan je mechanica


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
// CALIBRATIE FUNCTIE
// =========================
// Meet tijd van volledig OMLAAG → VOLLEDIG OMHOOG
// =====================================================
void calibrateBridge() {

  Serial.println("CALIBRATIE START... brug omhoog meten");

  // start onderaan
  while (digitalRead(pinEindeloopOnder) == HIGH) {
    omlaag();
  }
  stopMotor();

  delay(500);

  unsigned long startTime = millis();

  // ga omhoog tot boven
  while (digitalRead(pinEindeloopBoven) == HIGH) {
    omhoog();
  }

  stopMotor();

  unsigned long endTime = millis();

  unsigned long totalTime = endTime - startTime;

  msPerDegree = (float)totalTime / MAX_ANGLE;

  Serial.print("CALIBRATIE KLAAR - ms/degree = ");
  Serial.println(msPerDegree);
}


// =========================
// GA NAAR HOEK
// =========================
void moveToAngle(int angle) {

  angle = constrain(angle, 0, MAX_ANGLE);

  Serial.print("Beweeg naar angle: ");
  Serial.println(angle);

  // bepaal huidige positie via grove inschatting:
  // (we gaan ervan uit dat we starten vanaf onder = 0°)
  unsigned long moveTime = angle * msPerDegree;

  unsigned long start = millis();

  while (millis() - start < moveTime) {

    // veiligheid
    if (digitalRead(OVERRIDE) == HIGH) {
      stopMotor();
      return;
    }

    omhoog();
  }

  stopMotor();
}


// =========================
// SERIAL LEZEN (ANGLE:xx)
// =========================
void readSerial() {

  while (Serial.available()) {

    char c = Serial.read();

    if (c == '\n') {

      if (input.startsWith("ANGLE:")) {

        targetAngle = input.substring(6).toInt();

        Serial.print("ANGLE ontvangen = ");
        Serial.println(targetAngle);

        moveToAngle(targetAngle);
      }
      else {
        Serial.print("Onbekend: ");
        Serial.println(input);
      }

      input = "";
    }
    else {
      input += c;
    }
  }
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

  Serial.begin(9600);

  stopMotor();

  delay(2000);

  calibrateBridge();
}


// =========================
// LOOP
// =========================
void loop() {

  // 1) altijd serial checken
  readSerial();

  // 2) OVERRIDE MODE blijft bestaan
  if (digitalRead(OVERRIDE) == HIGH) {

    Serial.println("OVERRIDE MODE");

    while (digitalRead(OVERRIDE) == HIGH) {

      if (digitalRead(OVERRIDESTOP) == HIGH) stopMotor();

      else if (digitalRead(OVERRIDEUP) == HIGH) omhoog();

      else if (digitalRead(OVERRIDEDOWN) == HIGH) omlaag();

      else stopMotor();

      delay(20);

      readSerial();
    }

    stopMotor();
  }

}
