import BlynkLib
import serial
import time

# =========================
# SERIAL NAAR ARDUINO
# =========================

arduino = serial.Serial('/dev/serial0', 9600, timeout=1)

time.sleep(2)

# =========================
# BLYNK
# =========================

BLYNK_AUTH = 'JOUW_BLYNK_TOKEN'

blynk = BlynkLib.Blynk(BLYNK_AUTH)

# =========================
# SLIDER V6
# =========================

@blynk.on("V6")
def v6_handler(value):

    angle = int(value[0])

    # veiligheid
    if angle < 0:
        angle = 0

    if angle > 90:
        angle = 90

    # stuur enkel getal
    msg = f"ANGLE:{angle}\n"

    arduino.write(msg.encode())

    print("Verstuurd:", angle)

# =========================
# LOOP
# =========================

while True:
    blynk.run()
    time.sleep(0.01)
