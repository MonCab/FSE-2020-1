import serial
import time
import sys
import Adafruit_DHT
import sys

# Configuracion del tipo de sensor DHT
sensor = Adafruit_DHT.DHT11

# Configuracion del puerto GPIO al cual esta conectado  (GPIO 23)
pin = 23

# Configuracion de la conexion UART con el modulo de Sigfox 
port = serial.Serial("/dev/ttyAMA0", baudrate=9600, timeout=3.0)

# Intenta ejecutar las siguientes instrucciones, si falla va a la instruccion except
try:	
	print(">> Limpieza del canal")
	#Ciclo infito para limpiar el canal
	#while True:
		# Se envia comando para limpiar el canal de comunicacion
	port.write("AT\n")
		# Obtenemos la respuesta
	rcv1 = port.readline(20)
		# Imprimimos la respuesta
	print(rcv1)
		# Esperamos a que la respuesta sea un OK
	#	if "OK" in rcv1 or "K" in rcv1:
			# Imprimimos la respuesta
	#		print(rcv1)
	#		print(">> Canal limpio")
			# Rompemos el ciclo
	#		break	
	
	# Se ejecuta en caso de que falle alguna instruccion dentro del try
except Exception,e:
	# Imprime en pantalla el error e
	print str(e)
	port.close()

# Cerramos la comunicacion con el modulo de Sigfox
port.close()
print(">> Programa terminado")