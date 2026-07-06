#define RCC_APB2ENR (*(volatile unsigned int*)0x40021018)
#define GPIOC_CRH   (*(volatile unsigned int*)0x40011004)
#define GPIOC_ODR   (*(volatile unsigned int*)0x4001100C)

void delay(volatile int t)
{
    while(t--) {
        for(volatile int i=0;i<1000;i++);
    }
}

int main(void)
{
    // 1. enable GPIOC clock
    RCC_APB2ENR |= (1 << 4);

    // 2. config PC13 as output
    GPIOC_CRH &= ~(0xF << 20);
    GPIOC_CRH |=  (0x2 << 20);

    while (1)
    {
        GPIOC_ODR &= ~(1 << 13); // LED ON
        delay(50000);

        GPIOC_ODR |= (1 << 13);  // LED OFF
        delay(50000);
    }
}