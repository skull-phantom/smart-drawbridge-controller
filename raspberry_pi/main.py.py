# =========================================================
# SMART DRAWBRIDGE SYSTEM - RASPBERRY PI CONTROLLER
# =========================================================
# Dit script:
# - Leest gewichtssensor (load cell)
# - Stuurt data naar Blynk app
# - Controleert GPIO outputs (LEDs / signalen)
# - Communiceert met Arduino via serial
# - Maakt live grafiek van gewicht
# =========================================================


# =========================
# IMPORT LIBRARIES
# =========================
import BlynkLib                      # Blynk IoT communicatie
import time                          # timing / delays
from qwiicscale import QwiicScale    # load cell sensor library
import matplotlib.pyplot as plt      # live grafiek
import numpy as np                   # numerieke berekeningen
import RPi.GPIO as GPIO              # Raspberry Pi GPIO control
import serial                        # UART communicatie met Arduino


# =========================
# SERIAL COMMUNICATION (PI ↔ ARDUINO)
# =========================
# /dev/ttyS0 = UART port op Raspberry Pi
arduino = serial.Serial('/dev/ttyS0', 9600, timeout=1)
time.sleep(2)  # wachten tot Arduino klaar is


# =========================
# FUNCTION: SEND ANGLE TO ARDUINO
# =========================
# Stuurt een hoekwaarde naar Arduino via serial (UART)
def send_angle(angle):
    msg = f"ANGLE:{angle}\n"
    arduino.write(msg.encode())
    print("verstuurd:", msg)


# =========================
# LIVE GRAPH SETUP
# =========================
# Deze grafiek toont real-time gewicht data
x_data = []
y_data = []

plt.ion()  # interactive mode aan (live update)
fig, ax = plt.subplots()
line, = ax.plot(x_data, y_data)


# =========================
# GPIO SETUP
# =========================
# BCM mode = GPIO nummering van Raspberry Pi
GPIO.setmode(GPIO.BCM)

# Outputs (LEDs / signalen / controle lijnen)
GPIO.setup(22, GPIO.OUT)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(24, GPIO.OUT)
GPIO.setup(25, GPIO.OUT)
GPIO.setup(17, GPIO.OUT)

# Alle outputs starten LOW (veilig toestand)
GPIO.output(22, GPIO.LOW)
GPIO.output(27, GPIO.LOW)
GPIO.output(24, GPIO.LOW)
GPIO.output(25, GPIO.LOW)


# =========================
# BLYNK SETUP (MOBILE APP)
# =========================
BLYNK_AUTH = 'c_oXkg5giB1GPc4sCMYZY-fviXKKL39W'
blynk = BlynkLib.Blynk(BLYNK_AUTH)

start_time = time.time()


# =========================================================
# BLYNK BUTTON HANDLERS (VIRTUAL PINS)
# =========================================================

# V1 = pulse / trigger actie
@blynk.on('V1')
def V1_write_handler(value):
    print(f"V1 waarde: {value}")

    value = int(value[0])

    if value == 1:
        GPIO.output(22, GPIO.HIGH)
        time.sleep(2)
        GPIO.output(22, GPIO.LOW)


# V2 = motor of control signaal
@blynk.on('V2')
def V2_write_handler(value):
    print(f"V2 waarde: {value}")

    value = int(value[0])
    GPIO.output(27, GPIO.HIGH if value == 1 else GPIO.LOW)


# V4 = extra control output
@blynk.on('V4')
def V4_write_handler(value):
    print(f"V4 waarde: {value}")

    value = int(value[0])
    GPIO.output(24, GPIO.HIGH if value == 1 else GPIO.LOW)


# V5 = extra output (bv. override / mode)
@blynk.on('V5')
def V5_write_handler(value):
    print(f"V5 waarde: {value}")

    value = int(value[0])
    GPIO.output(25, GPIO.HIGH if value == 1 else GPIO.LOW)


# V6 = slider (later gebruikt voor angle control)
@blynk.on('V6')
def V6_write_handler(value):
    print(f"Slider V6: {value}")
    value = int(value[0])


# =========================
# LOAD CELL HELPER FUNCTION
# =========================
# Neemt meerdere metingen en maakt gemiddelde
# → zorgt voor stabielere waarden
def get_average(scale, samples=5):
    total = 0

    for _ in range(samples):
        while not scale.available():
            pass
        total += scale.get_reading()
        time.sleep(0.05)

    return total / samples


# =========================
# MAIN PROGRAM START
# =========================
if scale.begin():

    print("Scale connected")

    # -------------------------
    # CALIBRATION (TARE)
    # -------------------------
    rawD = get_average(scale)

    print("Taring... verwijder gewicht")
    time.sleep(1)

    raw0 = get_average(scale)
    print("Zero reference:", raw0)

    print("Plaats gekend gewicht")
    time.sleep(1)

    raw_k = get_average(scale)
    print("Known weight raw:", raw_k)

    known_weight = 1010  # referentie gewicht (kalibratie)

    last_weight = 0


    # =========================
    # MAIN LOOP
    # =========================
    while True:

        # -------------------------
        # RAW SENSOR DATA
        # -------------------------
        raw = get_average(scale)

        kal = raw - raw0
        dif = raw_k - raw0

        # conversiefactor naar echte gewichtseenheid
        a_factor = known_weight / dif


        # -------------------------
        # NOISE FILTERING
        # -------------------------
        if abs(kal) <= 150:
            kal = 0
            last_weight = kal
        else:
            if abs(last_weight - kal) <= 150:
                kal = last_weight
            else:
                last_weight = kal


        sensor_value = kal * a_factor
        current_time = time.time() - start_time


        # -------------------------
        # SAFETY LED
        # -------------------------
        # LED aan als gewicht te hoog is
        if sensor_value > 1500:
            GPIO.output(17, GPIO.HIGH)
        else:
            GPIO.output(17, GPIO.LOW)


        # -------------------------
        # LIVE GRAPH UPDATE
        # -------------------------
        x_data.append(current_time)
        y_data.append(sensor_value)

        line.set_xdata(x_data)
        line.set_ydata(y_data)

        ax.relim()
        ax.autoscale_view()


        # -------------------------
        # BLYNK UPDATE
        # -------------------------
        blynk.run()
        blynk.virtual_write(0, sensor_value)


        time.sleep(0.01)

else:
    print("Scale not detected")
