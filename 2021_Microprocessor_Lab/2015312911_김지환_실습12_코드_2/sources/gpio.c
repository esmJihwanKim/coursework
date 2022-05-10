#include "gpio.h"

void init_portb(int direction) 
{
  if (direction == 0)
    Regs.ddrb.byte = 0x0; // all are input
  else
    Regs.ddrb.byte = 0xff; // all are output
}

void set_portb(int reverse, unsigned char data) 
{
  // reverse�� 1�̸� ������Ŵ
  if (reverse == 1)
    Regs.portb.byte = ~data;
  else
    Regs.portb.byte = data;
}

unsigned char get_portb(void) 
{
  return Regs.portb.byte;
}
