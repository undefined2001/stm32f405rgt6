#ifndef UART_H_
#define UART_H_

#include "stm32f405xx.h"

typedef enum
{
    UART_ERROR = -1,
    UART_OK = 0
} UART_Error_t;

#define UART_MODE_TX (1U << 3)
#define UART_MODE_RX (1U << 2)
#define UART_MODE_TX_RX (UART_MODE_TX | UART_MODE_RX)

#define UART_BAUDRATE_1200 1200U
#define UART_BAUDRATE_2400 2400U
#define UART_BAUDRATE_4800 4800U
#define UART_BAUDRATE_9600 9600U
#define UART_BAUDRATE_19200 19200U
#define UART_BAUDRATE_38400 38400U
#define UART_BAUDRATE_57600 57600U
#define UART_BAUDRATE_115200 115200U
#define UART_BAUDRATE_230400 230400U
#define UART_BAUDRATE_460800 460800U
#define UART_BAUDRATE_921600 921600U
#define UART_BAUDRATE_1000000 1000000U

#define UART_PARITY_NONE (0U << 9)               // PCE = 0
#define UART_PARITY_EVEN (1U << 10)              // PCE = 1, PS = 0
#define UART_PARITY_ODD ((1U << 10) | (1U << 9)) // PCE = 1, PS = 1

#define UART_WORD_LEN_8BIT (0 << 12)
#define UART_WORT_LEN_9BIT (1 << 12)

#define UART_STOPBITS_1BIT (0 << 12)
#define UART_STOPBITS_0_5BIT (1 << 12)
#define UART_STOPBITS_2BIT (2 << 12)
#define UART_STOPBITS_1_5BIT (3 << 12)

typedef struct
{
    USART_TypeDef *pUSARTx;
    uint32_t BaudRate;
    uint32_t WordLen;
    uint32_t ParityConfig;
    uint32_t Direction;
    uint32_t StopBits;
} UART_Config_t;

UART_Error_t UART_Init(UART_Config_t *pConfig);
void UART_Transmit();
void UART_TransmitIT();
void UART_TransmitDMA();
void UART_Receive();
void UART_ReceiveIT();
void UART_ReceiveDMA();

#endif // UART_H_
