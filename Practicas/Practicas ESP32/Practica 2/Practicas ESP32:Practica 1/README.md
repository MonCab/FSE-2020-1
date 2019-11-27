FSE 2020-1 Práctica 1 ESP32 

Objetivo

El alumno conocerá el ambiente de desarrollo ESP-IDF para la programación del microcontrolador ESP32. Asimismo, aplicará los conceptos del manejo de entradas y salidas digitales de prop ́osito general.

Desarrollo 

1. Para el desarrollo de la práctica utilizamos varios GPIO
	-Uno para el sensor 
	-Cuatro para cuatro LEDs.
2. Leemos el valor del sensor Hall
3. Convertimos el entero en un número binario
4. Separamos el número vinario en un arreglo de 4  números (1 o 0)
5. A cada LED le asignamos el valor de una posición del arreglo 
6. Repetimos el proceso en un ciclo infinito
