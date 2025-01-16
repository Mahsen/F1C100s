#ifndef UART_H
#define UART_H
//----------------------------------------------------------
#include "../Core/define.h"
//----------------------------------------------------------
#define  UART_CHANNEL_1                                  0 // /dev/tty1
#define  UART_CHANNEL_2                                  1 // /dev/tty2
#define  UART_CHANNEL_MAX                                2
#define  UART_BUFFER_MAX                                 1024
//----------------------------------------------------------
struct struct_Ring {
  int File;
  struct struct_Receive {
    U8 Data[UART_BUFFER_MAX];
    U16 Length;
  } Receive;
};
//----------------------------------------------------------
void UART_Init(void);
void UART_Channel_Config(U8 Channel, U32 BaudRate, U32 WordLength, U32 Parity, U32 StopBits);
void UART_Channel_DeConfig(U8 Channel);
void UART_Channel_Clear(U8 Channel);
U8* UART_Channel_Receive(U8 Channel, U16* Length);
void UART_Channel_Send(U8 Channel, U8* Data, U16 Length);
//----------------------------------------------------------
#endif
