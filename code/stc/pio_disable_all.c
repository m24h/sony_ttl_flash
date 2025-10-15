#include "pio.h"

void pio_disable_all(void)
{
	pio_port_disable(0);
	pio_port_disable(1);
	pio_port_disable(2);
	pio_port_disable(3);
	pio_port_disable(4);
	pio_port_disable(5);
#if defined(MCU_STC8H)
	pio_port_disable(6);
	pio_port_disable(7);
#endif
}