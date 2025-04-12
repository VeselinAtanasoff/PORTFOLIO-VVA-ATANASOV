#include "UI.h"

UI::UI() {
    initUSART();
}

void UI::initUSART() {
    // Enable USART2 clock
    RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
    // Set GPIO pin PA2 to alternate function.
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER2) | (0b10 << GPIO_MODER_MODER2_Pos);
    // Select alternate function AF7 (USART2_TX) for GPIO pin PA2.
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL2) | (0b0111 << GPIO_AFRL_AFRL2_Pos);
    // Set GPIO pin PA3 to alternate function.
    GPIOA->MODER = (GPIOA->MODER & ~GPIO_MODER_MODER3) | (0b10 << GPIO_MODER_MODER3_Pos);
    // Select alternate function AF7 (USART2_RX) for GPIO pin PA3.
    GPIOA->AFR[0] = (GPIOA->AFR[0] & ~GPIO_AFRL_AFRL3) | (0b0111 << GPIO_AFRL_AFRL3_Pos);

    // Configure USART2
    USART2->BRR = 36000000 / 9600; // Assuming 36 MHz clock, 9600 baud rate.
    USART2->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void UI::sendString(const char *str) {
    while (*str) {
        while (!(USART2->ISR & USART_ISR_TXE));
        USART2->TDR = *str++;
    }
}

void UI::sendInt(int value) {
    char buf[12]; // Enough for 10 digits + '\0'
    snprintf(buf, sizeof(buf), "%d\r\n", value);
    sendString(buf); // Reuse the existing method
}

char* UI::receiveString() {
    static int i = 0;
    char c = 0;
    USART2->ICR |= USART_ICR_ORECF; // Clear overrun error flag.
    while (i == 0 || c != '\0') {
        if (USART2->ISR & USART_ISR_RXNE) {
            c = USART2->RDR;
            if (c == '\n') {
                c = '\0';
                rcvBuf[i++] = c;
            } else if (i < BUFLENGTH - 1) {
                rcvBuf[i++] = c;
            }
        }
    }
    i = 0;
    return rcvBuf;
}

void UI::sendFormattedString(const char *format, ...) {
    char buf[100]; // Buffer for formatted string
    va_list args;
    va_start(args, format);
    vsnprintf(buf, sizeof(buf), format, args);
    va_end(args);
    sendString(buf);
}