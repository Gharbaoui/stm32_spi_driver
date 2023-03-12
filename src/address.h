#include <stdint.h>

#define RCC_BASE_ADDR 0x40023800
#define RCC_AHB1ENR *(volatile uint32_t *)(RCC_BASE_ADDR + 0x30)
#define	RCC_APB2ENR *(volatile uint32_t *)(RCC_BASE_ADDR + 0x44)

#define GPIOA_BASE_ADDR 0x40020000
#define GPIOA_MODER *(volatile uint32_t *)(GPIOA_BASE_ADDR + 0x0)
