String input = "";

void setup() {
  Serial.begin(9600);
  Serial.println("Arduino klaar voor ANGLE test");
}

void loop() {

  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {

      if (input.startsWith("ANGLE:")) {
        int angle = input.substring(6).toInt();

        Serial.print("OK ontvangen ANGLE = ");
        Serial.println(angle);

        // hier zou later je motor komen
        // moveToAngle(angle);

      } else {
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