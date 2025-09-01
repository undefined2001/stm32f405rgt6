#include "uart.h"
#include <stddef.h>

extern uint32_t SystemCoreClock;

UART_Error_t UART_Init(UART_Config_t *pConfig)
{
    if (pConfig == NULL)
        return UART_ERROR;

    if (pConfig->BaudRate < UART_BAUDRATE_1200 ||
        pConfig->BaudRate > UART_BAUDRATE_1000000)
    {
        return UART_ERROR;
    }

    USART_TypeDef *USARTx = pConfig->pUSARTx;

    uint32_t tReg = 0;

    // Disable UART before config

    // Configure word length + parity

    tReg |= pConfig->WordLen | pConfig->ParityConfig;

    // Configure TX/RX mode
    tReg |= pConfig->Direction;

    pConfig->pUSARTx->CR1 = tReg;

    // Configure stop bits
    USARTx->CR2 &= ~(3U << 12);
    USARTx->CR2 |= pConfig->StopBits;

    // Configure baud rate
    if ((USARTx->CR1 & USART_CR1_OVER8) == 0)
    {
        // oversampling by 16
        USARTx->BRR = (SystemCoreClock + (pConfig->BaudRate / 2U)) / pConfig->BaudRate;
    }
    else
    {
        // oversampling by 8
        uint32_t usartdiv = (2U * SystemCoreClock + (pConfig->BaudRate / 2U)) / pConfig->BaudRate;
        USARTx->BRR = (usartdiv & 0xFFF0U) | ((usartdiv & 0x000FU) >> 1U);
    }

    // Enable UART
    USARTx->CR1 |= USART_CR1_UE;

    return UART_OK;
}
