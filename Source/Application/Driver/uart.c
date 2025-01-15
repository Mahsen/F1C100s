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
    Last Update : 2025/1/15
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
#include <stddef.h>
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
/*
    Nothing
*/
/************************************************** Opjects ***********************************************************/
/*
    Nothing
*/
/************************************************** Functions *********************************************************/
static int UART_idx (UART_T *UART) {
  if(UART == UART0) return 1 << 20;
  else if(UART == UART1) return 1 << 21;
  else if(UART == UART2) return 1 << 22;
  else return KO;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int UART_init (UART_T *UART, struct UART_CFG cfg) {
	int mask;
	if(UART == UART0) {
		/* PE0=UART0_RX, PE1=UART0_TX */
		if(cfg.port == UART0_PE) {
			u32 PE_CFG0_Value = REGISTER_Read((u32)&PE->CFG0);
			PE_CFG0_Value = (PE_CFG0_Value & 0xFFFFFF00) | 0x00000055;
			REGISTER_Write((u32)&PE->CFG0, PE_CFG0_Value);
		}
		/* PF2=UART0_RX, PF4=UART0_TX */
		else if(cfg.port == UART0_PF) {
			u32 PF_CFG0_Value = REGISTER_Read((u32)&PF->CFG0);
			PF_CFG0_Value = (PF_CFG0_Value & 0xFFF0F0FF) | 0x00030300;
			REGISTER_Write((u32)&PF->CFG0, PF_CFG0_Value);
		}
		else return KO;
	}
	else if(UART == UART1) {
		/* PA2=UART1_RX, PA3=UART1_TX */
		if(cfg.port == UART1_PA) {		
			u32 PA_CFG0_Value = REGISTER_Read((u32)&PA->CFG0);
			PA_CFG0_Value = (PA_CFG0_Value & 0xFFFF00FF) | 0x00005500;
			REGISTER_Write((u32)&PA->CFG0, PA_CFG0_Value);
		}
		/* PD3=UART1_RX, PD4=UART1_TX */
		else if(cfg.port == UART1_PD) {	
			u32 PD_CFG0_Value = REGISTER_Read((u32)&PD->CFG0);
			PD_CFG0_Value = (PD_CFG0_Value & 0xFFF00FFF) | 0x00033000;
			REGISTER_Write((u32)&PD->CFG0, PD_CFG0_Value);
		}
		else return KO;
	}
	else if(UART == UART2) {
		/* PD14=UART2_RX, PE13=UART2_TX */
		if(cfg.port == UART2_PD) {		
			u32 PD_CFG0_Value = REGISTER_Read((u32)&PD->CFG0);
			PD_CFG0_Value = (PD_CFG0_Value & 0xF00FFFFF) | 0x03300000;
			REGISTER_Write((u32)&PD->CFG0, PD_CFG0_Value);
		}
		/* PE8=UART2_RX, PE7=UART2_TX */
		else if(cfg.port == UART2_PE) { 
			u32 PE_CFG0_Value = REGISTER_Read((u32)&PE->CFG0);
			PE_CFG0_Value = (PE_CFG0_Value & 0x0FFFFFFF) | 0x30000000;
			REGISTER_Write((u32)&PE->CFG0, PE_CFG0_Value);
			
			u32 PE_CFG1_Value = REGISTER_Read((u32)&PE->CFG1);
			PE_CFG1_Value = (PE_CFG1_Value & 0xFFFFFFF0) | 0x00000003;
			REGISTER_Write((u32)&PE->CFG1, PE_CFG1_Value);
		}
		else return KO;
	}
	else return KO;
  
	mask = UART_idx(UART);
	u32 CCU_BUS_CLK_GATING2_Value = REGISTER_Read((u32)&CCU->BUS_CLK_GATING2);
	CCU_BUS_CLK_GATING2_Value |= mask;
	REGISTER_Write((u32)&CCU->BUS_CLK_GATING2, CCU_BUS_CLK_GATING2_Value);
	
	u32 CCU_BUS_SOFT_RST2_Value = REGISTER_Read((u32)&CCU->BUS_SOFT_RST2);
	CCU_BUS_SOFT_RST2_Value &= ~mask;
	CCU_BUS_SOFT_RST2_Value |= mask;
	REGISTER_Write((u32)&CCU->BUS_SOFT_RST2, CCU_BUS_SOFT_RST2_Value);
	
	REGISTER_Write((u32)&UART->THR, 0);
	REGISTER_Write((u32)&UART->FCR, 0xF7);
	REGISTER_Write((u32)&UART->MCR, 0);
	REGISTER_Write((u32)&UART->LCR, 0x80);
	REGISTER_Write((u32)&UART->DLL, cfg.bitrate);
	REGISTER_Write((u32)&UART->DLH, (cfg.bitrate >> 8));
	REGISTER_Write((u32)&UART->LCR, ((cfg.parity << 3) | (cfg.stop << 2) | cfg.lenght));
	
	return OK;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_Config(U8 Channel, U32 BaudRate, U32 WordLength, U32 Parity, U32 StopBits) {
	switch(Channel) {
		case UART_CHANNEL_2: {    
			struct UART_CFG cfg;
			cfg.port = UART2_PE;
			cfg.parity = Parity;
			cfg.stop = StopBits;
			cfg.lenght = WordLength;
			cfg.bitrate = UART_BR(BaudRate);
			UART_init (UART2, cfg);
			break;
		}
		default: {
			while(1); //Error
		}
	}
}
/*--------------------------------------------------------------------------------------------------------------------*/
int UART_put (UART_T *UART, u8 c) {
	while(!(REGISTER_Read((u32)&UART->LSR) & 64));
	REGISTER_Write((u32)&UART->THR, c);
	return OK;
}
/*--------------------------------------------------------------------------------------------------------------------*/
void UART_Channel_Send(U8 Channel, U8* Data, U16 Length) {    
    switch(Channel) {
        case UART_CHANNEL_2: {                             
            for(U16 Index=0; Index< Length; Index++) {
            	UART_put(UART2, Data[Index]);
            }
            break;
        }
        default: {
            while(1); //Error
        }
    }
}
/*--------------------------------------------------------------------------------------------------------------------*/
int UART_rx_check (UART_T *UART) {
  return REGISTER_Read((u32)&UART->LSR) & 1 ? OK : KO;
}
/*--------------------------------------------------------------------------------------------------------------------*/
int UART_get (UART_T *UART) {
  return UART_rx_check(UART) == KO ? KO : REGISTER_Read((u32)&UART->RBR);
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





