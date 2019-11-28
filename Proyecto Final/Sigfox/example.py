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
	while True:
		# Se envia comando para limpiar el canal de comunicacion
		port.write("AT$RC\n")
		# Obtenemos la respuesta
		rcv1 = port.readline(20)
		# Esperamos a que la respuesta sea un OK
		if "OK" in rcv1 or "K" in rcv1:
			# Imprimimos la respuesta
			print(rcv1)
			print(">> Canal limpio")
			# Rompemos el ciclo
			break	
	
	print(">> Envio del mensaje")
	# Ciclo principal infinito
	while True:
		# Obtiene la humedad y la temperatura desde el sensor 
		humedad, temperatura = Adafruit_DHT.read_retry(sensor, pin)
		
		# Imprime en la consola las variables temperatura y humedad con un decimal
		print('Temperatura={0:0.1f}*  Humedad={1:0.1f}%'.format(temperatura, humedad))
			
		# Datos en formato hexadecimal, de un numero entero y de tipo cadena	
		temp = hex(int(temperatura))
		hum = hex(int(humedad))
		
		# Eliminamos el formato 0x de las cadenas
		temp = temp[2:]
		hum = hum[2:]		

		# Dato del ambiente a enviar
		data = temp + "3A" + hum
		print("\n>> Dato a enviar: " + data)
		# Mensaje a enviar
		msg = "AT$SF=" + data + "\n" 
		print(">> Mensaje a Sigfox: " + msg)
		
		# Enviamos la informacion resultante del sensor
		port.write(msg)
		# Leemos la respuesta
		rcv = port.readline(20)
		print(rcv)
		#Esperamos a que la respuesta sea un Ok
		if "OK" in rcv:
			# Imprimimos la respuesta
			#print(rcv)
			print(">> Informacion enviada")
			# Rompemos el ciclo
			break

# Se ejecuta en caso de que falle alguna instruccion dentro del try
except Exception,e:
	# Imprime en pantalla el error e
	print str(e)
	port.close()

# Cerramos la comunicacion con el modulo de Sigfox
port.close()
print(">> Programa terminado")