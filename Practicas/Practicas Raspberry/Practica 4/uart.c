#include <stdio.h>
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

	//----- TX BYTES -----
	unsigned char tx_buffer[256] = "";
	unsigned char *p_tx_buffer;

	int j = 0; //Contador del while
	int i = 0; //COntador del for
	
	while (j <= 15) { 
		usleep(500000);
		
		if(sprintf( tx_buffer, "%i: FSE 2020-1 Comunicacion UART RPi - FSE\n", j) <= 0) {
			printf("Error - Unable to save the string");
		}

		//Transmitiendo bytes	
		p_tx_buffer = &tx_buffer[0];
		for(i = 0; i < strlen(tx_buffer); i++){
			//printf("Entrando al for\n");
			*p_tx_buffer++ = tx_buffer[i];
		}

		if (uart0_filestream != -1){
			int count = write(uart0_filestream, &tx_buffer[0], strlen(tx_buffer));		//(p_tx_buffer - &tx_buffer[0])Filestream, bytes to write, number of bytes to write
			if (count < 0){
				printf("UART TX error\n");
			}
			printf("%i: FSE 2020-1 Comunicacion UART RPi - FSE\n", j);
		}
		
		j++;

	}
	
	

	//----- CLOSE THE UART -----
	close(uart0_filestream);

	return;
}