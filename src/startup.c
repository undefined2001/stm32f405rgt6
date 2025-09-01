#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;

void main();

extern void __libc_init_array(void);

typedef void (*f_ptr)(void);

void Default_Handler();

void Reset_Handler(void);
void NMI_Handler() __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler() __attribute__((weak, alias("Default_Handler")));
void MemManage_Handler() __attribute__((weak, alias("Default_Handler")));
void BusFault_Handler() __attribute__((weak, alias("Default_Handler")));
void UsageFault_Handler() __attribute__((weak, alias("Default_Handler")));
void SVC_Handler() __attribute__((weak, alias("Default_Handler")));
void DebugMon_Handler() __attribute__((weak, alias("Default_Handler")));
void PendSV_Handler() __attribute__((weak, alias("Default_Handler")));
void SysTick_Handler() __attribute__((weak, alias("Default_Handler")));

/* External Interrupts */
void WWDG_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* Window WatchDog              */
void PVD_IRQHandler() __attribute__((weak, alias("Default_Handler")));                /* PVD through EXTI Line detection */
void TAMP_STAMP_IRQHandler() __attribute__((weak, alias("Default_Handler")));         /* Tamper and TimeStamps through the EXTI line */
void RTC_WKUP_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* RTC Wakeup through the EXTI line */
void FLASH_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* FLASH                        */
void RCC_IRQHandler() __attribute__((weak, alias("Default_Handler")));                /* RCC                          */
void EXTI0_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* EXTI Line0                   */
void EXTI1_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* EXTI Line1                   */
void EXTI2_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* EXTI Line2                   */
void EXTI3_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* EXTI Line3                   */
void EXTI4_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* EXTI Line4                   */
void DMA1_Stream0_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 0                */
void DMA1_Stream1_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 1                */
void DMA1_Stream2_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 2                */
void DMA1_Stream3_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 3                */
void DMA1_Stream4_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 4                */
void DMA1_Stream5_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 5                */
void DMA1_Stream6_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream 6                */
void ADC_IRQHandler() __attribute__((weak, alias("Default_Handler")));                /* ADC1, ADC2 and ADC3s         */
void CAN1_TX_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* CAN1 TX                      */
void CAN1_RX0_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* CAN1 RX0                     */
void CAN1_RX1_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* CAN1 RX1                     */
void CAN1_SCE_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* CAN1 SCE                     */
void EXTI9_5_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* External Line[9:5]s          */
void TIM1_BRK_TIM9_IRQHandler() __attribute__((weak, alias("Default_Handler")));      /* TIM1 Break and TIM9          */
void TIM1_UP_TIM10_IRQHandler() __attribute__((weak, alias("Default_Handler")));      /* TIM1 Update and TIM10        */
void TIM1_TRG_COM_TIM11_IRQHandler() __attribute__((weak, alias("Default_Handler"))); /* TIM1 Trigger and Commutation and TIM11 */
void TIM1_CC_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* TIM1 Capture Compare         */
void TIM2_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* TIM2                         */
void TIM3_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* TIM3                         */
void TIM4_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* TIM4                         */
void I2C1_EV_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* I2C1 Event                   */
void I2C1_ER_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* I2C1 Error                   */
void I2C2_EV_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* I2C2 Event                   */
void I2C2_ER_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* I2C2 Error                   */
void SPI1_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* SPI1                         */
void SPI2_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* SPI2                         */
void USART1_IRQHandler() __attribute__((weak, alias("Default_Handler")));             /* USART1                       */
void USART2_IRQHandler() __attribute__((weak, alias("Default_Handler")));             /* USART2                       */
void USART3_IRQHandler() __attribute__((weak, alias("Default_Handler")));             /* USART3                       */
void EXTI15_10_IRQHandler() __attribute__((weak, alias("Default_Handler")));          /* External Line[15:10]s        */
void RTC_Alarm_IRQHandler() __attribute__((weak, alias("Default_Handler")));          /* RTC Alarm (A and B) through EXTI Line */
void OTG_FS_WKUP_IRQHandler() __attribute__((weak, alias("Default_Handler")));        /* USB OTG FS Wakeup through EXTI line */
void TIM8_BRK_TIM12_IRQHandler() __attribute__((weak, alias("Default_Handler")));     /* TIM8 Break and TIM12         */
void TIM8_UP_TIM13_IRQHandler() __attribute__((weak, alias("Default_Handler")));      /* TIM8 Update and TIM13        */
void TIM8_TRG_COM_TIM14_IRQHandler() __attribute__((weak, alias("Default_Handler"))); /* TIM8 Trigger and Commutation and TIM14 */
void TIM8_CC_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* TIM8 Capture Compare         */
void DMA1_Stream7_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA1 Stream7                 */
void FSMC_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* FSMC                         */
void SDIO_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* SDIO                         */
void TIM5_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* TIM5                         */
void SPI3_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* SPI3                         */
void UART4_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* UART4                        */
void UART5_IRQHandler() __attribute__((weak, alias("Default_Handler")));              /* UART5                        */
void TIM6_DAC_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* TIM6 and DAC1&2 underrun errors */
void TIM7_IRQHandler() __attribute__((weak, alias("Default_Handler")));               /* TIM7                         */
void DMA2_Stream0_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 0                */
void DMA2_Stream1_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 1                */
void DMA2_Stream2_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 2                */
void DMA2_Stream3_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 3                */
void DMA2_Stream4_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 4                */
void CAN2_TX_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* CAN2 TX                      */
void CAN2_RX0_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* CAN2 RX0                     */
void CAN2_RX1_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* CAN2 RX1                     */
void CAN2_SCE_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* CAN2 SCE                     */
void OTG_FS_IRQHandler() __attribute__((weak, alias("Default_Handler")));             /* USB OTG FS                   */
void DMA2_Stream5_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 5                */
void DMA2_Stream6_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 6                */
void DMA2_Stream7_IRQHandler() __attribute__((weak, alias("Default_Handler")));       /* DMA2 Stream 7                */
void USART6_IRQHandler() __attribute__((weak, alias("Default_Handler")));             /* USART6                       */
void I2C3_EV_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* I2C3 event                   */
void I2C3_ER_IRQHandler() __attribute__((weak, alias("Default_Handler")));            /* I2C3 error                   */
void OTG_HS_EP1_OUT_IRQHandler() __attribute__((weak, alias("Default_Handler")));     /* USB OTG HS End Point 1 Out   */
void OTG_HS_EP1_IN_IRQHandler() __attribute__((weak, alias("Default_Handler")));      /* USB OTG HS End Point 1 In    */
void OTG_HS_WKUP_IRQHandler() __attribute__((weak, alias("Default_Handler")));        /* USB OTG HS Wakeup through EXTI */
void OTG_HS_IRQHandler() __attribute__((weak, alias("Default_Handler")));             /* USB OTG HS                   */
void HASH_RNG_IRQHandler() __attribute__((weak, alias("Default_Handler")));           /* Hash and Rng                 */
void FPU_IRQHandler() __attribute__((weak, alias("Default_Handler")));                /*FPU Interrupt*/

