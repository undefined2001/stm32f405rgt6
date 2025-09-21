#include "stm32f405xx.h"
#include "uart.h"

/**
 * @brief Global UART1 handle structure
 *
 * Configured with default parameters for USART1 at 115200 baud.
 */
UART_Handle_t huart = UART_HANDLE_STRUCT_DEFAULT(USART1, 115200);

/** @brief Buffer for received UART data */
uint8_t msg[10];

/* Prototypes */
void UART1_GPIO_Init(void);
void UART_SendBuff(UART_Handle_t *huart, uint8_t *pData, uint32_t size);

/**
 * @brief Main application entry point
 *
 * Initializes USART1 with DMA, configures interrupts,
 * and starts continuous receive/echo operation.
 *
 * @return int Never returns under normal conditions
 */
int main(void)
{
    /* Enable DMA IRQs for USART1 TX (Stream7) and RX (Stream2) */
    NVIC_EnableIRQ(DMA2_Stream7_IRQn);  /**< TX DMA IRQ enable */
    NVIC_SetPriority(DMA2_Stream7_IRQn, 0);
    NVIC_EnableIRQ(DMA2_Stream2_IRQn);  /**< RX DMA IRQ enable */
    NVIC_SetPriority(DMA2_Stream2_IRQn, 0);

    /* Initialize clocks, GPIO, and UART peripheral */
    UART1_GPIO_Init();
    RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;

    /* Assign DMA streams and channels for USART1 */
    huart.pTxDMAStream = DMA2_Stream7;
    huart.TxDMAChannel = 4;
    huart.pRxDMAStream = DMA2_Stream2;
    huart.RxDMAChannel = 4;

    UART_Init(&huart);

    /* Start first RX transfer */
    UART_ReceiveDMA(&huart, msg, sizeof(msg));

    while (1)
    {
        /* Main loop empty, echo handled entirely in ISR */
    }
}

/**
 * @brief Blocking UART transmit function (for debugging)
 *
 * Sends a buffer of data over UART using polling (no DMA/interrupts).
 *
 * @param huart Pointer to UART handle
 * @param pData Pointer to data buffer
 * @param size  Number of bytes to send
 */
void UART_SendBuff(UART_Handle_t *huart, uint8_t *pData, uint32_t size)
{
    while (size--)
    {
        while (!(huart->Init.pUSARTx->SR & USART_SR_TXE))
            ;
        huart->Init.pUSARTx->DR = *pData++;
    }
}

/**
 * @brief Initialize GPIO pins for USART1
 *
 * Configures PA9 (TX) and PA10 (RX) as alternate function AF7.
 * - High speed, push-pull, pull-up enabled.
 * - Enables GPIOA and USART1 peripheral clocks.
 */
void UART1_GPIO_Init(void)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    /* Configure PA9/PA10 in alternate function mode */
    GPIOA->MODER &= ~((3U << (9 * 2)) | (3U << (10 * 2)));
    GPIOA->MODER |= (2U << (9 * 2)) | (2U << (10 * 2));

    /* Set AF7 (USART1) */
    GPIOA->AFR[1] &= ~((0xF << ((9 - 8) * 4)) | (0xF << ((10 - 8) * 4)));
    GPIOA->AFR[1] |= (7U << ((9 - 8) * 4)) | (7U << ((10 - 8) * 4));

    /* Push-pull, high speed */
    GPIOA->OTYPER &= ~((1U << 9) | (1U << 10));
    GPIOA->OSPEEDR |= (3U << (9 * 2)) | (3U << (10 * 2));

    /* Pull-up resistors */
    GPIOA->PUPDR &= ~((3U << (9 * 2)) | (3U << (10 * 2)));
    GPIOA->PUPDR |= (1U << (9 * 2)) | (1U << (10 * 2));
}

/* ========================= DMA IRQ Handlers ========================= */

/**
 * @brief DMA2 Stream7 IRQ Handler (USART1 TX)
 *
 * Handles TX complete and error conditions for DMA-driven UART transmit.
 */
void DMA2_Stream7_IRQHandler(void)
{
    if (DMA2->HISR & DMA_HISR_TCIF7) /**< Transfer complete */
    {
        DMA2->HIFCR |= DMA_HIFCR_CTCIF7;
        USART1->CR3 &= ~USART_CR3_DMAT;
        DMA2_Stream7->CR &= ~DMA_SxCR_EN;
        huart.BusyState = UART_STATE_READY;
    }

    if (DMA2->HISR & (DMA_HISR_TEIF7 | DMA_HISR_DMEIF7 | DMA_HISR_FEIF7)) /**< Errors */
    {
        DMA2->HIFCR |= DMA_HIFCR_CTEIF7 | DMA_HIFCR_CDMEIF7 | DMA_HIFCR_CFEIF7;
        USART1->CR3 &= ~USART_CR3_DMAT;
        DMA2_Stream7->CR &= ~DMA_SxCR_EN;
        huart.BusyState = UART_STATE_READY;
    }
}

/**
 * @brief DMA2 Stream2 IRQ Handler (USART1 RX)
 *
 * Handles RX complete and error conditions for DMA-driven UART receive.
 * Echoes received buffer back over TX DMA and restarts RX.
 */
void DMA2_Stream2_IRQHandler(void)
{
    if (DMA2->LISR & DMA_LISR_TCIF2) /**< Transfer complete */
    {
        DMA2->LIFCR |= DMA_LIFCR_CTCIF2;
        USART1->CR3 &= ~USART_CR3_DMAR;
        DMA2_Stream2->CR &= ~DMA_SxCR_EN;
        huart.BusyState = UART_STATE_READY;

        /* Echo received data */
        UART_TransmitDMA(&huart, msg, sizeof(msg));

        /* Restart reception */
        UART_ReceiveDMA(&huart, msg, sizeof(msg));
    }

    if (DMA2->LISR & (DMA_LISR_TEIF2 | DMA_LISR_DMEIF2 | DMA_LISR_FEIF2)) /**< Errors */
    {
        DMA2->LIFCR |= DMA_LIFCR_CTEIF2 | DMA_LIFCR_CDMEIF2 | DMA_LIFCR_CFEIF2;
        USART1->CR3 &= ~USART_CR3_DMAR;
        DMA2_Stream2->CR &= ~DMA_SxCR_EN;
        huart.BusyState = UART_STATE_READY;
    }
}
