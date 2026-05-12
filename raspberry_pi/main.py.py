import BlynkLib
import time
from qwiicscale import QwiicScale
import matplotlib.pyplot as plt
import numpy as np
scale = QwiicScale()
import RPi.GPIO as GPIO
import serial

arduino = serial.Serial('/dev/ttyS0',9600, timeout=1)
time.sleep(2)

def send_angle(angel):
    msg =f"ANGLE:{angle}\n"
    arduino.write(msg.encode())
    print("verstuurd:",msg)


x_data = []
y_data = []
plt.ion()
fig, ax = plt.subplots()
line , = ax.plot(x_data, y_data)

GPIO.setmode(GPIO.BCM)
GPIO.setup(22, GPIO.OUT)
GPIO.output(22,GPIO.LOW)
GPIO.setup(27, GPIO.OUT)
GPIO.output(27,GPIO.LOW)
GPIO.setup(24, GPIO.OUT)
GPIO.output(24,GPIO.LOW)
GPIO.setup(25, GPIO.OUT)
GPIO.output(25,GPIO.LOW)
GPIO.setup(27, GPIO.OUT)
GPIO.setup(17, GPIO.OUT)
GPIO.setup(22, GPIO.OUT)
GPIO.output(22, GPIO.LOW)

start_time = time.time()

BLYNK_AUTH = 'c_oXkg5giB1GPc4sCMYZY-fviXKKL39W'
blynk = BlynkLib.Blynk(BLYNK_AUTH)

@blynk.on('V1')
def V1_write_handler(value):
    print(f"De knop op V1 is nu waarde {value}");
    value = int(value[0])
    if value == 1:
        GPIO.output(22, GPIO.HIGH)
        time.sleep(2)
        GPIO.output(22, GPIO.LOW)
    

@blynk.on('V2')
def V2_write_handler(value):
    print(f"De knop op V2 is nu waarde {value}");
    value = int(value[0])
    if value == 1:
        GPIO.output(27, GPIO.HIGH)
    else:
        GPIO.output(27, GPIO.LOW)



@blynk.on('V4')
def V4_write_handler(value):
    print(f"De knop op V4 is nu waarde {value}");
    value = int(value[0])
    if value == 1:
        GPIO.output(24, GPIO.HIGH)
    else:
        GPIO.output(24, GPIO.LOW)
    
@blynk.on('V5')
def V5_write_handler(value):
    print(f"De knop op V5 is nu waarde {value}");
    value = int(value[0])
    if value == 1:
        GPIO.output(25, GPIO.HIGH)
    else:
        GPIO.output(25, GPIO.LOW)

@blynk.on('V6')
def V6_write_handler(value):
    print(f"slider op V6 heeft waarde {value}");
    value = int(value[0])


    
def get_average(scale, samples =5):
    total = 0
    for _ in range(samples):
        while not scale.available():
            pass
        total += scale.get_reading()
        time.sleep(0.05)
    return (total/samples)

if scale.begin():
    print("Scale conect")
    rawD = get_average(scale)
    print("taring... verwijder gewicht")
    time.sleep(1)
    raw0 = get_average(scale)
    print("row0: 0g:" , raw0)
    print("Plaats gewicht met gekende massa")
    time.sleep(1)
    raw_k = get_average(scale)
    print("row_k", raw0)
    know_weight = 1010
    
    last_weight = 0
    
    while True:
        raw = get_average(scale)
        kal = raw - raw0
        dif = raw_k - raw0
        a_factor = know_weight/dif
        
        if abs(kal) <= 150:
            kal = 0
            last_weight = kal
            print(kal*a_factor)
        else:
            if abs(last_weight-kal) <= 150:
                kal = last_weight
                print(kal*a_factor)
            else:
                print(kal*a_factor)
                last_weight = kal
                
        sensor_value = kal*a_factor
        current_time = time.time() - start_time
        
        if sensor_value > 1500:
            GPIO.output(17, GPIO.HIGH)
        else:
            GPIO.output(17, GPIO.LOW)
            
        x_data.append(current_time)
        y_data.append(sensor_value)
        
        line.set_xdata(x_data)
        line.set_ydata(y_data)
        
        ax.relim()
        ax.autoscale_view()
        
      
        
        blynk.run()
        blynk.virtual_write(0, sensor_value)
        time.sleep(0.01)
        
else:
    print("Scale not detected")