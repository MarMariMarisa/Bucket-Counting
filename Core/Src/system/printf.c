/*
 * Created On: September 12, 2023
 * 	Author: Marisa
 *
 */

#include "printf.h"
#include "UART.H"
#include <stdio.h>
#include <string.h>

static char buffer[128];

static void print_string(const char* string,int len){
	USART_Write(USART2,(unsigned char*)string,len);
}

int puts(const char* string){
	int len = strlen(string);
	print_string(string,len);
	print_string("\n",1);
	return len;
}


int printf(const char* format,...){
	int num = sprintf(buffer,"%s",format);
	print_string(buffer,num);
	return num;
}
