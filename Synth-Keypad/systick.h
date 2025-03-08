#ifndef SYSTICK_H
#define SYSTICK_H

void InitSquareWave(void (*interrupt_handler)());
void StartSquareWave(unsigned int period_in_us);
void StopSquareWave();

#endif