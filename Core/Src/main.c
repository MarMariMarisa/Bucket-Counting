
#include <led.h>
#include "UART.h"
#include "printf.h"
#include "stdio.h"
#include <ctype.h>
#include <clock.h>
#include <GPIO.h>
#include <string.h>

uint8_t buffer[100];
int lower_limit = 50;
int upper_limit = 150;
uint32_t last_capture = 0; // Stores the last captured counter value
uint32_t pulse_duration = 0; // Stores the calculated duration of the pulse
struct bucket {
  int bucket_num;
  int count;
};

int power_on_self_test(void){
	 uint32_t start_time = TIM2->CNT;
	 uint32_t timeout = 100000; // 100 milliseconds in microseconds
	 int pulse_detected = 0;

	    // Wait for a pulse or timeout
	 while ((TIM2->CNT - start_time) < timeout) {
	    if (TIM2->SR & TIM_SR_CC1IF) { // Check if the capture/compare interrupt flag is set
	    	pulse_detected = 1;
	        TIM2->SR &= ~TIM_SR_CC1IF; // Clear the interrupt flag
	        break; // Exit the loop if a pulse is detected
	    }
	 }
	 return pulse_detected;
}
struct bucket buckets[101];
void init_buckets(){
	for(int i = 0;i<=100;i++){
		buckets[i].bucket_num = i+lower_limit;
		buckets[i].count = 0;
	}
}


void get_limit(void *buff, int max_length){
	int count = 0;
	char rxByte = 0;
	while(rxByte != '\r'){
		rxByte = USART_Read(USART2);

		if(rxByte!= '\r'){
			buffer[count] = rxByte;
			if(!isdigit(buffer[count])){
				printf("\r\n%s\r\n","Please input only digits");
				get_limit(buffer,sizeof(buffer));
				break;
			}
			count++;
			printf("%c",rxByte);
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
    	printf("\r\n%s\r\n","Input should be between [50-9950]");

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
               printf("\r\n%s","Press 'R' to retry POST or any other key to proceed");
               printf("\033[0;37m");
               char choice = USART_Read(USART2);
               if (choice != 'R' && choice != 'r') {
                   post_success = 1; // Proceed even though POST failed
               }
           }
       } while (!post_success);
    // Main loop runs forever
    while(1)
    {
    	int pulse_count = 0;
    	uint32_t pulses[1001];
    	//Prompt user for limits
    	strcpy(buffer,"");
    	printf("\033[0;35m");
    	printf("\r\n%s%d\r\n","The current lower limit is ", lower_limit);
    	printf("%s\r\n","Press 'Y' if you would like to adjust.");
    	printf("\033[0;37m");
    	char answer = USART_Read(USART2);
    	if(answer == 'Y' || 'y'){
    		printf("\033[0;35m");
    		printf("%s\r\n","Enter new limit between [50-9950]");
    		printf("\033[0;37m");
    		get_limit(buffer,sizeof(buffer));
    	}
    	upper_limit = lower_limit + 100;
    	printf("\033[0;35m");
    	printf("\r\n%s%d%s%d%s","Your program will run with limits of [",lower_limit,"-",upper_limit,"]");
    	printf("\r\n%s\r\n","Press any key to continue");
    	char wait = USART_Read(USART2);
    	init_buckets();
    	while(pulse_count<1002){
    		if (TIM2->SR & TIM_SR_CC1IF) // Check if the capture/compare interrupt flag is set
    			    {
    			        uint32_t current_capture = TIM2->CNT;
    			        if (current_capture >= last_capture){
    			            pulse_duration = (current_capture - last_capture);
    			            pulses[pulse_count] = pulse_duration;
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

    	for(int i = 0;i<101;i++){
    		printf("\r\n%d",pulses[i]);
    		if(buckets[i].count > 0){
    		printf("\r\n%d%s%d\r\n",buckets[i].bucket_num," ",buckets[i].count);
    		}

    	}

    }

}

