#include "main.h"

int speed = 0;

void main ()
{  
  speed++; 
  
  int_disable();                      //���ͷ�Ʈ disable
  																		//����Ÿ�� ���ͷ�Ʈ �ʱ�ȭ 
  init_rti(3);				
  ini_interrupt();			//���ͷ�Ʈ �ʱ�ȭ      (�� 0.5ms���� ���ͷ�Ʈ)
  																	
  int_enable();				//���ͷ�Ʈ enanle
  xint_enable();			
                
  Pim.ddrh.byte= 0xFF; 
  Pim.pth.byte = 0b00000001;
    
	//Insert Application Software Here.
	for (;;); 

}