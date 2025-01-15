#ifndef UART_H
#define UART_H

#include "../Core/register.h"

#define  UART_CHANNEL_2                                  2

enum UART0_PORT { UART0_PE, UART0_PF };
enum UART1_PORT { UART1_PA, UART1_PD };
enum UART2_PORT { UART2_PD, UART2_PE };
enum UART_PAR   { UART_PAR_NO, UART_PAR_ODD, UART_PAR_EVEN };
enum UART_STP   { UART_STP_1, UART_STP_1_5 };
enum UART_LEN   { UART_5b, UART_6b, UART_7b, UART_8b };

#define UART_BR(x) (u16)(6000000L / x)

struct UART_CFG {
  u32 port    : 2;
  u32 parity  : 2;
  u32 stop    : 2;
  u32 lenght  : 2;
  u32 bitrate : 16;
};

void UART_Channel_Config(U8 Channel, U32 BaudRate, U32 WordLength, U32 Parity, U32 StopBits);
void UART_Channel_Send(U8 Channel, U8* Data, U16 Length);
int UART_put (UART_T *UART, u8 c);
int UART_rx_check (UART_T *UART);
int UART_get (UART_T *UART);

#endif
