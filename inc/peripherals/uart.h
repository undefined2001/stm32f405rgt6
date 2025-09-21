#ifndef UART_H_
#define UART_H_

#include "stm32f405xx.h"
#include <stddef.h>
typedef enum
{
    UART_ERROR = -1,
    UART_OK = 0
} UART_Error_t;

/* UART Modes */
#define UART_MODE_TX (1U << 3)
#define UART_MODE_RX (1U << 2)
#define UART_MODE_TX_RX (UART_MODE_TX | UART_MODE_RX)

/* Baud Rates */
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

/* Parity Config */
#define UART_PARITY_NONE (0U << 9)               // PCE = 0
#define UART_PARITY_EVEN (1U << 10)              // PCE = 1, PS = 0
#define UART_PARITY_ODD ((1U << 10) | (1U << 9)) // PCE = 1, PS = 1

/* Word Length */
#define UART_WORD_LEN_8BIT (0U << 12)
#define UART_WORD_LEN_9BIT (1U << 12)

/* Stop Bits */
#define UART_STOPBITS_1BIT (0U << 12)
#define UART_STOPBITS_0_5BIT (1U << 12)
#define UART_STOPBITS_2BIT (2U << 12)
#define UART_STOPBITS_1_5BIT (3U << 12)

/* UART States */
#define UART_STATE_READY 0U
#define UART_STATE_BUSY_TX 1U
#define UART_STATE_BUSY_RX 2U

typedef struct
{
    USART_TypeDef *pUSARTx;
    uint32_t BaudRate;
    uint32_t WordLen;
    uint32_t ParityConfig;
    uint32_t Direction;
    uint32_t StopBits;
} UART_Init_t;

typedef struct
{
    UART_Init_t Init;
    DMA_Stream_TypeDef *pTxDMAStream;
    DMA_Stream_TypeDef *pRxDMAStream;
    uint32_t TxDMAChannel;
    uint32_t RxDMAChannel;
    uint32_t BusyState;

    /* runtime buffers */
    uint8_t *pTxBuffer;
    uint8_t *pRxBuffer;
    uint32_t TxSize;
    uint32_t RxSize;
} UART_Handle_t;

#define UART_HANDLE_STRUCT_DEFAULT(pUSART, baud) \
    (UART_Handle_t){                             \
        .Init = {                                \
            .pUSARTx = (pUSART),                 \
            .BaudRate = (baud),                  \
            .WordLen = UART_WORD_LEN_8BIT,       \
            .ParityConfig = UART_PARITY_NONE,    \
            .Direction = UART_MODE_TX_RX,        \
            .StopBits = UART_STOPBITS_1BIT},     \
        .pTxDMAStream = NULL,                    \
        .pRxDMAStream = NULL,                    \
        .TxDMAChannel = 0,                       \
        .RxDMAChannel = 0,                       \
        .BusyState = UART_STATE_READY,           \
        .pTxBuffer = NULL,                       \
        .pRxBuffer = NULL,                       \
        .TxSize = 0,                             \
        .RxSize = 0}

/* API Prototypes */
UART_Error_t UART_Init(UART_Handle_t *pHandle);
void UART_Transmit(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);
void UART_TransmitIT(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);
void UART_TransmitDMA(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);
void UART_Receive(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);
void UART_ReceiveIT(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);
void UART_ReceiveDMA(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

#endif // UART_H_
