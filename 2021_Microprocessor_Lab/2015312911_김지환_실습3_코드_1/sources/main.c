#include "main.h"

void main ()
{  
  int_disable();                      //���ͷ�Ʈ disable
  																		//����Ÿ�� ���ͷ�Ʈ �ʱ�ȭ 
  ini_interrupt();			//���ͷ�Ʈ �ʱ�ȭ      (�� 0.5ms���� ���ͷ�Ʈ)
  																	
  Regs.ddrb.byte = 0xFF;
  Regs.portb.byte = 0xFF;		
  
  int_enable();
      
	//Insert Application Software Here.
	for (;;); 

}