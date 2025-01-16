/************************************************** Description *******************************************************/
/*
    File : uart.c
    Programmer : Mohammad Lotfi
    Used : uart
    Design Pattern : none
    Types of memory : Heap & Stack
    Total Tread : Nothing
    Site : https://www.mahsen.ir
    Tel : +989124662703
    Email : info@mahsen.ir
    Last Update : 2025/1/16
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
#include "uart.h"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
int UART[2];
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
void UART_Channel_Config(U8 Channel, U32 BaudRate, U32 WordLength, U32 Parity, U32 StopBits) {
	switch(Channel) {
		case UART_CHANNEL_1: { 
			UART[Channel] = open("/dev/ttyS1", O_RDWR | O_NOCTTY);
			if (UART[Channel] == -1) {
				return;
			}
			struct termios options;
			tcgetattr(UART[Channel], &options);          // Get current UART attributes
			cfsetispeed(&options, BaudRate);             // Set input baud rate
			cfsetospeed(&options, BaudRate);             // Set output baud rate
			options.c_cflag &= ~Parity;                  // parity
			options.c_cflag &= ~StopBits;                // stop bit
			options.c_cflag &= ~CSIZE;                   // Clear size bits
			options.c_cflag |= WordLength;               // data bits
			options.c_cflag |= (CLOCAL | CREAD);         // Enable receiver, ignore modem lines
			tcsetattr(UART[Channel], TCSANOW, &options); // Apply the settings
			break;
		}
		case UART_CHANNEL_2: { 
			UART[Channel] = open("/dev/ttyS2", O_RDWR | O_NOCTTY);
			if (UART[Channel] == -1) {
				return;
			}
			struct termios options;
			tcgetattr(UART[Channel], &options);          // Get current UART attributes
			cfsetispeed(&options, BaudRate);             // Set input baud rate
			cfsetospeed(&options, BaudRate);             // Set output baud rate
			options.c_cflag &= ~Parity;                  // parity
			options.c_cflag &= ~StopBits;                // stop bit
			options.c_cflag &= ~CSIZE;                   // Clear size bits
			options.c_cflag |= WordLength;               // data bits
			options.c_cflag |= (CLOCAL | CREAD);         // Enable receiver, ignore modem lines
			tcsetattr(UART[Channel], TCSANOW, &options); // Apply the settings
			break;
		}
		default: {
			while(1); //Error
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_DeConfig(U8 Channel) {
	switch(Channel) {
		case UART_CHANNEL_1: { 
			close(UART[Channel]);
			break;
		}
		case UART_CHANNEL_2: { 
			close(UART[Channel]);
			break;
		}
		default: {
			while(1); //Error
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_Send(U8 Channel, U8* Data, U16 Length) {    
    switch(Channel) {
    	case UART_CHANNEL_1: {                            
            write(UART[Channel], Data, Length); 
            break;
        }
        case UART_CHANNEL_2: {                            
            write(UART[Channel], Data, Length); 
            break;
        }
        default: {
            while(1); //Error
        }
    }
}
/************************************************** Tasks *************************************************************/
/*
    Nothing
*/
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/





