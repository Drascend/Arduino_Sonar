
```Python
import serial 
import numpy as np 
import matplotlib.pyplot as plt 
import time

#===============#
# Configuración #
#===============#

PORT = 'COM6'
BAUDRATE = 115200
MAX_DIST = 200

#==================#
# CONEXIÓN ARDUINO #
#==================#

ser = serial.Serial(PORT, BAUDRATE, timeout=0)
time.sleep(2)
 
#=====================#
# CONFIGURACIÓN RADAR #
#=====================#
plt.ion()
fig = plt.figure(figsize=(6,6))
ax = fig.add_subplot(111, polar=True)

ax.set_ylim(0, MAX_DIST)
ax.set_theta_zero_location("N")
ax.set_theta_direction(-1)

line_detect, = ax.plot([], [], color='lime', linewidth=3)
line_rest, = ax.plot([], [], color='red', linewidth=1)
sweep_line, = ax.plot([], [], color='cyan', linewidth=1, alpha=0.6)

#=================#
# BUCLE PRINCIPAL #
#=================#
try:
    while True:

        # Vaciar buffer y quedarnos solo con el dato más reciente
        while ser.in_waiting:
            line = ser.readline().decode().strip()

        if not line:
            continue

        try:
            ang, dist = line.split(",")
            ang = float(ang)
            dist = float(dist)

            ang_rad = np.deg2rad(ang)

            # Línea hasta objeto
            line_detect.set_data([ang_rad, ang_rad], [0, dist])

            # Línea desde objeto hasta borde
            line_rest.set_data([ang_rad, ang_rad], [dist, MAX_DIST])

            # Barrido completo
            sweep_line.set_data([ang_rad, ang_rad], [0, MAX_DIST])

            # Dibujo más rápido
            fig.canvas.draw_idle()
            fig.canvas.flush_events()

        except:
            pass
    
except KeyboardInterrupt:
    print("Cerrando Radar...")

finally:
    ser.close()
    plt.ioff()
    plt.show()
```