/************************************************** Description *******************************************************/
/*
    File : main.cpp
    Programmer : Mohammad Lotfi
    Used : main
    Design Pattern : none
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2025/1/14
*/
/************************************************** Warnings **********************************************************/
/*
    Only for learning
*/
/************************************************** Wizards ***********************************************************/
/*
    Nothing
*/
/************************************************** Includes **********************************************************/
#include "Module/Print.hpp"
#include "Driver/uart.h"
#include <thread>
#include <unistd.h>
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
void MAIN_Blink(void);
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
/* The main function start of program in cpp language */
int main() {
	
	Print((char*)"Application: Start");
	UART_Channel_Config(UART_CHANNEL_2, 115200, UART_8b, UART_PAR_NO, UART_STP_1);
	Print((char*)"Application: uart 1 inited");
	UART_Channel_Send(UART_CHANNEL_2, (U8*)"Hello Mohammad\r\n", strlen("Hello Mohammad\r\n"));
	Print((char*)"Application: uart 1 Sent");	
	Print((char*)"Application: End");
	
	//std::thread Task_Blink(MAIN_Blink);
	//Task_Blink.detach(); 
	
	//while(true);
	return 0;
}
/************************************************** Tasks *************************************************************/
void MAIN_Blink(void) {
	while(true) {
		static bool led = false;
		char str[32];
		sprintf(str, "gpio write PE2 %d", led);
		system(str);
		led ^= true;
		usleep(300000);
	}
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
