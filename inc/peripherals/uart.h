#ifndef UART_H_
#define UART_H_

#include "stm32f405xx.h"
#include <stddef.h>

/**
 * @file uart.h
 * @brief UART driver for STM32F4 series
 * @details This file contains all the data structures, macros, and API
 *          function declarations required to initialize and use the UART
 *          peripheral with optional DMA support.
 */

/**
 * @enum UART_Error_t
 * @brief Error codes for UART operations
 */
typedef enum
{
    UART_ERROR = -1, /**< General error */
    UART_OK = 0      /**< Operation successful */
} UART_Error_t;

/** @defgroup UART_Modes UART Modes
 * Macros to select UART direction
 * @{
 */
#define UART_MODE_TX       (1U << 3)           /**< Transmit only */
#define UART_MODE_RX       (1U << 2)           /**< Receive only */
#define UART_MODE_TX_RX    (UART_MODE_TX | UART_MODE_RX) /**< Transmit and Receive */
/** @} */

/** @defgroup UART_BaudRates UART Baud Rates
 * Supported UART baud rates
 * @{
 */
#define UART_BAUDRATE_1200     1200U
#define UART_BAUDRATE_2400     2400U
#define UART_BAUDRATE_4800     4800U
#define UART_BAUDRATE_9600     9600U
#define UART_BAUDRATE_19200    19200U
#define UART_BAUDRATE_38400    38400U
#define UART_BAUDRATE_57600    57600U
#define UART_BAUDRATE_115200   115200U
#define UART_BAUDRATE_230400   230400U
#define UART_BAUDRATE_460800   460800U
#define UART_BAUDRATE_921600   921600U
#define UART_BAUDRATE_1000000  1000000U
/** @} */

/** @defgroup UART_Parity UART Parity
 * Parity configuration macros
 * @{
 */
#define UART_PARITY_NONE (0U << 9)                /**< No parity (PCE = 0) */
#define UART_PARITY_EVEN (1U << 10)               /**< Even parity (PCE = 1, PS = 0) */
#define UART_PARITY_ODD  ((1U << 10) | (1U << 9)) /**< Odd parity (PCE = 1, PS = 1) */
/** @} */

/** @defgroup UART_WordLength UART Word Length
 * Number of data bits
 * @{
 */
#define UART_WORD_LEN_8BIT (0U << 12) /**< 8-bit data */
#define UART_WORD_LEN_9BIT (1U << 12) /**< 9-bit data */
/** @} */

/** @defgroup UART_StopBits UART Stop Bits
 * Stop bits configuration macros
 * @{
 */
#define UART_STOPBITS_1BIT    (0U << 12)
#define UART_STOPBITS_0_5BIT  (1U << 12)
#define UART_STOPBITS_2BIT    (2U << 12)
#define UART_STOPBITS_1_5BIT  (3U << 12)
/** @} */

/** @defgroup UART_States UART States
 * UART busy/ready states
 * @{
 */
#define UART_STATE_READY   0U /**< UART is ready */
#define UART_STATE_BUSY_TX 1U /**< UART is busy transmitting */
#define UART_STATE_BUSY_RX 2U /**< UART is busy receiving */
/** @} */

/**
 * @struct UART_Init_t
 * @brief Configuration structure for UART peripheral
 */
typedef struct
{
    USART_TypeDef *pUSARTx; /**< UART peripheral base address */
    uint32_t BaudRate;      /**< Communication speed */
    uint32_t WordLen;       /**< Number of data bits */
    uint32_t ParityConfig;  /**< Parity configuration */
    uint32_t Direction;     /**< UART mode: TX, RX, or TX_RX */
    uint32_t StopBits;      /**< Stop bits configuration */
} UART_Init_t;

/**
 * @struct UART_Handle_t
 * @brief UART handle structure including DMA and buffers
 */
typedef struct
{
    UART_Init_t Init;               /**< UART configuration */
    DMA_Stream_TypeDef *pTxDMAStream; /**< DMA stream for TX */
    DMA_Stream_TypeDef *pRxDMAStream; /**< DMA stream for RX */
    uint32_t TxDMAChannel;          /**< DMA channel for TX */
    uint32_t RxDMAChannel;          /**< DMA channel for RX */
    uint32_t BusyState;             /**< UART current state */

    /* Runtime buffers */
    uint8_t *pTxBuffer;             /**< Pointer to TX buffer */
    uint8_t *pRxBuffer;             /**< Pointer to RX buffer */
    uint32_t TxSize;                /**< TX buffer size */
    uint32_t RxSize;                /**< RX buffer size */
} UART_Handle_t;

/**
 * @brief Macro to initialize a default UART handle structure
 * @param pUSART Pointer to USART peripheral
 * @param baud Baud rate
 */
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

/**
 * @brief Initialize UART peripheral with given handle
 * @param pHandle Pointer to UART handle structure
 * @return UART_OK on success, UART_ERROR on failure
 */
UART_Error_t UART_Init(UART_Handle_t *pHandle);

/**
 * @brief Transmit data via UART (blocking)
 * @param pHandle Pointer to UART handle
 * @param pData Pointer to data buffer
 * @param Size Number of bytes to transmit
 */
void UART_Transmit(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

/**
 * @brief Transmit data via UART using interrupts
 */
void UART_TransmitIT(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

/**
 * @brief Transmit data via UART using DMA
 */
void UART_TransmitDMA(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

/**
 * @brief Receive data via UART (blocking)
 */
void UART_Receive(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

/**
 * @brief Receive data via UART using interrupts
 */
void UART_ReceiveIT(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

/**
 * @brief Receive data via UART using DMA
 */
void UART_ReceiveDMA(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size);

#endif // UART_H_
