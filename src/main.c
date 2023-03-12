#include "address.h"

void	clock_init(void) {
	RCC_AHB1ENR |= 0x1; // enable GPIOA
	RCC_APB2ENR |= (1 << 12); // enable clock for spi1
}

int	main(void) {
}
