// main.c with demo
// Updated and refactored Larry Kiser copyright 2021


// include project specific header files
#include <led.h>
#include "SysClock.h"
#include "UART.h"
#include "printf.h"
#include "stdio.h"

uint8_t buffer[100];

int main(void){
	int		some_int;
	float 	some_float = 1.0;
	int		n ;

	// initialization code
	System_Clock_Init(); // set System Clock = 80 MHz
	UART2_Init();
	led_init();

	while (1){
			// create some values to print
			some_float *= -1.618;
			some_int = some_float;
			char *msg = "";

			// toggle User LED based on user input
			char rxByte = USART_Read(USART2);
			// 'L' turns LED on
			if (rxByte == 'L') {
				led_set(1);
				msg = "ON";
			}
			// 'l' turns it off
			else if(rxByte == 'l') {
				led_set(0);
				msg = "off";
			}

			// print out some values
			n = sprintf((char *)buffer, "some_int=%d\t some_float=%5.3f \t%s\r\n", some_int, some_float, msg);
			USART_Write(USART2, buffer, n);
		}
}

