/* Blink Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Can use project configuration menu (idf.py menuconfig) to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO
#define LED_ONE_GPIO GPIO_NUM_16
#define LED_TWO_GPIO GPIO_NUM_17
#define LED_THREE_GPIO GPIO_NUM_5
#define LED_FOUR_GPIO GPIO_NUM_18
#define SENSOR_GPIO GPIO_NUM_19
int variable, j = 0;
int leds[4] = {0,0,0,0};

void decToBinary(int n){ 
	// array to store binary number 
	//int leds[4]; 
  
	// counter for binary array 
	int i = 0; 
	while (n > 0) {  
	// storing remainder in binary array 
	leds[i] = n % 2; 
	n = n / 2; 
	i++; 
	}
	//return leds; 
} 

void app_main(void)
{
	/* Configure the IOMUX register for pad BLINK_GPIO (some pads are
	   muxed to GPIO on reset already, but some default to other
	   functions and need to be switched to GPIO. Consult the
	   Technical Reference for a list of pads and their default
	   functions.)
	*/
	gpio_pad_select_gpio(BLINK_GPIO);
	gpio_pad_select_gpio(LED_ONE_GPIO);
	gpio_pad_select_gpio(LED_TWO_GPIO);
	gpio_pad_select_gpio(LED_THREE_GPIO);
	gpio_pad_select_gpio(LED_FOUR_GPIO);
	gpio_pad_select_gpio(SENSOR_GPIO);
	/* Set the GPIO as a push/pull output */
	gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_ONE_GPIO, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_TWO_GPIO, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_THREE_GPIO, GPIO_MODE_OUTPUT);
	gpio_set_direction(LED_FOUR_GPIO, GPIO_MODE_OUTPUT);
	gpio_set_direction(SENSOR_GPIO, GPIO_MODE_INPUT);

	while(1){
	 
	  if(!(gpio_get_level(SENSOR_GPIO))){
	  gpio_set_level(LED_ONE_GPIO,leds[0]);
	  gpio_set_level(LED_TWO_GPIO,leds[1]);
	  gpio_set_level(LED_THREE_GPIO,leds[2]); 
	  gpio_set_level(LED_FOUR_GPIO,leds[3]);	
	  if (variable >= 10){
		 variable = 1;
		 for (j = 0; j < 4; ++j){
		 	leds[j] = 0;
		 }
	  }else{
	 	 variable += 1;
	  }	  
	  decToBinary(variable);
	  vTaskDelay(500 / portTICK_PERIOD_MS);
 
	  printf("\n\n %d-%d-%d-%d ", leds[0],leds[1],leds[2],leds[3]);
	  
	}
  }
}
