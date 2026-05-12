// =========================================================
// ARDUINO SERIAL ANGLE RECEIVER
// =========================================================
// Dit programma ontvangt data van de Raspberry Pi via UART.
//
// Doel:
// - Ontvangen van "ANGLE:<waarde>" commando
// - Data parsen (tekst → getal)
// - Klaarzetten voor motorbesturing (toekomstig)
//
// Voorbeeld input:
// ANGLE:45
// =========================================================


// =========================
// INPUT BUFFER
// =========================
// Hierin wordt inkomende seriële data tijdelijk opgeslagen
String input = "";


// =========================
// SETUP
// =========================

void setup() {

  // Start seriële communicatie
  Serial.begin(9600);

  // Debug boodschap bij opstart
  Serial.println("Arduino klaar voor ANGLE test");
}


// =========================
// MAIN LOOP
// =========================

void loop() {

  // =====================================================
  // LEES SERIËLE DATA
  // =====================================================
  // Zolang er data beschikbaar is op de serial buffer,
  // worden de inkomende characters één voor één gelezen.
  // =====================================================

  while (Serial.available()) {

    char c = Serial.read();

    // -----------------------------------------------------
    // EINDE VAN BERICHT (NEWLINE \n)
    // -----------------------------------------------------
    // Een volledig commando is ontvangen
    // -----------------------------------------------------
    if (c == '\n') {

      // =========================
      // COMMANDO CHECK
      // =========================
      // Controleer of het bericht start met "ANGLE:"
      // =========================

      if (input.startsWith("ANGLE:")) {

        // Haal numerieke waarde uit string
        int angle = input.substring(6).toInt();

        // Debug output
        Serial.print("OK ontvangen ANGLE = ");
        Serial.println(angle);

        // =================================================
        // TOEKOMSTIGE MOTOR FUNCTIE
        // =================================================
        // Hier kan later de motor gestuurd worden:
        //
        // moveToAngle(angle);
        //
        // Bijvoorbeeld:
        // - servo besturing
        // - stepper motor
        // - H-bridge control
        // =================================================

      } 
      else {

        // Onbekend commando ontvangen
        Serial.print("Onbekend commando: ");
        Serial.println(input);
      }

      // reset buffer na elk volledig bericht
      input = "";
    }

    // -----------------------------------------------------
    // GEWOON CHARACTER TOEVOEGEN AAN BUFFER
    // -----------------------------------------------------
    else {
      input += c;
    }
  }
}
