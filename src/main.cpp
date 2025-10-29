#include "stm32f4xx.h"

extern "C" void SystemInit(void);

int main(void) {
    SystemInit();

    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;   // Enable GPIOD clock
    GPIOD->MODER |= GPIO_MODER_MODE12_0;   // Set PD12 as output

    while (1) {
        GPIOD->ODR ^= GPIO_ODR_OD12;       // Toggle LED
        for (volatile int i = 0; i < 1000000; i++);
    }
}
