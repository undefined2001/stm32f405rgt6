#ifndef GPIO_H_
#define GPIO_H_

#include "stm32f405xx.h"

/**
 * @defgroup GPIO_Pins GPIO Pin Definitions
 * @{
 */
#define GPIO_PIN_0   0x0001U /**< GPIO Pin 0 */
#define GPIO_PIN_1   0x0002U /**< GPIO Pin 1 */
#define GPIO_PIN_2   0x0004U /**< GPIO Pin 2 */
#define GPIO_PIN_3   0x0008U /**< GPIO Pin 3 */
#define GPIO_PIN_4   0x0010U /**< GPIO Pin 4 */
#define GPIO_PIN_5   0x0020U /**< GPIO Pin 5 */
#define GPIO_PIN_6   0x0040U /**< GPIO Pin 6 */
#define GPIO_PIN_7   0x0080U /**< GPIO Pin 7 */
#define GPIO_PIN_8   0x0100U /**< GPIO Pin 8 */
#define GPIO_PIN_9   0x0200U /**< GPIO Pin 9 */
#define GPIO_PIN_10  0x0400U /**< GPIO Pin 10 */
#define GPIO_PIN_11  0x0800U /**< GPIO Pin 11 */
#define GPIO_PIN_12  0x1000U /**< GPIO Pin 12 */
#define GPIO_PIN_13  0x2000U /**< GPIO Pin 13 */
#define GPIO_PIN_14  0x4000U /**< GPIO Pin 14 */
#define GPIO_PIN_15  0x8000U /**< GPIO Pin 15 */
/** @} */

/**
 * @defgroup GPIO_Modes GPIO Mode Definitions
 * @{
 */
#define GPIO_MODE_INPUT   0x0U /**< Input mode */
#define GPIO_MODE_OUTPUT  0x1U /**< General purpose output mode */
#define GPIO_MODE_ALTFN   0x2U /**< Alternate function mode */
#define GPIO_MODE_ANALOG  0x3U /**< Analog mode */
/** @} */

/**
 * @brief GPIO Initialization structure
 *
 * This structure holds the configuration settings for a GPIO pin.
 */
typedef struct
{
    GPIO_TypeDef *pGPIOx; /**< Pointer to GPIO peripheral base address */
    uint32_t Mode;        /**< GPIO mode: @ref GPIO_Modes */
    uint32_t Ospeed;      /**< Output speed (0: Low, 1: Medium, 2: Fast, 3: High) */
    uint32_t Otype;       /**< Output type (0: Push-pull, 1: Open-drain) */
    uint32_t Pupd;        /**< Pull-up/Pull-down (0: None, 1: Pull-up, 2: Pull-down) */
    uint32_t AFn;         /**< Alternate function number (0–15) */
} gpio_init_t;

#endif // GPIO_H_
