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
	UART_Init();

	Print((char*)"Application: Start");
	UART_Channel_Config(UART_CHANNEL_2, B115200, CS8, PARENB, CSTOPB);
	Print((char*)"Application: Uart2 Inited");

	std::thread Task_Blink(MAIN_Blink);
	Task_Blink.detach(); 

	while(true) {
		U16 Length = 0;
		U8* Data = UART_Channel_Receive(UART_CHANNEL_2, &Length);
		if (Data) {
			Data[Length] = 0;
			UART_Channel_Send(UART_CHANNEL_2, Data, Length);
			Print((char*)Data);
			UART_Channel_Clear(UART_CHANNEL_2);
		}
	}

	Print((char*)"Application: End");

	//return 0;
}
/************************************************** Tasks *************************************************************/
void MAIN_Blink(void) {
	while(true) {
		static bool led = false;
		char str[32];
		sprintf(str, "gpio write PE2 %d", led);
		system(str);
		led ^= true;
		usleep(100000);
	}
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/
