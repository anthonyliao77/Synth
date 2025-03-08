#ifndef KEYBOARD_H
#define KEYBOARD_H

void InitKeyboard(void (*interrupt_handler)());
unsigned char keyb(void);

#endif