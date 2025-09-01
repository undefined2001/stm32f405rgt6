#include "stm32f405xx.h"
#include "uart.h"

void UART_Config(void);
void UART1_GPIO_Init(void);
void UART_SendBuff(UART_Config_t *huart, uint8_t *pData, uint32_t size);
UART_Config_t huart;

int main(void)
{

    UART1_GPIO_Init();
    UART_Config();

    uint8_t msg[] = "\033[32m[INFO]This is UART Driver Test\r\n\033[0m";

    while (1)
    {
        UART_SendBuff(&huart, msg, sizeof(msg));
        for (volatile int i = 0; i < 500000; i++)
            ; // Delay
    }
}

void UART_Config(void)
{
    huart.pUSARTx = USART1;
    huart.BaudRate = UART_BAUDRATE_115200;
    huart.Direction = UART_MODE_TX_RX;
    huart.ParityConfig = UART_PARITY_NONE;
    huart.StopBits = UART_STOPBITS_1BIT;
    huart.WordLen = UART_WORD_LEN_8BIT;
    UART_Init(&huart);
}

void UART1_GPIO_Init(void)
{
    // 1. Enable clock for GPIOA
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;

    // 2. Enable clock for USART1
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 3. Configure PA9 (TX) and PA10 (RX) as Alternate Function
    GPIOA->MODER &= ~((3U << (9 * 2)) | (3U << (10 * 2))); // clear mode
    GPIOA->MODER |= (2U << (9 * 2)) | (2U << (10 * 2));    // AF mode

    // 4. Select AF7 (USART1/2/3) for PA9, PA10
    GPIOA->AFR[1] &= ~((0xF << ((9 - 8) * 4)) | (0xF << ((10 - 8) * 4)));
    GPIOA->AFR[1] |= (7U << ((9 - 8) * 4)) | (7U << ((10 - 8) * 4));

    // 5. Set output type to push-pull (default), speed high, pull-up
    GPIOA->OTYPER &= ~((1U << 9) | (1U << 10));           // push-pull
    GPIOA->OSPEEDR |= (3U << (9 * 2)) | (3U << (10 * 2)); // very high speed
    GPIOA->PUPDR &= ~((3U << (9 * 2)) | (3U << (10 * 2)));
    GPIOA->PUPDR |= (1U << (9 * 2)) | (1U << (10 * 2)); // pull-up
}

void UART_SendBuff(UART_Config_t *huart, uint8_t *pData, uint32_t size)
{
    while (size--)
    {
        while (!(huart->pUSARTx->SR & USART_SR_TXE))
            ;
        huart->pUSARTx->DR = *pData++;
    }
}