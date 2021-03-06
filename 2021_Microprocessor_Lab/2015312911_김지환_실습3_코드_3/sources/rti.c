#include "rti.h"

int scaler;
int i = 0;
int pin = 0x01;

// s : scaler by 0.5ms
// eg) s=2000 -> 0.5*2000 = 1s

/*************************************************/
/*  리얼타임 인터럽트를 초기화 한다.*/
/*************************************************/
void init_rti(int s)
{
	scaler = s;
	Crg.rtictl.byte = 0b00010111;     //리얼타임 인터럽트의 속도 결정(0.5ms 로 하시오) -> 8 x 2^10
	Crg.crgint.byte |= 0b10000000;		//리얼타임 인터럽트 enable
	
}

/*************************************************/
/*  리얼타임 인터럽트가 발생할 때마다 */
/*  7-세그먼트가 동작. */
/*  ex) Pim.pth.byte = 0x01       세그먼트 값출력*/
/*  자유롭게 코딩을 하시오.			*/
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
/*  리얼타임 인터럽트가 발생할 때의 동작을 정의한다. */
/*************************************************/

/* 0.5초 마다 rti_handler 실?  */
void rti_handler(void)
{
	static int count = 0;   //static
	
	count++;

	if (count >= 2000) {
	 /*약 1초마다 실행*/
		// process task
		rti_service();
  	count = 0;

		
	}
	// clear flag
  Crg.crgflg.bit.rtif = 1;    // 실시간 인터럽트 플래그 초기화

}
