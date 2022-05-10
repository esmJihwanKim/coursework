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
/*************************************************/
void rti_service(void) 
{
   static int max_reached = 0;
   
   if(max_reached<5)
   {
      operateMotor();
      max_reached++;
   } 
   else if (max_reached>=5 && max_reached<10) 
   {
      // max pwm for some time 
      max_reached++;
   } 
   else 
   {
      operateMotor();      
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
	
	
	if (count >= scaler) {
	 /*�� 1�ʸ��� ����*/
		// process task
		rti_service();
  	count = 0;
	}
	// clear flag
  Crg.crgflg.bit.rtif = 1;    // �ǽð� ���ͷ�Ʈ �÷��� �ʱ�ȭ

}
