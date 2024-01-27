

#include "stm32f10x.h"

void delay_ms(uint32_t ms) {
    // T�nh to�n s? l?n l?p c?n thi?t d? d?t du?c d? tr?
    uint32_t ticks = ms * (SystemCoreClock / 8000);

    // Thi?t l?p SysTick
    SysTick_Config(ticks);

    // Ch? cho SysTick h?t s? l?n l?p
    while (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk);

    // T?t SysTick d? tr�nh t?o th�m ng?n g?n th?i gian tr?
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

int main(void) {
    // C?u h�nh RCC d? s? d?ng HSI (8MHz)
    RCC->CR |= RCC_CR_HSION;           // B?t HSI
    while (!(RCC->CR & RCC_CR_HSIRDY)); // �?i HSI s?n s�ng
    RCC->CFGR &= ~RCC_CFGR_SW;         // X�a c�c bit SW
    RCC->CFGR |= RCC_CFGR_SW_HSI;      // Ch?n HSI l�m ngu?n clock
    while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI); // �?i chuy?n d?i xong

    // C?u h�nh GPIO PC13 l�m output
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN; // B?t clock cho GPIOC
    GPIOC->CRH &= ~(GPIO_CRH_CNF13 | GPIO_CRH_MODE13); // X�a c?u h�nh cu
    GPIOC->CRH |= GPIO_CRH_MODE13_0; // Output mode, max speed 10MHz

    while (1) {
        // B?t LED tr�n PC13 (t?t LED)
        GPIOC->BSRR = GPIO_BSRR_BS13;
        delay_ms(1000);

        // T?t LED tr�n PC13 (b?t LED)
        GPIOC->BSRR = GPIO_BSRR_BR13;
        delay_ms(1000);
    }

    return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
    while (1);
}
#endif