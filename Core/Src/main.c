
#include "UART.h"
#include "printf.h"
#include "stdio.h"
#include <ctype.h>
#include <clock.h>
#include <GPIO.h>
#include <string.h>

//declares the intial limits and buffer
uint8_t buffer[100];
int lower_limit = 50;
int upper_limit = 150;
//declares the variables that the capture times will be stored in
uint32_t last_capture = 0;
uint32_t pulse_duration = 0;
//a "bucket" struct that has a number and count associated with it
struct bucket {
  int bucket_num;
  int count;
};

int power_on_self_test(void){
	 uint32_t start_time = TIM2->CNT;
	 // 100 milliseconds in microseconds
	 uint32_t timeout = 100000;
	 int pulse_detected = 0;

	    // wait for a pulse or timeout
	 while ((TIM2->CNT - start_time) < timeout) {
	    if (TIM2->SR & TIM_SR_CC1IF) { // Check if the capture/compare interrupt flag is set
	    	pulse_detected = 1;
	        TIM2->SR &= ~TIM_SR_CC1IF; // Clear the interrupt flag
	        break; // Exit the loop if a pulse is detected
	    }
	 }
	 return pulse_detected;
}

//Initialize the buckets according to the limits the user set
struct bucket buckets[101];
void init_buckets(){
	for(int i = 0;i<=100;i++){
		buckets[i].bucket_num = i+lower_limit;
		buckets[i].count = 0;
	}
}

//This function gtes the numbers from the user USARt input. It also checks if they are digits
//and in the range
void get_limit(void *buff, int max_length){
	printf("\033[0;37m");
	int count = 0;
	char read_byte = 0;
	while(read_byte != '\r'){
		read_byte = USART_Read(USART2);

		if(read_byte!= '\r'){
			buffer[count] = read_byte;
			if(!isdigit(buffer[count])){
				printf("\033[0;31m");
				printf("\r\n%s\r\n","Please input only digits");
				get_limit(buffer,sizeof(buffer));
				break;
			}
			count++;
			printf("%c",read_byte);
		}
	}

	printf("\r\n");
    int result = 0;
    for (int i = 0;i<count; i++) {
        result = result * 10 + (buffer[i] - '0');
    }
    if(result >= 50 && result <= 9950){
    	lower_limit = result;
    }
    else{
    	printf("\033[0;31m");
    	printf("%s\r\n","Input should be between [50-9950]");
    	printf("\033[0;35m");
    	printf("%s","Enter new limit between [50-9950]: ");
    	get_limit(buffer,sizeof(buffer));
    }
}

int main(void){
    // Initialization executed once at startup

	Clock_Init();
    UART2_Init();
    GPIO_Init();
    int post_success = 0;
       do {
           printf("\033[0;35m\r\n%s","Performing Power On Self Test (POST)");
           if (power_on_self_test() == 1) {
               printf("\r\n%s","POST successful. Proceeding to the program");
               post_success = 1;
           } else {
               printf("\r\n%s","POST failed. No pulse detected within 100 milliseconds.");
               printf("\r\n%s","Press key to retry POST");
               printf("\033[0;37m");
               USART_Read(USART2);
           }
       } while (!post_success);
    // Main loop runs forever
    while(1)
    {
    	int pulse_count = 0;
    	//Prompt user for limits
    	strcpy(buffer,"");
    	printf("\033[0;35m");
    	printf("\r\n%s%d%s%d%s\r\n","The current limits are [", lower_limit,"-",upper_limit,"]");
    	printf("%s\r\n","Press 'Y' if you would like to adjust.");
    	printf("\033[0;37m");
    	char answer = USART_Read(USART2);
    	if(answer == 'Y' || 'y'){
    		printf("\033[0;35m");
    		printf("%s","Enter new limit between [50-9950]: ");
    		printf("\033[0;37m");
    		get_limit(buffer,sizeof(buffer));
    	}
    	upper_limit = lower_limit + 100;
    	printf("\033[0;35m");
    	printf("\r\n%s%d%s%d%s","Your program will run with limits of [",lower_limit,"-",upper_limit,"]");
    	printf("\r\n%s\r\n","Press any key to continue");
    	USART_Read(USART2);
    	init_buckets();
    	TIM2->CNT = 0;
    	while(pulse_count<1001){
    		if (TIM2->SR & TIM_SR_CC1IF){// Check if the capture/compare interrupt flag is set
    			uint32_t current_capture = TIM2->CCR1;

    			if (current_capture >= last_capture){
    				pulse_duration = (current_capture - last_capture) * 1.2 *  0.01;
    			    for(int i = 0;i<100;i++){
    			    	if(buckets[i].bucket_num == pulse_duration){
    			    		buckets[i].count++;
    			            break;
    			         }
    			    }
    			    pulse_count++;
    			    }else if(current_capture < last_capture) {
    			     // Overflow occurred
    			    	pulse_duration = (0XFFFFFFFF - last_capture) + current_capture + 1;
    			    }
    			    last_capture = current_capture;
    			    TIM2->SR &= ~TIM_SR_CC1IF;
    			    }
    	}

    	for(int i = 0;i<100;i++){
    			printf("\033[0;32m");
    			if(buckets[i].count != 0){
    			printf("\r\n%d%s%d\r\n",buckets[i].bucket_num," ",buckets[i].count);

    			}
    	}
    }
}

