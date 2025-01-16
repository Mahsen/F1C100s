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
#include "../Module/Print.hpp"
/************************************************** Defineds **********************************************************/
/*
    Nothing
*/
/************************************************** Names *************************************************************/
/*
    Nothing
*/
/************************************************** Variables *********************************************************/
volatile struct struct_Ring UART[UART_CHANNEL_MAX];
char* UART_Channel_tty[] = {(char*)"/dev/ttyS1", (char*)"/dev/ttyS2"};
void UART_Task(void);
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
void UART_Init(void) {
	std::thread Task(UART_Task);
	Task.detach(); 
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_Config(U8 Channel, U32 BaudRate, U32 WordLength, U32 Parity, U32 StopBits) {
	if(Channel < UART_CHANNEL_MAX) {
		UART_Channel_Clear(Channel);
		UART[Channel].File = open(UART_Channel_tty[Channel], O_RDWR | O_NOCTTY);
		if (UART[Channel].File == -1) {
			return;
		}
		struct termios options;
		tcgetattr(UART[Channel].File, &options);          // Get current UART attributes
		cfsetispeed(&options, BaudRate);             // Set input baud rate
		cfsetospeed(&options, BaudRate);             // Set output baud rate
		options.c_cflag &= ~Parity;                  // parity
		options.c_cflag &= ~StopBits;                // stop bit
		options.c_cflag &= ~CSIZE;                   // Clear size bits
		options.c_cflag |= WordLength;               // data bits
		options.c_cflag |= (CLOCAL | CREAD);         // Enable receiver, ignore modem lines
		// Set UART to raw mode
		options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); // Disable canonical mode and echo
		options.c_iflag &= ~(IXON | IXOFF | IXANY);         // Disable software flow control
		options.c_oflag &= ~OPOST;                          // Disable output processing
		tcsetattr(UART[Channel].File, TCSANOW, &options); // Apply the settings
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_DeConfig(U8 Channel) {
	if(Channel < UART_CHANNEL_MAX) {
		if(UART[Channel].File) {
			close(UART[Channel].File);
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_Clear(U8 Channel) {
    if(Channel < UART_CHANNEL_MAX) {      
		memset((void*)UART[Channel].Receive.Data, 0, UART_BUFFER_MAX);              
		UART[Channel].Receive.Length = 0;
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
U8* UART_Channel_Receive(U8 Channel, U16* Length) {
    if(Channel < UART_CHANNEL_MAX) {    
		if(UART[Channel].File) {                  
            if(UART[Channel].Receive.Length) {                
                do {
                    *Length = UART[Channel].Receive.Length;
                    usleep(10000);
                } while(*Length != UART[Channel].Receive.Length);
                return (U8*)UART[Channel].Receive.Data;
            }
        }
	}
	*Length = 0;
	return NULL;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_Send(U8 Channel, U8* Data, U16 Length) {    
    if(Channel < UART_CHANNEL_MAX) {    
		if(UART[Channel].File) {                            
            write(UART[Channel].File, Data, Length); 
		}
    }
}
/************************************************** Tasks *************************************************************/
void UART_Task(void) {
	char Buffer[UART_BUFFER_MAX];  
    int Length;
	while(true) {
		for(int Index=0; Index<UART_CHANNEL_MAX; Index++) {
			if(UART[Index].File) {
				Length = read(UART[Index].File, Buffer, (UART_BUFFER_MAX - 1));
				if(Length) {
					memcpy((void*)&UART[Index].Receive.Data[UART[Index].Receive.Length], Buffer, Length);
					UART[Index].Receive.Length += Length;
				}
			}
		}
		usleep(1000);
	}
}
/************************************************** Vectors ***********************************************************/
/*
    Nothing
*/
/**********************************************************************************************************************/





