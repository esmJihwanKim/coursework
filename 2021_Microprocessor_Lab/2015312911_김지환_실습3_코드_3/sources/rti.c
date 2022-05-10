#include "rti.h"

int scaler;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �ʱ�ȭ �Ѵ�.*/
/*************************************************/
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = 0b00010111;     //����Ÿ�� ���ͷ�Ʈ�� �ӵ� ����(0.5ms �� �Ͻÿ�) -> 8 x 2^10
	Crg.crgint.byte |= 0b10000000;		//����Ÿ�� ���ͷ�Ʈ enable
	
}

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �߻��� ������ */
/*  7-���׸�Ʈ�� ����. */
/*  ex) Pim.pth.byte = 0x01       ���׸�Ʈ �����*/
/*  �����Ӱ� �ڵ��� �Ͻÿ�.			*/
/*************************************************/
void rti_service(void) 
{
  
  if(scaler==1)  // SW2 Pressed  - Clockwise - Increase Port Number 
  {  
     if(Pim.pth.byte == 0b00100000) Pim.pth.byte = 0b00000001;   
     else Pim.pth.byte = Pim.pth.byte << 1;
                  
  } 
                                 
  else if(scaler==2)    // SW3 Pressed - Counter Clockwise - Decrease Port Number 
  {      
     if(Pim.pth.byte == 0b00000001) Pim.pth.byte = 0b00100000;   
     else Pim.pth.byte = Pim.pth.byte >> 1; 
   
  }
  
  else  // Scaler == 3 - Stop 
  {
      
  }
  
}

/*************************************************/
/*  ����Ÿ�� ���ͷ�Ʈ�� �߻��� ���� ������ �����Ѵ�. */
/*************************************************/

/* 0.5�� ���� rti_handler ���  */
void rti_handler(void)
{
	static int count = 0;   //static
	
	count++;

	if (count >= 2000) {
	 /*�� 1�ʸ��� ����*/
		// process task
		rti_service();
  	count = 0;

		
	}
	// clear flag
  Crg.crgflg.bit.rtif = 1;    // �ǽð� ���ͷ�Ʈ �÷��� �ʱ�ȭ

}
