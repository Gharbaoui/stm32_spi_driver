#include "address.h"

void	clock_init(void) {
	RCC_AHB1ENR |= 0x1; // enable GPIOA
	RCC_APB2ENR |= (1 << 12); // enable clock for spi1
}


void	gpio_init(void) {
	GPIOA_MODER &= ~( ( 3 << (2 * 4) ) | ( 3 << (2 * 5) ) |
	( 3 << (2 * 6) ) | ( 3 << (2 * 7) ) );
}

int	main(void) {
}