f_ptr vectors[] __attribute__((section(".isr_vector"))) = {
    (f_ptr)&_estack,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,

    WWDG_IRQHandler,
    PVD_IRQHandler,
    TAMP_STAMP_IRQHandler,
    RTC_WKUP_IRQHandler,
    FLASH_IRQHandler,
    RCC_IRQHandler,
    EXTI0_IRQHandler,
    EXTI1_IRQHandler,
    EXTI2_IRQHandler,
    EXTI3_IRQHandler,
    EXTI4_IRQHandler,
    DMA1_Stream0_IRQHandler,
    DMA1_Stream1_IRQHandler,
    DMA1_Stream2_IRQHandler,
    DMA1_Stream3_IRQHandler,
    DMA1_Stream4_IRQHandler,
    DMA1_Stream5_IRQHandler,
    DMA1_Stream6_IRQHandler,
    ADC_IRQHandler,
    CAN1_TX_IRQHandler,
    CAN1_RX0_IRQHandler,
    CAN1_RX1_IRQHandler,
    CAN1_SCE_IRQHandler,
    EXTI9_5_IRQHandler,
    TIM1_BRK_TIM9_IRQHandler,
    TIM1_UP_TIM10_IRQHandler,
    TIM1_TRG_COM_TIM11_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_IRQHandler,
    TIM4_IRQHandler,
    I2C1_EV_IRQHandler,
    I2C1_ER_IRQHandler,
    I2C2_EV_IRQHandler,
    I2C2_ER_IRQHandler,
    SPI1_IRQHandler,
    SPI2_IRQHandler,
    USART1_IRQHandler,
    USART2_IRQHandler,
    USART3_IRQHandler,
    EXTI15_10_IRQHandler,
    RTC_Alarm_IRQHandler,
    OTG_FS_WKUP_IRQHandler,
    TIM8_BRK_TIM12_IRQHandler,
    TIM8_UP_TIM13_IRQHandler,
    TIM8_TRG_COM_TIM14_IRQHandler,
    TIM8_CC_IRQHandler,
    DMA1_Stream7_IRQHandler,
    FSMC_IRQHandler,
    SDIO_IRQHandler,
    TIM5_IRQHandler,
    SPI3_IRQHandler,
    UART4_IRQHandler,
    UART5_IRQHandler,
    TIM6_DAC_IRQHandler,
    TIM7_IRQHandler,
    DMA2_Stream0_IRQHandler,
    DMA2_Stream1_IRQHandler,
    DMA2_Stream2_IRQHandler,
    DMA2_Stream3_IRQHandler,
    DMA2_Stream4_IRQHandler,
    0,
    0,
    CAN2_TX_IRQHandler,
    CAN2_RX0_IRQHandler,
    CAN2_RX1_IRQHandler,
    CAN2_SCE_IRQHandler,
    OTG_FS_IRQHandler,
    DMA2_Stream5_IRQHandler,
    DMA2_Stream6_IRQHandler,
    DMA2_Stream7_IRQHandler,
    USART6_IRQHandler,
    I2C3_EV_IRQHandler,
    I2C3_ER_IRQHandler,
    OTG_HS_EP1_OUT_IRQHandler,
    OTG_HS_EP1_IN_IRQHandler,
    OTG_HS_WKUP_IRQHandler,
    OTG_HS_IRQHandler,
    0,
    0,
    HASH_RNG_IRQHandler,
    FPU_IRQHandler,
};

static void copy_memory(uint32_t *dest, uint32_t *src, uint32_t size)
{
    while (size--)
        *dest++ = *src++;
}

static void zero_bss(uint32_t *src, uint32_t size)
{
    while (size--)
        *src++ = 0;
}

void Reset_Handler(void)
{
    uint32_t *src = &_sidata;
    uint32_t *dest = &_sdata;
    copy_memory(dest, src, &_edata - &_sdata);

    uint32_t *bss_start = &_sbss;
    zero_bss(bss_start, &_ebss - &_sbss);

    __libc_init_array();

    main();
}

void Default_Handler()
{
    while (1)
        ;
}