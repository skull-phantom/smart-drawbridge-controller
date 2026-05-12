// =========================================================
// SMART DRAWBRIDGE CONTROL SYSTEM - ARDUINO
// =========================================================
// Deze code bestuurt de fysieke brug (motor + veiligheid).
//
// Functies:
// - Motor aansturen via H-bridge
// - Eindeloop schakelaars (veiligheid)
// - Automatische cyclus (omhoog → wachten → omlaag)
// - Handmatige override mode
// =========================================================


// =========================
// PIN DEFINITIES
// =========================

// Motor driver pins (H-bridge)
const int pinRichting1 = 8;
const int pinRichting2 = 9;

// Eindeloop schakelaars (veiligheid)
const int pinEindeloopBoven = 2;
const int pinEindeloopOnder = 3;

// Start knop (automatische cyclus)
const int pinKnop = 4;

// Override systeem (handmatige bediening)
const int OVERRIDE = 5;
const int OVERRIDESTOP = 11;
const int OVERRIDEUP = 12;
const int OVERRIDEDOWN = 13;


// =========================
// MOTOR FUNCTIES
// =========================

// Motor stoppen (veilig toestand)
void stopMotor() {
  digitalWrite(pinRichting1, LOW);
  digitalWrite(pinRichting2, LOW);
}

// Brug omhoog bewegen
void omhoog() {
  digitalWrite(pinRichting1, HIGH);
  digitalWrite(pinRichting2, LOW);
}

// Brug omlaag bewegen
void omlaag() {
  digitalWrite(pinRichting1, LOW);
  digitalWrite(pinRichting2, HIGH);
}


// =========================
// SETUP
// =========================

void setup() {

  // Motor pins
  pinMode(pinRichting1, OUTPUT);
  pinMode(pinRichting2, OUTPUT);

  // Eindeloop schakelaars (INPUT_PULLUP = veilig standaard HIGH)
  pinMode(pinEindeloopBoven, INPUT_PULLUP);
  pinMode(pinEindeloopOnder, INPUT_PULLUP);

  // Start knop
  pinMode(pinKnop, INPUT_PULLUP);

  // Override systeem
  pinMode(OVERRIDE, INPUT_PULLUP);
  pinMode(OVERRIDESTOP, INPUT_PULLUP);
  pinMode(OVERRIDEUP, INPUT_PULLUP);
  pinMode(OVERRIDEDOWN, INPUT_PULLUP);

  // Zorg dat motor start in veilige toestand
  stopMotor();

  // Serial communicatie voor debugging
  Serial.begin(9600);
}


// =========================
// MAIN LOOP
// =========================

void loop() {

  // =====================================================
  // OVERRIDE MODE (HANDMATIGE BEDIENING)
  // =====================================================
  // Wanneer override actief is, wordt automatische logica
  // genegeerd en kan gebruiker manueel de brug sturen.
  // =====================================================

  if (digitalRead(OVERRIDE) == HIGH) {

    Serial.println("OVERRIDE MODE");

    while (digitalRead(OVERRIDE) == HIGH) {

      // STOP knop
      if (digitalRead(OVERRIDESTOP) == HIGH) {
        stopMotor();
      }

      // Brug omhoog (mits bovenlimiet niet bereikt)
      else if (
        digitalRead(OVERRIDEUP) == HIGH &&
        digitalRead(pinEindeloopBoven) == HIGH
      ) {
        omhoog();
      }

      // Brug omlaag (mits onderlimiet niet bereikt)
      else if (
        digitalRead(OVERRIDEDOWN) == HIGH &&
        digitalRead(pinEindeloopOnder) == HIGH
      ) {
        omlaag();
      }

      // Geen input → motor veilig stoppen
      else {
        stopMotor();
      }

      delay(20);
    }

    // extra veiligheid bij verlaten override
    stopMotor();
  }


  // =====================================================
  // AUTOMATISCHE CYCLUS
  // =====================================================

  Serial.println("Brug gaat omhoog");

  // Brug gaat omhoog tot bovenste eindeloop bereikt wordt
  while (digitalRead(pinEindeloopBoven) == HIGH) {

    // veiligheid: override kan altijd interrupten
    if (digitalRead(OVERRIDE) == HIGH) {
      stopMotor();
      return;
    }

    omhoog();
  }

  stopMotor();
  Serial.println("Boven bereikt");


  // =====================================================
  // WACHT OP START KNOP
  // =====================================================

  while (digitalRead(pinKnop) == LOW) {

    if (digitalRead(OVERRIDE) == HIGH) {
      return;
    }

    delay(50);
  }

  delay(300);


  // =====================================================
  // BRUG GAAT OMLAAG
  // =====================================================

  Serial.println("Brug gaat omlaag");

  // Brug daalt tot onderste eindeloop
  while (digitalRead(pinEindeloopOnder) == HIGH) {

    if (digitalRead(OVERRIDE) == HIGH) {
      stopMotor();
      return;
    }

    omlaag();
  }

  stopMotor();
  Serial.println("Onder bereikt");


  // =====================================================
  // WACHT OP VOLGENDE CYCLUS
  // =====================================================

  while (digitalRead(pinKnop) == LOW) {

    if (digitalRead(OVERRIDE) == HIGH) {
      return;
    }

    delay(50);
  }

  delay(300);
}
