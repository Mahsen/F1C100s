#ifndef UART_H
#define UART_H

#include "../Core/define.h"

#define  UART_CHANNEL_1                                  0 // /dev/tty1
#define  UART_CHANNEL_2                                  1 // /dev/tty2

void UART_Channel_Config(U8 Channel, U32 BaudRate, U32 WordLength, U32 Parity, U32 StopBits);
void UART_Channel_Send(U8 Channel, U8* Data, U16 Length);

#endif
