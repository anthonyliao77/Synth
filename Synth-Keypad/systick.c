#include "systick.h"
#include "ports.h"

// I den här funktionen skall lägre byten av Port E förberedas för att lägga
// ut en signal på pinne 0. Den skall bara kallas en gång.
void InitSquareWave(void (*interrupt_handler)())
{
	*((void (**)(void))(0x2001C000 + 0x3C)) = interrupt_handler;	
	// Sätt pinne 0 till "ut"
	*GPIO_E_MODER &= ~0x3;
	*GPIO_E_MODER |= 0x1; 
}

// När man kallat den här funktionen skall en fyrkantsvåg med given period 
// (i mikrosekunder) läggas ut på pinne 0, Port E. Perioden skall kunna 
// vara upp till 99000 mikrosekunder.
void StartSquareWave(unsigned int period_in_us)
{
	unsigned int system_frequency = 168; // Clocks per microsecond 
	// Ladda systick med halv period (i klockor)
	*STK_LOAD = (period_in_us / 2) * system_frequency;
	// Starta systick MED INTERRUPT
	*STK_CTRL = 7; 
}

// Den här funktionen skall avbryta fyrkantsvågen.
void StopSquareWave()
{
	*STK_CTRL &= ~0x1; 
}