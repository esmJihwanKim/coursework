#include "main.h"


void main ()
{
  char str[20];  
  int_disable();                      //���ͷ�Ʈ disable
  																		//����Ÿ�� ���ͷ�Ʈ �ʱ�ȭ 
  init_rti(2000);				
  ini_interrupt();			//���ͷ�Ʈ �ʱ�ȭ      (�� 0.5ms���� ���ͷ�Ʈ)
  init_pwm();
  init_LCD();
  																	
  int_enable();				//���ͷ�Ʈ enable
  xint_enable();			
                
  Pim.ddrh.byte= 0xFF; 
  Pim.pth.byte = 0b00000001;
    
	//Insert Application Software Here.
	for (;;) { 
	    
	} 

}