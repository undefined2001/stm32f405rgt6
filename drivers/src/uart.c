#include "uart.h"
#include <stddef.h>

extern uint32_t SystemCoreClock;

#include "uart.h"
#include <stddef.h>

#include "uart.h"
#include <stddef.h>

extern uint32_t SystemCoreClock;

UART_Error_t UART_Init(UART_Handle_t *pHandle)
{
    if (pHandle == NULL)
        return UART_ERROR;

    if (pHandle->Init.BaudRate < UART_BAUDRATE_1200 ||
        pHandle->Init.BaudRate > UART_BAUDRATE_1000000)
    {
        return UART_ERROR;
    }

    USART_TypeDef *USARTx = pHandle->Init.pUSARTx;

    // 1. Disable UART before config
    USARTx->CR1 &= ~USART_CR1_UE;

    // 2. Configure word length + parity + direction
    USARTx->CR1 &= ~(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS |
                     USART_CR1_TE | USART_CR1_RE);
    USARTx->CR1 |= (pHandle->Init.WordLen |
                    pHandle->Init.ParityConfig |
                    pHandle->Init.Direction);

    // 3. Configure stop bits
    USARTx->CR2 &= ~(USART_CR2_STOP);
    USARTx->CR2 |= pHandle->Init.StopBits;

    // 4. Configure baud rate using default 16 MHz clock
    uint32_t periphClk = 16000000UL; // assuming HSI = 16 MHz
    uint32_t usartdiv;

    if ((USARTx->CR1 & USART_CR1_OVER8) == 0)
    {
        // oversampling by 16
        usartdiv = (periphClk + (pHandle->Init.BaudRate / 2U)) /
                   pHandle->Init.BaudRate;
        USARTx->BRR = usartdiv;
    }
    else
    {
        // oversampling by 8
        usartdiv = (2U * periphClk + (pHandle->Init.BaudRate / 2U)) /
                   pHandle->Init.BaudRate;
        USARTx->BRR = (usartdiv & 0xFFF0U) | ((usartdiv & 0x000FU) >> 1U);
    }

    // 5. Enable UART
    USARTx->CR1 |= USART_CR1_UE;

    // 6. Initialize handle runtime state
    pHandle->BusyState = UART_STATE_READY;
    pHandle->pTxBuffer = NULL;
    pHandle->pRxBuffer = NULL;
    pHandle->TxSize = 0;
    pHandle->RxSize = 0;

    return UART_OK;
}

void UART_TransmitDMA(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size)
{
    if (pHandle->BusyState != UART_STATE_READY || Size == 0 || pHandle->pTxDMAStream == NULL)
        return;

    // 1. Mark UART as busy
    pHandle->BusyState = UART_STATE_BUSY_TX;
    pHandle->pTxBuffer = pData;
    pHandle->TxSize = Size;

    USART_TypeDef *USARTx = pHandle->Init.pUSARTx;
    DMA_Stream_TypeDef *DMAxStream = pHandle->pTxDMAStream;

    // 2. Enable UART DMA TX mode
    USARTx->CR3 |= USART_CR3_DMAT;

    // 3. Disable DMA stream before configuration
    DMAxStream->CR &= ~DMA_SxCR_EN;
    while (DMAxStream->CR & DMA_SxCR_EN)
        ; // wait until fully disabled

    // 4. Configure peripheral and memory addresses
    DMAxStream->PAR = (uint32_t)&USARTx->DR; // peripheral register
    DMAxStream->M0AR = (uint32_t)pData;      // memory address

    // 5. Set number of data items
    DMAxStream->NDTR = Size;

    // 6. Configure stream control register (CR)
    uint32_t tmp = DMAxStream->CR;
    tmp &= ~(DMA_SxCR_CHSEL | DMA_SxCR_DIR | DMA_SxCR_MINC |
             DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | DMA_SxCR_PL);
    tmp |= (pHandle->TxDMAChannel << DMA_SxCR_CHSEL_Pos) | // DMA channel
           (0x1U << DMA_SxCR_DIR_Pos) |                    // Memory-to-peripheral
           DMA_SxCR_MINC |                                 // Increment memory pointer
           (0x0U << DMA_SxCR_MSIZE_Pos) |                  // Memory size 8-bit
           (0x0U << DMA_SxCR_PSIZE_Pos) |                  // Peripheral size 8-bit
           (0x1U << DMA_SxCR_PL_Pos);                      // Medium priority

    DMAxStream->CR = tmp;

    // 7. Enable transfer complete interrupt (optional)
    DMAxStream->CR |= DMA_SxCR_TCIE;

    // 8. Enable DMA stream
    DMAxStream->CR |= DMA_SxCR_EN;
}

void UART_ReceiveDMA(UART_Handle_t *pHandle, uint8_t *pData, uint32_t Size)
{
    if (pHandle->BusyState != UART_STATE_READY || Size == 0 || pHandle->pRxDMAStream == NULL)
        return;

    // Mark UART busy
    pHandle->BusyState = UART_STATE_BUSY_RX;
    pHandle->pRxBuffer = pData;
    pHandle->RxSize = Size;

    USART_TypeDef *USARTx = pHandle->Init.pUSARTx;
    DMA_Stream_TypeDef *DMAxStream = pHandle->pRxDMAStream;

    // Enable UART DMA RX mode
    USARTx->CR3 |= USART_CR3_DMAR;

    // Disable DMA before config
    DMAxStream->CR &= ~DMA_SxCR_EN;
    while (DMAxStream->CR & DMA_SxCR_EN)
        ;

    // Peripheral = USART data register, Memory = user buffer
    DMAxStream->PAR = (uint32_t)&USARTx->DR;
    DMAxStream->M0AR = (uint32_t)pData;
    DMAxStream->NDTR = Size;

    uint32_t tmp = DMAxStream->CR;
    tmp &= ~(DMA_SxCR_CHSEL | DMA_SxCR_DIR | DMA_SxCR_MINC |
             DMA_SxCR_MSIZE | DMA_SxCR_PSIZE | DMA_SxCR_PL);
    tmp |= (pHandle->RxDMAChannel << DMA_SxCR_CHSEL_Pos) | // channel
           (0x0U << DMA_SxCR_DIR_Pos) |                    // Peripheral-to-memory
           DMA_SxCR_MINC |                                 // increment buffer
           (0x0U << DMA_SxCR_MSIZE_Pos) |                  // 8-bit memory
           (0x0U << DMA_SxCR_PSIZE_Pos) |                  // 8-bit peripheral
           (0x1U << DMA_SxCR_PL_Pos);                      // medium priority

    DMAxStream->CR = tmp;

    DMAxStream->CR |= DMA_SxCR_TCIE; // enable transfer complete interrupt
    DMAxStream->CR |= DMA_SxCR_EN;   // enable stream
}
