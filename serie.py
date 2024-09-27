import serial
import time
import threading

# Configurar el puerto serie y la velocidad
puerto_serial = '/dev/ttyUSB0'  
baudrate = 115200


try:
    ser = serial.Serial(puerto_serial, baudrate)
except serial.SerialException as e:
    print(f"Error al abrir el puerto serie: {e}")
    exit()

# Archivo para guardar las mediciones
archivo = "distancias.csv"

# Variable para controlar el estado de la escritura
escribiendo = True

def leer_serial():
    global escribiendo
    with open(archivo, 'w') as f:
        print("Comenzando a leer datos del puerto serie... (presiona Enter para detener)")
        while escribiendo:
            if ser.in_waiting > 0:  # Verifica si hay datos disponibles
                linea = ser.readline().decode('utf-8').rstrip()  # Leer línea
                if linea:  # Solo escribe si la línea no está vacía
                    f.write(linea + "\n")  # Escribir en el archivo
                    f.flush()  # Asegurarse de que los datos se escriban inmediatamente
                    print(linea)  # Imprimir en la consola
                else:
                    print("Recibido: línea vacía.")
        print("Deteniendo la escritura en el archivo.")

def detener_escritura():
    global escribiendo
    input("Presiona Enter para detener la escritura...")
    escribiendo = False

# Iniciar el hilo para leer del puerto serie
hilo_lectura = threading.Thread(target=leer_serial)
hilo_lectura.start()

# Iniciar el hilo para detener la escritura
detener_escritura()

# Esperar a que el hilo de lectura termine
hilo_lectura.join()

# Cerrar el puerto serie
ser.close()
print("Puerto serie cerrado.")

