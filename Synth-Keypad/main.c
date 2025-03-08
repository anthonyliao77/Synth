#include "ports.h"
#include "keyboard.h"
#include "systick.h"

//////////////////////////////////////////////////////// Song struct /////////////////////////////////////////////////////
typedef struct {
	unsigned int period;
	unsigned int time_in_ms; 
  } Note; 
  
  Note song[] = {
   {3807, 200}, {3807, 200}, {3214, 200}, {3807, 200}, {2863, 200}, {3807, 200}, {2702, 200}, {2551, 200},
   {3807, 200}, {3807, 200}, {3214, 200}, {3807, 200}, {2551, 200}, {3807, 200}, {2863, 200}, {3214, 200},
   {3807, 200}, {3807, 200}, {3214, 200}, {3807, 200}, {2863, 200}, {3807, 200}, {2702, 200}, {2551, 200},
   {3807, 200}, {1607, 200}, {1903, 200}, {2145, 200}, {2551, 200}, {2702, 200}, {2863, 200}, {3214, 200}
  };
  
  unsigned int song_length = sizeof(song)/sizeof(Note); 


/////////////////////////////////////////////////////// SYSTICK interrupt handler /////////////////////////////////////////////////////

volatile unsigned flip;
; unsigned char flipflop = 0xFF;
// Systick handler
void systick_handler(void) {
    *GPIO_E_ODRLOW = flipflop;
    flipflop ^= 0xFF;
    flip = 1;
}


//////////////////////////////////////////////////////// Keyoad interrupt handler /////////////////////////////////////////////////////

// Global variabel som skall vara 0xFF om ingen tangent
// är nedtryckt och annars identifierar den nedtryckta
// knappen.
volatile unsigned char currently_pressed_key = 0xFF;

// Keyboard interrupt handler

void key_handler(void) {

  unsigned int keymap[] =
  {1903, 1803, 1702, 1607, // 1, 2, 3, A
   2407, 2271, 2145, 2024, // 4, 5, 6, B
   3033, 2863, 2702, 2551, // 7, 8, 9, C
   3807, 3607, 3405, 3214}; // *, 0, #, D

  *EXTI_IMR = 0x000; // nollställ interrupt
   
  currently_pressed_key = keyb();
  if (currently_pressed_key == 0xFF)
    StopSquareWave();
  else {
    StartSquareWave(keymap[(currently_pressed_key)]);
  }

  *EXTI_PR = 0xF00; // trigga pending
  *GPIO_E_ODRHIGH = 0xF0; // återaktivera alla rader
  *EXTI_IMR = 0xF00; // aktivera interrupt igen
}
////////////////////////////////////////////////////////////// Main /////////////////////////////////////////////////////////////

void main(void)
{
  // Relocate Vector Table
  *STB_VTOR = 0x2001C000;
  InitSquareWave(systick_handler);
  InitKeyboard(key_handler); 

  while(1){
  };
}