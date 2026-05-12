# =========================================================
# BLYNK → RASPBERRY PI → ARDUINO ANGLE CONTROL
# =========================================================
# Dit script stuurt een hoekwaarde van de Blynk app (slider)
# naar de Arduino via UART serial communicatie.
#
# Flow:
# Blynk Slider (V6)
#        ↓
# Raspberry Pi (Python)
#        ↓ UART (TX/RX)
# Arduino → motor control (brug hoek)
# =========================================================


# =========================
# IMPORT LIBRARIES
# =========================
import BlynkLib      # IoT communicatie met Blynk app
import serial        # UART communicatie met Arduino
import time          # timing / delays


# =========================
# SERIAL CONNECTION (PI ↔ ARDUINO)
# =========================
# /dev/serial0 = standaard UART poort op Raspberry Pi
arduino = serial.Serial('/dev/serial0', 9600, timeout=1)

# korte wachttijd zodat Arduino volledig opstart
time.sleep(2)


# =========================
# BLYNK SETUP
# =========================
# Authentication token van Blynk project
BLYNK_AUTH = 'JOUW_BLYNK_TOKEN'

blynk = BlynkLib.Blynk(BLYNK_AUTH)


# =========================================================
# SLIDER HANDLER (V6)
# =========================================================
# Deze functie wordt automatisch aangeroepen wanneer
# de slider in de Blynk app verandert.
#
# Input:
# value = lijst met string (bv. ['45'])
#
# Output:
# stuurt "ANGLE:45" naar Arduino
# =========================================================
@blynk.on("V6")
def v6_handler(value):

    # slider waarde omzetten naar integer
    angle = int(value[0])

    # -------------------------
    # SAFETY LIMITS
    # -------------------------
    # voorkomt foutieve of gevaarlijke waarden
    if angle < 0:
        angle = 0

    if angle > 90:
        angle = 90

    # -------------------------
    # SERIAL MESSAGE FORMAT
    # -------------------------
    # Arduino verwacht: ANGLE:<waarde>
    msg = f"ANGLE:{angle}\n"

    # stuur data naar Arduino
    arduino.write(msg.encode())

    print("Verstuurd angle:", angle)


# =========================================================
# MAIN LOOP
# =========================================================
# Houdt verbinding met Blynk actief
# en luistert naar updates van de app
# =========================================================
while True:

    # verwerkt inkomende Blynk events
    blynk.run()

    # kleine delay om CPU gebruik te beperken
    time.sleep(0.01)
