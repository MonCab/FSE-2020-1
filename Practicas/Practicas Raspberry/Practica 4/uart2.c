#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>		//Used for UART
#include <fcntl.h>		//Used for UART
#include <termios.h>		//Used for UART



void main(){
	int uart0_filestream = -1;

	uart0_filestream = open("/dev/ttyS0", O_RDWR | O_NOCTTY | O_NDELAY);		//Open in non blocking read/write mode

	if (uart0_filestream == -1)
	{
		//ERROR - CAN'T OPEN SERIAL PORT
		printf("Error - Unable to open UART.  Ensure it is not in use by another application\n");
	}	

	struct termios options;
	tcgetattr(uart0_filestream, &options);
	options.c_cflag = B115200 | CS8 | CLOCAL | CREAD;		//<Set baud rate
	options.c_iflag = IGNPAR;
	options.c_oflag = 0;
	options.c_lflag = 0;
	tcflush(uart0_filestream, TCIFLUSH);
	tcsetattr(uart0_filestream, TCSANOW, &options);
	
	//----- CHECK FOR ANY RX BYTES -----
	// Read up to 255 characters from the port if they are there
	unsigned char rx_buffer[256]; 

	//----- TX BYTES -----
	unsigned char tx_buffer[256] = "";
	unsigned char *p_tx_buffer;

	int j = 0; //Contador del while
	int i = 0; //Contador del for
	int k = 0; //Contador para las condiciones
	int number = 0, bandera = 0;
	float volt = 0.0;
	char tipo [272] = "";
	unsigned char cadena [256] = "";
	
	while (j <= 50) { 
		usleep(500000);
		
		//Recibiendo bytes

		if (uart0_filestream != -1) {
			while(1){
				int rx_length = read(uart0_filestream, (void*)rx_buffer, 255);//Filestream, buffer to store in, number of bytes to read (max)
				if (rx_length < 0){
					//printf("An error occured (will occur if there are no bytes)\n");
				} else if (rx_length == 0){
					//printf("No data waiting\n");
				} else {
					//Bytes received
					rx_buffer[rx_length] = '\0';
					//printf("%i bytes read : %s from UART\n", rx_length, rx_buffer);
					break;
				}
			}
		}

		strcpy(cadena, rx_buffer);
		
		if(strcmp(cadena, " ") == 0)
			continue;
		
		char *token= strtok(cadena, ",");
		do{
			switch(k){
				case 0:
					strcpy(tipo, "Numero entero: ");
					number = atoi(token);
					if(number < 0 || number > 4095)
						token = "Error";
					break;
				case 1:
					strcpy(tipo, "Iniciales: ");
					break;
				case 2:
					strcpy(tipo, "Bandera: ");
					bandera = atoi(token);
					if(bandera != 0 && bandera != 1)
						token = "Error";
					break;
				case 3:
					strcpy(tipo, "Voltaje: ");
					volt = atof(token);
					if(bandera < 0.0 || bandera > 3.3)
						token = "Error";
					break;
				default:
					printf("Error - Switch\n");
					break;
			}
			
			strcat(tipo, token);
			strcat(tipo, "\n");
			printf( "%s\n", tipo );
			
		    	
			//Transmitiendo bytes	
			strcpy(tx_buffer, tipo);

			if (uart0_filestream != -1){
				int count = write(uart0_filestream, &tx_buffer[0], strlen(tx_buffer));		//(p_tx_buffer - &tx_buffer[0])Filestream, bytes to write, number of bytes to write
				if (count < 0){
					printf("UART TX error\n");
				}
			}

			token = "";
			strcpy(tipo, "");
			k++;
		} while( (token = strtok( NULL, "," )) != NULL );		

		j++;
		k = 0;

	}
	
	

	//----- CLOSE THE UART -----
	close(uart0_filestream);

	return;
}